// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: PBMessage.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "PBMessage.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace {

const ::google::protobuf::Descriptor* CG_LOGIN_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  CG_LOGIN_reflection_ = NULL;
const ::google::protobuf::EnumDescriptor* CG_LOGIN_VALIDATETYPE_descriptor_ = NULL;

}  // namespace


void protobuf_AssignDesc_PBMessage_2eproto() {
  protobuf_AddDesc_PBMessage_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "PBMessage.proto");
  GOOGLE_CHECK(file != NULL);
  CG_LOGIN_descriptor_ = file->message_type(0);
  static const int CG_LOGIN_offsets_[9] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(CG_LOGIN, vtype_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(CG_LOGIN, gameversion_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(CG_LOGIN, programversion_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(CG_LOGIN, publicresourceversion_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(CG_LOGIN, maxpacketid_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(CG_LOGIN, forceenter_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(CG_LOGIN, deviceid_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(CG_LOGIN, devicetype_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(CG_LOGIN, deviceversion_),
  };
  CG_LOGIN_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      CG_LOGIN_descriptor_,
      CG_LOGIN::default_instance_,
      CG_LOGIN_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(CG_LOGIN, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(CG_LOGIN, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(CG_LOGIN));
  CG_LOGIN_VALIDATETYPE_descriptor_ = CG_LOGIN_descriptor_->enum_type(0);
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_PBMessage_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    CG_LOGIN_descriptor_, &CG_LOGIN::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_PBMessage_2eproto() {
  delete CG_LOGIN::default_instance_;
  delete CG_LOGIN_reflection_;
}

void protobuf_AddDesc_PBMessage_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\017PBMessage.proto\"\357\001\n\010CG_LOGIN\022\r\n\005vtype\030"
    "\001 \002(\005\022\023\n\013gameversion\030\002 \002(\005\022\026\n\016programver"
    "sion\030\003 \002(\005\022\035\n\025publicresourceversion\030\004 \002("
    "\005\022\023\n\013maxpacketid\030\005 \002(\005\022\022\n\nforceenter\030\006 \002"
    "(\005\022\020\n\010deviceid\030\007 \002(\t\022\022\n\ndevicetype\030\010 \002(\t"
    "\022\025\n\rdeviceversion\030\t \002(\t\"\"\n\014VALIDATETYPE\022"
    "\010\n\004TEST\020\000\022\010\n\004CYOU\020\001", 259);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "PBMessage.proto", &protobuf_RegisterTypes);
  CG_LOGIN::default_instance_ = new CG_LOGIN();
  CG_LOGIN::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_PBMessage_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_PBMessage_2eproto {
  StaticDescriptorInitializer_PBMessage_2eproto() {
    protobuf_AddDesc_PBMessage_2eproto();
  }
} static_descriptor_initializer_PBMessage_2eproto_;

// ===================================================================

const ::google::protobuf::EnumDescriptor* CG_LOGIN_VALIDATETYPE_descriptor() {
  protobuf_AssignDescriptorsOnce();
  return CG_LOGIN_VALIDATETYPE_descriptor_;
}
bool CG_LOGIN_VALIDATETYPE_IsValid(int value) {
  switch(value) {
    case 0:
    case 1:
      return true;
    default:
      return false;
  }
}

#ifndef _MSC_VER
const CG_LOGIN_VALIDATETYPE CG_LOGIN::TEST;
const CG_LOGIN_VALIDATETYPE CG_LOGIN::CYOU;
const CG_LOGIN_VALIDATETYPE CG_LOGIN::VALIDATETYPE_MIN;
const CG_LOGIN_VALIDATETYPE CG_LOGIN::VALIDATETYPE_MAX;
const int CG_LOGIN::VALIDATETYPE_ARRAYSIZE;
#endif  // _MSC_VER
#ifndef _MSC_VER
const int CG_LOGIN::kVtypeFieldNumber;
const int CG_LOGIN::kGameversionFieldNumber;
const int CG_LOGIN::kProgramversionFieldNumber;
const int CG_LOGIN::kPublicresourceversionFieldNumber;
const int CG_LOGIN::kMaxpacketidFieldNumber;
const int CG_LOGIN::kForceenterFieldNumber;
const int CG_LOGIN::kDeviceidFieldNumber;
const int CG_LOGIN::kDevicetypeFieldNumber;
const int CG_LOGIN::kDeviceversionFieldNumber;
#endif  // !_MSC_VER

CG_LOGIN::CG_LOGIN()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:CG_LOGIN)
}

void CG_LOGIN::InitAsDefaultInstance() {
}

CG_LOGIN::CG_LOGIN(const CG_LOGIN& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:CG_LOGIN)
}

void CG_LOGIN::SharedCtor() {
  ::google::protobuf::internal::GetEmptyString();
  _cached_size_ = 0;
  vtype_ = 0;
  gameversion_ = 0;
  programversion_ = 0;
  publicresourceversion_ = 0;
  maxpacketid_ = 0;
  forceenter_ = 0;
  deviceid_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  devicetype_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  deviceversion_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

CG_LOGIN::~CG_LOGIN() {
  // @@protoc_insertion_point(destructor:CG_LOGIN)
  SharedDtor();
}

void CG_LOGIN::SharedDtor() {
  if (deviceid_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete deviceid_;
  }
  if (devicetype_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete devicetype_;
  }
  if (deviceversion_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete deviceversion_;
  }
  if (this != default_instance_) {
  }
}

void CG_LOGIN::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* CG_LOGIN::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return CG_LOGIN_descriptor_;
}

const CG_LOGIN& CG_LOGIN::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_PBMessage_2eproto();
  return *default_instance_;
}

CG_LOGIN* CG_LOGIN::default_instance_ = NULL;

CG_LOGIN* CG_LOGIN::New() const {
  return new CG_LOGIN;
}

void CG_LOGIN::Clear() {
#define OFFSET_OF_FIELD_(f) (reinterpret_cast<char*>(      \
  &reinterpret_cast<CG_LOGIN*>(16)->f) - \
   reinterpret_cast<char*>(16))

#define ZR_(first, last) do {                              \
    size_t f = OFFSET_OF_FIELD_(first);                    \
    size_t n = OFFSET_OF_FIELD_(last) - f + sizeof(last);  \
    ::memset(&first, 0, n);                                \
  } while (0)

  if (_has_bits_[0 / 32] & 255) {
    ZR_(vtype_, forceenter_);
    if (has_deviceid()) {
      if (deviceid_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
        deviceid_->clear();
      }
    }
    if (has_devicetype()) {
      if (devicetype_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
        devicetype_->clear();
      }
    }
  }
  if (has_deviceversion()) {
    if (deviceversion_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
      deviceversion_->clear();
    }
  }

#undef OFFSET_OF_FIELD_
#undef ZR_

  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool CG_LOGIN::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:CG_LOGIN)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required int32 vtype = 1;
      case 1: {
        if (tag == 8) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &vtype_)));
          set_has_vtype();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(16)) goto parse_gameversion;
        break;
      }

      // required int32 gameversion = 2;
      case 2: {
        if (tag == 16) {
         parse_gameversion:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &gameversion_)));
          set_has_gameversion();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(24)) goto parse_programversion;
        break;
      }

      // required int32 programversion = 3;
      case 3: {
        if (tag == 24) {
         parse_programversion:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &programversion_)));
          set_has_programversion();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(32)) goto parse_publicresourceversion;
        break;
      }

      // required int32 publicresourceversion = 4;
      case 4: {
        if (tag == 32) {
         parse_publicresourceversion:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &publicresourceversion_)));
          set_has_publicresourceversion();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(40)) goto parse_maxpacketid;
        break;
      }

      // required int32 maxpacketid = 5;
      case 5: {
        if (tag == 40) {
         parse_maxpacketid:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &maxpacketid_)));
          set_has_maxpacketid();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(48)) goto parse_forceenter;
        break;
      }

      // required int32 forceenter = 6;
      case 6: {
        if (tag == 48) {
         parse_forceenter:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &forceenter_)));
          set_has_forceenter();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(58)) goto parse_deviceid;
        break;
      }

      // required string deviceid = 7;
      case 7: {
        if (tag == 58) {
         parse_deviceid:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_deviceid()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->deviceid().data(), this->deviceid().length(),
            ::google::protobuf::internal::WireFormat::PARSE,
            "deviceid");
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(66)) goto parse_devicetype;
        break;
      }

      // required string devicetype = 8;
      case 8: {
        if (tag == 66) {
         parse_devicetype:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_devicetype()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->devicetype().data(), this->devicetype().length(),
            ::google::protobuf::internal::WireFormat::PARSE,
            "devicetype");
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(74)) goto parse_deviceversion;
        break;
      }

      // required string deviceversion = 9;
      case 9: {
        if (tag == 74) {
         parse_deviceversion:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_deviceversion()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->deviceversion().data(), this->deviceversion().length(),
            ::google::protobuf::internal::WireFormat::PARSE,
            "deviceversion");
        } else {
          goto handle_unusual;
        }
        if (input->ExpectAtEnd()) goto success;
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0 ||
            ::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:CG_LOGIN)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:CG_LOGIN)
  return false;
#undef DO_
}

void CG_LOGIN::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:CG_LOGIN)
  // required int32 vtype = 1;
  if (has_vtype()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(1, this->vtype(), output);
  }

  // required int32 gameversion = 2;
  if (has_gameversion()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(2, this->gameversion(), output);
  }

  // required int32 programversion = 3;
  if (has_programversion()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(3, this->programversion(), output);
  }

  // required int32 publicresourceversion = 4;
  if (has_publicresourceversion()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(4, this->publicresourceversion(), output);
  }

  // required int32 maxpacketid = 5;
  if (has_maxpacketid()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(5, this->maxpacketid(), output);
  }

  // required int32 forceenter = 6;
  if (has_forceenter()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(6, this->forceenter(), output);
  }

  // required string deviceid = 7;
  if (has_deviceid()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->deviceid().data(), this->deviceid().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "deviceid");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      7, this->deviceid(), output);
  }

  // required string devicetype = 8;
  if (has_devicetype()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->devicetype().data(), this->devicetype().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "devicetype");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      8, this->devicetype(), output);
  }

  // required string deviceversion = 9;
  if (has_deviceversion()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->deviceversion().data(), this->deviceversion().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "deviceversion");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      9, this->deviceversion(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:CG_LOGIN)
}

::google::protobuf::uint8* CG_LOGIN::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:CG_LOGIN)
  // required int32 vtype = 1;
  if (has_vtype()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(1, this->vtype(), target);
  }

  // required int32 gameversion = 2;
  if (has_gameversion()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(2, this->gameversion(), target);
  }

  // required int32 programversion = 3;
  if (has_programversion()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(3, this->programversion(), target);
  }

  // required int32 publicresourceversion = 4;
  if (has_publicresourceversion()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(4, this->publicresourceversion(), target);
  }

  // required int32 maxpacketid = 5;
  if (has_maxpacketid()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(5, this->maxpacketid(), target);
  }

  // required int32 forceenter = 6;
  if (has_forceenter()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(6, this->forceenter(), target);
  }

  // required string deviceid = 7;
  if (has_deviceid()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->deviceid().data(), this->deviceid().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "deviceid");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        7, this->deviceid(), target);
  }

  // required string devicetype = 8;
  if (has_devicetype()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->devicetype().data(), this->devicetype().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "devicetype");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        8, this->devicetype(), target);
  }

  // required string deviceversion = 9;
  if (has_deviceversion()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->deviceversion().data(), this->deviceversion().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "deviceversion");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        9, this->deviceversion(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:CG_LOGIN)
  return target;
}

int CG_LOGIN::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required int32 vtype = 1;
    if (has_vtype()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->vtype());
    }

    // required int32 gameversion = 2;
    if (has_gameversion()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->gameversion());
    }

    // required int32 programversion = 3;
    if (has_programversion()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->programversion());
    }

    // required int32 publicresourceversion = 4;
    if (has_publicresourceversion()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->publicresourceversion());
    }

    // required int32 maxpacketid = 5;
    if (has_maxpacketid()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->maxpacketid());
    }

    // required int32 forceenter = 6;
    if (has_forceenter()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->forceenter());
    }

    // required string deviceid = 7;
    if (has_deviceid()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->deviceid());
    }

    // required string devicetype = 8;
    if (has_devicetype()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->devicetype());
    }

  }
  if (_has_bits_[8 / 32] & (0xffu << (8 % 32))) {
    // required string deviceversion = 9;
    if (has_deviceversion()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->deviceversion());
    }

  }
  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void CG_LOGIN::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const CG_LOGIN* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const CG_LOGIN*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void CG_LOGIN::MergeFrom(const CG_LOGIN& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_vtype()) {
      set_vtype(from.vtype());
    }
    if (from.has_gameversion()) {
      set_gameversion(from.gameversion());
    }
    if (from.has_programversion()) {
      set_programversion(from.programversion());
    }
    if (from.has_publicresourceversion()) {
      set_publicresourceversion(from.publicresourceversion());
    }
    if (from.has_maxpacketid()) {
      set_maxpacketid(from.maxpacketid());
    }
    if (from.has_forceenter()) {
      set_forceenter(from.forceenter());
    }
    if (from.has_deviceid()) {
      set_deviceid(from.deviceid());
    }
    if (from.has_devicetype()) {
      set_devicetype(from.devicetype());
    }
  }
  if (from._has_bits_[8 / 32] & (0xffu << (8 % 32))) {
    if (from.has_deviceversion()) {
      set_deviceversion(from.deviceversion());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void CG_LOGIN::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void CG_LOGIN::CopyFrom(const CG_LOGIN& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool CG_LOGIN::IsInitialized() const {
  if ((_has_bits_[0] & 0x000001ff) != 0x000001ff) return false;

  return true;
}

void CG_LOGIN::Swap(CG_LOGIN* other) {
  if (other != this) {
    std::swap(vtype_, other->vtype_);
    std::swap(gameversion_, other->gameversion_);
    std::swap(programversion_, other->programversion_);
    std::swap(publicresourceversion_, other->publicresourceversion_);
    std::swap(maxpacketid_, other->maxpacketid_);
    std::swap(forceenter_, other->forceenter_);
    std::swap(deviceid_, other->deviceid_);
    std::swap(devicetype_, other->devicetype_);
    std::swap(deviceversion_, other->deviceversion_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata CG_LOGIN::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = CG_LOGIN_descriptor_;
  metadata.reflection = CG_LOGIN_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

// @@protoc_insertion_point(global_scope)