#include "BaseLib.h"
#include "Config.h"
#include "ExceptionHandler.h"
#include <signal.h>
#if defined(__WINDOWS__)
#include <process.h>
#include "SimpleSymbolEngine.h"
#include "SimpleSymbolEngine.cpp"
#elif defined(__LINUX__)
#include <execinfo.h>
#include <sys/types.h>
#endif

class SignalInstallType
{
public:
	enum
	{
		INVALID = 0,
		DEFAULT,
		IGNORE_,
		CUSTOM,
	};
};

class SignalHandleType
{
public:
	enum 
	{
		INVALID = 0,
		HOLD,
		RERAISE,
	};
};

struct SignalDesc
{
	int32 nID;
	CHAR  szID[32];
	int32 nInstall;
	int32 nHandle;
};

static SignalDesc s_SignalDesc [] = 
{
#if defined(__LINUX__)
	//POSIX.1-1990
	{SIGHUP,	"SIGHUP", SignalInstallType::CUSTOM, SignalHandleType::HOLD},
	{SIGINT,	"SIGINT", SignalInstallType::CUSTOM, SignalHandleType::HOLD},
	{SIGQUIT,	"SIGQUIT", SignalInstallType::CUSTOM, SignalHandleType::RERAISE},
	{SIGILL,	"SIGILL", SignalInstallType::CUSTOM, SignalHandleType::RERAISE},
	{SIGABRT,	"SIGABRT", SignalInstallType::CUSTOM, SignalHandleType::RERAISE},
	{SIGFPE,	"SIGFPE", SignalInstallType::CUSTOM, SignalHandleType::HOLD},
	{SIGKILL,	"SIGKILL", SignalInstallType::INVALID, SignalHandleType::INVALID},
	{SIGSEGV,	"SIGSEGV", SignalInstallType::CUSTOM, SignalHandleType::RERAISE},
	{SIGPIPE,	"SIGPIPE", SignalInstallType::CUSTOM, SignalHandleType::HOLD},
	{SIGALRM,	"SIGALRM", SignalInstallType::CUSTOM, SignalHandleType::HOLD},
	{SIGTERM,	"SIGTERM", SignalInstallType::CUSTOM, SignalHandleType::HOLD},
	{SIGUSR1,	"SIGUSR1", SignalInstallType::CUSTOM, SignalHandleType::HOLD},
	{SIGUSR2,	"SIGUSR2", SignalInstallType::CUSTOM, SignalHandleType::HOLD},
	{SIGCHLD,	"SIGCHLD", SignalInstallType::CUSTOM, SignalHandleType::HOLD},
	{SIGCONT,	"SIGCONT", SignalInstallType::INVALID, SignalHandleType::INVALID},
	{SIGSTOP,	"SIGSTOP", SignalInstallType::INVALID, SignalHandleType::INVALID},
	{SIGTSTP,	"SIGTSTP", SignalInstallType::CUSTOM, SignalHandleType::HOLD},
	{SIGTTIN,	"SIGTTIN", SignalInstallType::CUSTOM, SignalHandleType::HOLD},
	{SIGTTOU,	"SIGTTOU", SignalInstallType::CUSTOM, SignalHandleType::HOLD},
	{SIGPIPE,	"SIGPIPE", SignalInstallType::CUSTOM, SignalHandleType::HOLD},

	//SUSc2 and POSIX.1-2001
	{SIGBUS,	"SIGBUS", SignalInstallType::CUSTOM, SignalHandleType::RERAISE},
	{SIGPROF,	"SIGPROF", SignalInstallType::CUSTOM, SignalHandleType::HOLD},
	{SIGSYS,	"SIGSYS", SignalInstallType::CUSTOM, SignalHandleType::RERAISE},
	{SIGTRAP,	"SIGTRAP", SignalInstallType::CUSTOM, SignalHandleType::RERAISE},
	{SIGURG,	"SIGURG", SignalInstallType::CUSTOM, SignalHandleType::HOLD},
	{SIGVTALRM,	"SIGVTALRM", SignalInstallType::CUSTOM, SignalHandleType::HOLD},
	{SIGXCPU,	"SIGXCPU", SignalInstallType::CUSTOM, SignalHandleType::HOLD},
	{SIGXFSZ,	"SIGXFSZ", SignalInstallType::CUSTOM, SignalHandleType::HOLD},

	//others
	{SIGSTKFLT,	"SIGSTKFLT",	SignalInstallType::CUSTOM, SignalHandleType::HOLD},
	{SIGIO,		"SIGIO",		SignalInstallType::CUSTOM, SignalHandleType::HOLD},
	{SIGPWR,	"SIGPWR",		SignalInstallType::CUSTOM, SignalHandleType::HOLD},
	{SIGWINCH,	"SIGWINCH",		SignalInstallType::CUSTOM, SignalHandleType::HOLD},

#elif defined(__WINDOWS__)
	{SIGINT,	"SIGINT", SignalInstallType::CUSTOM, SignalHandleType::HOLD},
	{SIGILL,	"SIGILL", SignalInstallType::CUSTOM, SignalHandleType::RERAISE},
	{SIGABRT,	"SIGABRT", SignalInstallType::CUSTOM, SignalHandleType::RERAISE},
	{SIGFPE,	"SIGFPE", SignalInstallType::CUSTOM, SignalHandleType::HOLD},
	{SIGSEGV,	"SIGSEGV", SignalInstallType::CUSTOM, SignalHandleType::RERAISE},
	{SIGTERM,	"SIGTERM", SignalInstallType::CUSTOM, SignalHandleType::HOLD},
#endif
};

void SignalHandler(int32_t sig);

void SignalInstall( int32 nSig, int installType, void(*Func)(int32))
{
	switch (installType)
	{
	case SignalInstallType::INVALID:
		break;
	case SignalInstallType::CUSTOM:
		signal(nSig, Func);
		break;
	case SignalInstallType::DEFAULT:
		signal(nSig, SIG_DFL);
		break;
	case SignalInstallType::IGNORE_:
		signal(nSig, SIG_IGN);
		break;
	default:
		break;
	}
}



ExceptionHandler::ExceptionHandler()
{
	int32 sigCount = sizeof(s_SignalDesc) / sizeof(SignalDesc);
	for(int32 i = 0; i < sigCount; i++)
	{
		SignalInstall(s_SignalDesc[i].nID, s_SignalDesc[i].nInstall, SignalHandler);
	}
}


void DumpStack(std::ostream& os)
{
#if defined( __LINUX__)
	const int len = 200;
	void* buffer[len];
	int nptrs = ::backtrace(buffer, len);
	char** strings = ::backtrace_symbols(buffer, nptrs);
	if (strings)
	{
		for (int i = 0; i < nptrs; ++i)
		{
			os << strings[i] << "\r\n";
		}
		free(strings);
	}
#elif defined(__WINDOWS__)
	CONTEXT context = {CONTEXT_FULL};
	::GetThreadContext( GetCurrentThread(), &context );
	SimpleSymbolEngine::instance().StackTrace( &context, os );
#endif
}

void WriteDumpLog(const CHAR* szMsg, int32_t len)
{
#define FILE_NAME_LEN (128)
	char logfileName[FILE_NAME_LEN] = {0};
	char curTime[DATETIME_LEN] = {0};

	TimeUtil::Format(curTime, DATETIME_LEN, "%Y%m%d-%H%M%S");
	tsnprintf(logfileName, FILE_NAME_LEN, "%s.%d.%s.log",  
		"dump", getpid(), curTime);

	CHAR filePath[_MAX_PATH] = {0};
	tsnprintf(filePath, _MAX_PATH, "Runtime/Log/%s", logfileName);

#undef FILE_NAME_LEN

	try
	{
		FILE *fp = fopen(filePath, "a+");
		if( fp != NULL )
		{
			fwrite(szMsg, 1, len, fp);
			fclose(fp);
		}
	}
	catch(...)
	{

	}
}

void SignalHandler(int32_t nSig)
{
	int32 indexOfSig = -1;
	int32 sigCount = sizeof(s_SignalDesc) / sizeof(SignalDesc);
	for(int32 i = 0; i < sigCount; i++)
	{
		if(s_SignalDesc[i].nID == nSig)
		{
			indexOfSig = i;
			break;
		}
	}

	FLString<8192> StackInfo;
	std::stringstream ss;
	if( indexOfSig >= 0 && indexOfSig< sigCount)
	{
		switch (s_SignalDesc[indexOfSig].nHandle)
		{
		case SignalHandleType::HOLD:
			{
				StackInfo.Clear();
				StackInfo += "Hold signal ";
				StackInfo += nSig;
				StackInfo += "(";
				StackInfo += s_SignalDesc[indexOfSig].szID;
				StackInfo += ")\r\n";
				DumpStack(ss);
				StackInfo += ss.str().c_str();
				WriteDumpLog(StackInfo.GetStr(), StackInfo.GetLength());
			}
			break;
		case SignalHandleType::RERAISE:
			{
				StackInfo.Clear();
				StackInfo += "Re raise signal ";
				StackInfo += nSig;
				StackInfo += "(";
				StackInfo += s_SignalDesc[indexOfSig].szID;
				StackInfo += ")\r\n";
				DumpStack(ss);
				StackInfo += ss.str().c_str();
				WriteDumpLog(StackInfo.GetStr(), StackInfo.GetLength());
				SignalInstall(s_SignalDesc[indexOfSig].nID, SignalInstallType::DEFAULT, NULL);
				raise(s_SignalDesc[indexOfSig].nID);
			}
			break;
		default:
			break;
		}
	}
	else
	{
		StackInfo.Clear();
		StackInfo += "dump signal=";
		StackInfo += nSig;
		StackInfo += "\r\n";
		DumpStack(ss);
		StackInfo += ss.str().c_str();
		WriteDumpLog(StackInfo.GetStr(), StackInfo.GetLength());
	}
}

ExceptionHandler g_ExceptionHandler;
