
#include "Base.h"
#include "Assertx.h"
#include "GameUtil.h"
#if defined(__WINDOWS__)
#include <io.h>
#include <Shlwapi.h>
#pragma comment(lib, "shlwapi")
#elif defined(__LINUX__)
#include <execinfo.h>
#include <signal.h>
#include <exception>
#include <setjmp.h>
#include <dirent.h>
#endif

//////////////////////////////////////////////////////////////////////////
void MySleep( uint32_t millionseconds )
{
#if defined(__WINDOWS__)
	Sleep( millionseconds ) ;
#elif defined(__LINUX__)
	usleep( millionseconds*1000 ) ;
#endif
}

TID MyGetCurrentThreadID( )
{
#if defined(__WINDOWS__)
	return GetCurrentThreadId( ) ;
#elif defined(__LINUX__)
	return pthread_self();
#endif
}

CHAR* MySocketError( )
{
#ifndef _ESIZE
#define _ESIZE 256
#endif

extern CHAR Error[_ESIZE] ;
	return Error ;
}
//////////////////////////////////////////////////////////////////////////
bool IsFileExists(const CHAR* szFile)
{
	if( szFile != NULL )
	{
		FILE* fp = fopen(szFile, "r");
		if( fp != NULL )
		{
			fclose(fp);
			return true;
		}
	}
	return false;
}
bool IsPathExists(const CHAR* szPath)
{
#if defined(__WINDOWS__)
	return (::PathFileExists(szPath) ? true : false);
#elif defined(__LINUX__)
	DIR* dir = opendir(szPath);
	if( dir != NULL )
	{
		closedir(dir);
		return true
	}
	return false;
#endif
	return false;
}
bool MakeDir(const CHAR* szPath)
{
	if(IsPathExists(szPath))
	{
		return true;
	}
#if defined(__WINDOWS__)
	if( _mkdir(szPath) == 0 )
		return true;

	return false;
#elif defined(__LINUX__)
	if(mkdir(szPath, 0755) == 0)
		return true;

	return false;
#endif

}
//////////////////////////////////////////////////////////////////////////
void HostName(bstd::string& hn) 
{
#if defined(__LINUX__)
	struct utsname buf;
	if (0 != uname(&buf)) {
		// ensure null termination on failure
		*buf.nodename = '\0';
	}
	hn = buf.nodename;
#elif defined(__WINDOWS__)
	char buf[MAX_COMPUTERNAME_LENGTH + 1];
	DWORD len = MAX_COMPUTERNAME_LENGTH + 1;
	if (GetComputerNameA(buf, &len)) {
		hn = buf;
	} else {
		hn.clear();
	}
#else
# warning There is no way to retrieve the host name.
	hn = "(unknown)";
#endif
}

//////////////////////////////////////////////////////////////////////////
// Returns true iff terminal supports using colors in output.
static bool terminalSupportsColor() {
	bool term_supports_color = false;
#if defined(__WINDOWS__)
	// on Windows TERM variable is usually not set, but the console does
	// support colors.
	term_supports_color = true;
#else
	// On non-Windows platforms, we rely on the TERM variable.
	const char* const term = getenv("TERM");
	if (term != NULL && term[0] != '\0') {
		term_supports_color =
			!strcmp(term, "xterm") ||
			!strcmp(term, "xterm-color") ||
			!strcmp(term, "xterm-256color") ||
			!strcmp(term, "screen") ||
			!strcmp(term, "linux") ||
			!strcmp(term, "cygwin");
	}
#endif
	return term_supports_color;
}

#if defined(__WINDOWS__)
// Returns the character attribute for the given color.
WORD GetColorAttribute(LogColor color) {
	switch (color) {
	case COLOR_RED:    return FOREGROUND_RED;
	case COLOR_GREEN:  return FOREGROUND_GREEN;
	case COLOR_YELLOW: return FOREGROUND_RED | FOREGROUND_GREEN;
	default:           return 0;
	}
}
#else
// Returns the ANSI color code for the given color.
const char* GetAnsiColorCode(GLogColor color) {
	switch (color) {
	case COLOR_RED:     return "1";
	case COLOR_GREEN:   return "2";
	case COLOR_YELLOW:  return "3";
	case COLOR_DEFAULT:  return "";
	};
	return NULL; // stop warning about return type.
}
#endif  // __WINDOWS__
//////////////////////////////////////////////////////////////////////////
void coloredWriteToStderr(const CHAR* message, size_t len, LogColor color)
{
	// Avoid using cerr from this module since we may get called during
	// exit code, and cerr may be partially or fully destroyed by then.
	if (COLOR_DEFAULT == color) {
		fwrite(message, len, 1, stderr);
		return;
	}
#if defined(__WINDOWS__)
	const HANDLE stderr_handle = GetStdHandle(STD_ERROR_HANDLE);

	// Gets the current text color.
	CONSOLE_SCREEN_BUFFER_INFO buffer_info;
	GetConsoleScreenBufferInfo(stderr_handle, &buffer_info);
	const WORD old_color_attrs = buffer_info.wAttributes;

	// We need to flush the stream buffers into the console before each
	// SetConsoleTextAttribute call lest it affect the text that is already
	// printed but has not yet reached the console.
	fflush(stderr);
	SetConsoleTextAttribute(stderr_handle,
		GetColorAttribute(color) | FOREGROUND_INTENSITY);
	fwrite(message, len, 1, stderr);
	fflush(stderr);
	// Restores the text color.
	SetConsoleTextAttribute(stderr_handle, old_color_attrs);
#else
	fprintf(stderr, "\033[0;3%sm", GetAnsiColorCode(color));
	fwrite(message, len, 1, stderr);
	fprintf(stderr, "\033[m");  // Resets the terminal to default.
#endif  // __WINDOWS__
}
void clearStderrLineBuffer(FILE *file)
{
#if defined(__WINDOWS__)
	HANDLE stdIOHandle;
	COORD coor;
	CONSOLE_SCREEN_BUFFER_INFO info;

	stdIOHandle = (HANDLE)_get_osfhandle(fileno(file));
	if(stdIOHandle == INVALID_HANDLE_VALUE)
		return ;

	if(!GetConsoleScreenBufferInfo(stdIOHandle,&info))
		return ;

	coor = info.dwCursorPosition;
	if(coor.Y <= 0) return ;

	coor.X = 0;
	SetConsoleCursorPosition(stdIOHandle, coor);
#else
	fprintf(file, "\033[0;0H");
	fprintf(file, "\033[K");
#endif
}

//////////////////////////////////////////////////////////////////////////
uint32_t g_aCrc32Table[256] =
{
	0x00000000, 0x77073096, 0xEE0E612C, 0x990951BA,
	0x076DC419, 0x706AF48F, 0xE963A535, 0x9E6495A3,
	0x0EDB8832, 0x79DCB8A4, 0xE0D5E91E, 0x97D2D988,
	0x09B64C2B, 0x7EB17CBD, 0xE7B82D07, 0x90BF1D91,
	0x1DB71064, 0x6AB020F2, 0xF3B97148, 0x84BE41DE,
	0x1ADAD47D, 0x6DDDE4EB, 0xF4D4B551, 0x83D385C7,
	0x136C9856, 0x646BA8C0, 0xFD62F97A, 0x8A65C9EC,
	0x14015C4F, 0x63066CD9, 0xFA0F3D63, 0x8D080DF5,
	0x3B6E20C8, 0x4C69105E, 0xD56041E4, 0xA2677172,
	0x3C03E4D1, 0x4B04D447, 0xD20D85FD, 0xA50AB56B,
	0x35B5A8FA, 0x42B2986C, 0xDBBBC9D6, 0xACBCF940,
	0x32D86CE3, 0x45DF5C75, 0xDCD60DCF, 0xABD13D59,
	0x26D930AC, 0x51DE003A, 0xC8D75180, 0xBFD06116,
	0x21B4F4B5, 0x56B3C423, 0xCFBA9599, 0xB8BDA50F,
	0x2802B89E, 0x5F058808, 0xC60CD9B2, 0xB10BE924,
	0x2F6F7C87, 0x58684C11, 0xC1611DAB, 0xB6662D3D,

	0x76DC4190, 0x01DB7106, 0x98D220BC, 0xEFD5102A,
	0x71B18589, 0x06B6B51F, 0x9FBFE4A5, 0xE8B8D433,
	0x7807C9A2, 0x0F00F934, 0x9609A88E, 0xE10E9818,
	0x7F6A0DBB, 0x086D3D2D, 0x91646C97, 0xE6635C01,
	0x6B6B51F4, 0x1C6C6162, 0x856530D8, 0xF262004E,
	0x6C0695ED, 0x1B01A57B, 0x8208F4C1, 0xF50FC457,
	0x65B0D9C6, 0x12B7E950, 0x8BBEB8EA, 0xFCB9887C,
	0x62DD1DDF, 0x15DA2D49, 0x8CD37CF3, 0xFBD44C65,
	0x4DB26158, 0x3AB551CE, 0xA3BC0074, 0xD4BB30E2,
	0x4ADFA541, 0x3DD895D7, 0xA4D1C46D, 0xD3D6F4FB,
	0x4369E96A, 0x346ED9FC, 0xAD678846, 0xDA60B8D0,
	0x44042D73, 0x33031DE5, 0xAA0A4C5F, 0xDD0D7CC9,
	0x5005713C, 0x270241AA, 0xBE0B1010, 0xC90C2086,
	0x5768B525, 0x206F85B3, 0xB966D409, 0xCE61E49F,
	0x5EDEF90E, 0x29D9C998, 0xB0D09822, 0xC7D7A8B4,
	0x59B33D17, 0x2EB40D81, 0xB7BD5C3B, 0xC0BA6CAD,

	0xEDB88320, 0x9ABFB3B6, 0x03B6E20C, 0x74B1D29A,
	0xEAD54739, 0x9DD277AF, 0x04DB2615, 0x73DC1683,
	0xE3630B12, 0x94643B84, 0x0D6D6A3E, 0x7A6A5AA8,
	0xE40ECF0B, 0x9309FF9D, 0x0A00AE27, 0x7D079EB1,
	0xF00F9344, 0x8708A3D2, 0x1E01F268, 0x6906C2FE,
	0xF762575D, 0x806567CB, 0x196C3671, 0x6E6B06E7,
	0xFED41B76, 0x89D32BE0, 0x10DA7A5A, 0x67DD4ACC,
	0xF9B9DF6F, 0x8EBEEFF9, 0x17B7BE43, 0x60B08ED5,
	0xD6D6A3E8, 0xA1D1937E, 0x38D8C2C4, 0x4FDFF252,
	0xD1BB67F1, 0xA6BC5767, 0x3FB506DD, 0x48B2364B,
	0xD80D2BDA, 0xAF0A1B4C, 0x36034AF6, 0x41047A60,
	0xDF60EFC3, 0xA867DF55, 0x316E8EEF, 0x4669BE79,
	0xCB61B38C, 0xBC66831A, 0x256FD2A0, 0x5268E236,
	0xCC0C7795, 0xBB0B4703, 0x220216B9, 0x5505262F,
	0xC5BA3BBE, 0xB2BD0B28, 0x2BB45A92, 0x5CB36A04,
	0xC2D7FFA7, 0xB5D0CF31, 0x2CD99E8B, 0x5BDEAE1D,

	0x9B64C2B0, 0xEC63F226, 0x756AA39C, 0x026D930A,
	0x9C0906A9, 0xEB0E363F, 0x72076785, 0x05005713,
	0x95BF4A82, 0xE2B87A14, 0x7BB12BAE, 0x0CB61B38,
	0x92D28E9B, 0xE5D5BE0D, 0x7CDCEFB7, 0x0BDBDF21,
	0x86D3D2D4, 0xF1D4E242, 0x68DDB3F8, 0x1FDA836E,
	0x81BE16CD, 0xF6B9265B, 0x6FB077E1, 0x18B74777,
	0x88085AE6, 0xFF0F6A70, 0x66063BCA, 0x11010B5C,
	0x8F659EFF, 0xF862AE69, 0x616BFFD3, 0x166CCF45,
	0xA00AE278, 0xD70DD2EE, 0x4E048354, 0x3903B3C2,
	0xA7672661, 0xD06016F7, 0x4969474D, 0x3E6E77DB,
	0xAED16A4A, 0xD9D65ADC, 0x40DF0B66, 0x37D83BF0,
	0xA9BCAE53, 0xDEBB9EC5, 0x47B2CF7F, 0x30B5FFE9,
	0xBDBDF21C, 0xCABAC28A, 0x53B39330, 0x24B4A3A6,
	0xBAD03605, 0xCDD70693, 0x54DE5729, 0x23D967BF,
	0xB3667A2E, 0xC4614AB8, 0x5D681B02, 0x2A6F2B94,
	0xB40BBE37, 0xC30C8EA1, 0x5A05DF1B, 0x2D02EF8D,
};

uint32_t MyCRC( const CHAR* szString )
{
	if(szString==NULL || szString[0]==0) return 0;

	uint32_t dwCrc32 = 0xFFFFFFFF;
	int32_t nSize = (int32_t)strlen(szString);
	for(int32_t i=0; i<nSize; i++)
	{
		dwCrc32 = dwCrc32*33 + (UCHAR)szString[i] ;
//1		dwCrc32 = (dwCrc32>>8)^g_aCrc32Table[(szString[i])^((dwCrc32)&0x000000FF)]; // 1179716420
//2		dwCrc32 = (dwCrc32>>8)^g_aCrc32Table[(dwCrc32 & 0xFF) ^ szString[i]];  //1179716420
//3		dwCrc32 = (dwCrc32>>8)^g_aCrc32Table[(dwCrc32 ^ szString[i]) & 0xFF];  //1179716420
	}
//3	dwCrc32 = ((~dwCrc32)>> 16) & 0x7fff;
//2	dwCrc32 ^= 0xFFFFFFFF;  
	return dwCrc32;
}
uint32_t MyCRC32(const CHAR* lpData)
{
	if( !lpData ) return 0;
	uint32_t sum = 0;
	for (sum = 0; *lpData; )
	{
		/*
		* gcc 2.95.2 x86 and icc 7.1.006 compile
		* that operator into the single "rol" opcode,
		* msvc 6.0sp2 compiles it into four opcodes.
		*/
		sum =	sum >> 1 | sum << 31;
		sum += *lpData++;
	}
	return sum;
}
//////////////////////////////////////////////////////////////////////////
CHAR Value2Ascii(CHAR in)
{
	__ENTER_FUNCTION
		switch(in) 
		{
			case 0:
				return '0';
				break;
			case 1:
				return '1';
			case 2:
				return '2';
				break;
			case 3:
				return '3';
				break;
			case 4:
				return '4';
				break;
			case 5:
				return '5';
				break;
			case 6:
				return '6';
				break;
			case 7:
				return '7';
				break;
			case 8:
				return '8';
				break;
			case 9:
				return '9';
				break;
			case 10:
				return 'A';
				break;
			case 11:
				return 'B';
				break;
			case 12:
				return 'C';
				break;
			case 13:
				return 'D';
				break;
			case 14:
				return 'E';
				break;
			case 15:
				return 'F';
				break;
			default:
				Assert(false);
				return '?';
				break;
		}

	__LEAVE_FUNCTION

		return '?';
}
CHAR Ascii2Value(CHAR in)
{
	__ENTER_FUNCTION
		switch(in) 
	{
		case '0':
			return 0;
			break;
		case '1':
			return 1;
		case '2':
			return 2;
			break;
		case '3':
			return 3;
			break;
		case '4':
			return 4;
			break;
		case '5':
			return 5;
			break;
		case '6':
			return 6;
			break;
		case '7':
			return 7;
			break;
		case '8':
			return 8;
			break;
		case '9':
			return 9;
			break;
		case 'A':
			return 10;
			break;
		case 'B':
			return 11;
			break;
		case 'C':
			return 12;
			break;
		case 'D':
			return 13;
			break;
		case 'E':
			return 14;
			break;
		case 'F':
			return 15;
			break;
		default:
			Assert(false);
			return '?';
			break;
	}

	__LEAVE_FUNCTION

		return '?';
}
//////////////////////////////////////////////////////////////////////////
bool Binary2String(const CHAR* pIn,uint32_t InLength,CHAR* pOut)
{
	__ENTER_FUNCTION

		if(InLength==0)
		{
			return false;
		}
		uint32_t iOut = 0;

		
		for(uint32_t i = 0 ;i<InLength;i++)
		{
			
			pOut[iOut] = Value2Ascii(((unsigned char)pIn[i]&0xF0)>>4);
			iOut++;
			pOut[iOut] = Value2Ascii(pIn[i]&0x0F);
			iOut++;
		

		}
		return true;

		__LEAVE_FUNCTION

			return false;
}
bool DBStr2Binary(const CHAR* pIn,uint32_t InLength,CHAR* pOut,uint32_t OutLimit,uint32_t& OutLength)
{
	__ENTER_FUNCTION

		if(InLength==0)
		{
			return false;
		}

		uint32_t iOut = 0;
		uint32_t i;
		for( i = 0 ;i<InLength-1;)
		{
			if(pIn[i]=='\0'||pIn[i+1]=='\0')
			{
				break;
			}
			
			pOut[iOut]	=	(Ascii2Value(pIn[i])<<4) + Ascii2Value(pIn[i+1]);
			iOut++;
			i+=2;
			if(iOut>=OutLimit)
				break;
		}
		OutLength = iOut;
		return true;
		__LEAVE_FUNCTION
		return false;
}
bool String2Binary(const CHAR* pIn,uint32_t InLength,CHAR* pOut,uint32_t OutLimit,uint32_t& OutLength)
{
	__ENTER_FUNCTION

		if(InLength==0)
		{
			return false;
		}

		uint32_t iOut = 0;
		uint32_t i;
		for( i = 0 ;i<InLength-1;)
		{
			if((pIn[i]=='\\') && (pIn[i+1]=='0'))
			{
				pOut[iOut]	=	'\0';
				iOut++;
				i+=2;
				continue;
			}
			else if((pIn[i]=='\'') && (pIn[i+1]=='\''))
			{
			pOut[iOut]	=	'\'';
			iOut++;
			i+=2;
			continue;
			}
			else if((pIn[i]=='\\') && (pIn[i+1]=='\"'))
			{
				pOut[iOut]	=	'\"';
				iOut++;
				i+=2;
				continue;
			}
			else if((pIn[i]=='\\') && (pIn[i+1]=='\\'))
			{
				pOut[iOut]	=	'\\';
				iOut++;
				i+=2;
				continue;
			}
			else if(pIn[i]=='\0')
			{
				break;
			}

			pOut[iOut] = pIn[i];
			iOut++;
			i++;

			if(iOut>=OutLimit)
				break;
		}
		OutLength = iOut;
		return true;

		__LEAVE_FUNCTION
			return false;
}
bool StrSafeCheck(const CHAR* pIn,uint32_t InLength)
{
	if(InLength==0)
	{
		return false;
	}
	for(uint32_t i = 0 ;i<InLength;i++)
	{
		switch(pIn[i]) 
		{
			case '\0':
				{
					return true;
					break;
				}
			case '\'':
			case '\"':
			case ')':
			case '(':
			case '=':
			case '%':
				{
					return false;
				}
		}
	}

	return true;

}
bool CommandSafeCheck(const CHAR* pIn,uint32_t InLength)
{
	if(InLength==0)
	{
		return false;
	}
	for(uint32_t i = 0 ;i<InLength;i++)
	{
		switch(pIn[i]) 
		{
		case '\0':
			{
				return true;
				break;
			}
		case '%':
			{
				return false;
			}
		}
	}

	return true;

}
//////////////////////////////////////////////////////////////////////////
CHAR* ReplaceIllegalString( CHAR* strText, int32_t nLength, int32_t nLevel )
{
	if( strText == NULL ) return NULL;
	int32_t i;
	for( i = 0; i < nLength; i ++ )
	{
		if( strText[i] == '%' ) strText[i] = '?';
		if( strText[i] == '\0' ) break;
	}

	return strText;
}
bool CheckIllegalString( const CHAR* strText, int32_t nLength, int32_t nLevel )
{
	if( strText == NULL ) return false;
	int32_t i;
	if( nLevel == CHECK_STRING_NORMAL )
	{
		for( i = 0; i < nLength; i ++ )
		{
			if( strText[i] == '%' ) return true;
			if( strText[i] == '\0' ) return false;
		}
	}
	else if( nLevel == CHECK_STRING_CHARNAME )
	{
		for( i = 0; i < nLength; i ++ )
		{
			switch( strText[i] )
			{
			case ' ':
			case '#':
			case '\\':
			case '/':
			case '`':
			case '~':
			case '!':
			case '@':
			case '$':
			case '%':
			case '^':
			case '&':
			case '*':
			case '(':
			case ')':
			case '-':
			case '_':
			case '+':
			case '|':
			case '{':
			case '}':
			case '[':
			case ']':
			case ';':
			case ':':
			case '\'':
			case '\"':
			case '<':
			case '>':
			case ',':
			case '.':
			case '?':
			case '0xA1':
				return true;
			}
			if( strText[i] == '\0' ) return false;
		}
	}
	return false;
}
//////////////////////////////////////////////////////////////////////////
bool	IsPow2(int32_t val) 
{ 
	return !(val & (val-1)); 
}

int32_t	AlignN(int32_t val, int32_t _algin)  
{ 
	return ((val + _algin - 1) & ~(_algin - 1)); 
}

int32_t	NextPow2(int32_t val)
{
	if( val > 1 )
	{
		if(!IsPow2(val))
		{
			val |= val  >> 1;
			val |= val  >> 2;
			val |= val  >> 4;
			val |= val  >> 8;
			val |= val  >> 16;
			val = val + 1;
		}
	}
	else
	{
		val = 2;
	}

	return val;
}
//////////////////////////////////////////////////////////////////////////

RandInt32::RandInt32(uint32_t seed)
{
	if( seed != 0 )
	{
		m_Seed = seed;
	}
	else
	{
		m_Seed = (uint32_t)time(NULL);
	}
}

int32_t RandInt32::Gen( )
{
	int32_t ret;
	ret = (((m_Seed = m_Seed * 1103515245 + 12345) >> 1 ) & INT32_MAX);
	return ret;
}

int32_t RandInt32::GenRange(int32_t low, int32_t high)
{
	int32_t ret = low;
	if(low <  high)
	{
		ret = (((m_Seed = m_Seed * 1103515245 + 12345) >> 1 ) & INT32_MAX);
		ret = (ret % (high - low + 1))+low;
	}
	return ret;
}

