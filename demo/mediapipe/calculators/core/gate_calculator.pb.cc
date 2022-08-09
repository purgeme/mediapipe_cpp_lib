// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: mediapipe/calculators/core/gate_calculator.proto

#include "mediapipe/calculators/core/gate_calculator.pb.h"

#include <algorithm>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>

PROTOBUF_PRAGMA_INIT_SEG
namespace mediapipe {
constexpr GateCalculatorOptions::GateCalculatorOptions(
  ::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized)
  : empty_packets_as_allow_(false)
  , allow_(false){}
struct GateCalculatorOptionsDefaultTypeInternal {
  constexpr GateCalculatorOptionsDefaultTypeInternal()
    : _instance(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized{}) {}
  ~GateCalculatorOptionsDefaultTypeInternal() {}
  union {
    GateCalculatorOptions _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT GateCalculatorOptionsDefaultTypeInternal _GateCalculatorOptions_default_instance_;
}  // namespace mediapipe
static ::PROTOBUF_NAMESPACE_ID::Metadata file_level_metadata_mediapipe_2fcalculators_2fcore_2fgate_5fcalculator_2eproto[1];
static constexpr ::PROTOBUF_NAMESPACE_ID::EnumDescriptor const** file_level_enum_descriptors_mediapipe_2fcalculators_2fcore_2fgate_5fcalculator_2eproto = nullptr;
static constexpr ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor const** file_level_service_descriptors_mediapipe_2fcalculators_2fcore_2fgate_5fcalculator_2eproto = nullptr;

const uint32_t TableStruct_mediapipe_2fcalculators_2fcore_2fgate_5fcalculator_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  PROTOBUF_FIELD_OFFSET(::mediapipe::GateCalculatorOptions, _has_bits_),
  PROTOBUF_FIELD_OFFSET(::mediapipe::GateCalculatorOptions, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::mediapipe::GateCalculatorOptions, empty_packets_as_allow_),
  PROTOBUF_FIELD_OFFSET(::mediapipe::GateCalculatorOptions, allow_),
  0,
  1,
};
static const ::PROTOBUF_NAMESPACE_ID::internal::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, 8, -1, sizeof(::mediapipe::GateCalculatorOptions)},
};

static ::PROTOBUF_NAMESPACE_ID::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::mediapipe::_GateCalculatorOptions_default_instance_),
};

const char descriptor_table_protodef_mediapipe_2fcalculators_2fcore_2fgate_5fcalculator_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n0mediapipe/calculators/core/gate_calcul"
  "ator.proto\022\tmediapipe\032$mediapipe/framewo"
  "rk/calculator.proto\"\235\001\n\025GateCalculatorOp"
  "tions\022\036\n\026empty_packets_as_allow\030\001 \001(\010\022\024\n"
  "\005allow\030\002 \001(\010:\005false2N\n\003ext\022\034.mediapipe.C"
  "alculatorOptions\030\337\237\350| \001(\0132 .mediapipe.Ga"
  "teCalculatorOptionsB\014\242\002\tMediaPipe"
  ;
static const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable*const descriptor_table_mediapipe_2fcalculators_2fcore_2fgate_5fcalculator_2eproto_deps[1] = {
  &::descriptor_table_mediapipe_2fframework_2fcalculator_2eproto,
};
static ::PROTOBUF_NAMESPACE_ID::internal::once_flag descriptor_table_mediapipe_2fcalculators_2fcore_2fgate_5fcalculator_2eproto_once;
const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_mediapipe_2fcalculators_2fcore_2fgate_5fcalculator_2eproto = {
  false, false, 273, descriptor_table_protodef_mediapipe_2fcalculators_2fcore_2fgate_5fcalculator_2eproto, "mediapipe/calculators/core/gate_calculator.proto", 
  &descriptor_table_mediapipe_2fcalculators_2fcore_2fgate_5fcalculator_2eproto_once, descriptor_table_mediapipe_2fcalculators_2fcore_2fgate_5fcalculator_2eproto_deps, 1, 1,
  schemas, file_default_instances, TableStruct_mediapipe_2fcalculators_2fcore_2fgate_5fcalculator_2eproto::offsets,
  file_level_metadata_mediapipe_2fcalculators_2fcore_2fgate_5fcalculator_2eproto, file_level_enum_descriptors_mediapipe_2fcalculators_2fcore_2fgate_5fcalculator_2eproto, file_level_service_descriptors_mediapipe_2fcalculators_2fcore_2fgate_5fcalculator_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable* descriptor_table_mediapipe_2fcalculators_2fcore_2fgate_5fcalculator_2eproto_getter() {
  return &descriptor_table_mediapipe_2fcalculators_2fcore_2fgate_5fcalculator_2eproto;
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY static ::PROTOBUF_NAMESPACE_ID::internal::AddDescriptorsRunner dynamic_init_dummy_mediapipe_2fcalculators_2fcore_2fgate_5fcalculator_2eproto(&descriptor_table_mediapipe_2fcalculators_2fcore_2fgate_5fcalculator_2eproto);
namespace mediapipe {

// ===================================================================

class GateCalculatorOptions::_Internal {
 public:
  using HasBits = decltype(std::declval<GateCalculatorOptions>()._has_bits_);
  static void set_has_empty_packets_as_allow(HasBits* has_bits) {
    (*has_bits)[0] |= 1u;
  }
  static void set_has_allow(HasBits* has_bits) {
    (*has_bits)[0] |= 2u;
  }
};

GateCalculatorOptions::GateCalculatorOptions(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor();
  if (!is_message_owned) {
    RegisterArenaDtor(arena);
  }
  // @@protoc_insertion_point(arena_constructor:mediapipe.GateCalculatorOptions)
}
GateCalculatorOptions::GateCalculatorOptions(const GateCalculatorOptions& from)
  : ::PROTOBUF_NAMESPACE_ID::Message(),
      _has_bits_(from._has_bits_) {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  ::memcpy(&empty_packets_as_allow_, &from.empty_packets_as_allow_,
    static_cast<size_t>(reinterpret_cast<char*>(&allow_) -
    reinterpret_cast<char*>(&empty_packets_as_allow_)) + sizeof(allow_));
  // @@protoc_insertion_point(copy_constructor:mediapipe.GateCalculatorOptions)
}

inline void GateCalculatorOptions::SharedCtor() {
::memset(reinterpret_cast<char*>(this) + static_cast<size_t>(
    reinterpret_cast<char*>(&empty_packets_as_allow_) - reinterpret_cast<char*>(this)),
    0, static_cast<size_t>(reinterpret_cast<char*>(&allow_) -
    reinterpret_cast<char*>(&empty_packets_as_allow_)) + sizeof(allow_));
}

GateCalculatorOptions::~GateCalculatorOptions() {
  // @@protoc_insertion_point(destructor:mediapipe.GateCalculatorOptions)
  if (GetArenaForAllocation() != nullptr) return;
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

inline void GateCalculatorOptions::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
}

void GateCalculatorOptions::ArenaDtor(void* object) {
  GateCalculatorOptions* _this = reinterpret_cast< GateCalculatorOptions* >(object);
  (void)_this;
}
void GateCalculatorOptions::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void GateCalculatorOptions::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}

void GateCalculatorOptions::Clear() {
// @@protoc_insertion_point(message_clear_start:mediapipe.GateCalculatorOptions)
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  ::memset(&empty_packets_as_allow_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&allow_) -
      reinterpret_cast<char*>(&empty_packets_as_allow_)) + sizeof(allow_));
  _has_bits_.Clear();
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* GateCalculatorOptions::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  _Internal::HasBits has_bits{};
  while (!ctx->Done(&ptr)) {
    uint32_t tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // optional bool empty_packets_as_allow = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 8)) {
          _Internal::set_has_empty_packets_as_allow(&has_bits);
          empty_packets_as_allow_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // optional bool allow = 2 [default = false];
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 16)) {
          _Internal::set_has_allow(&has_bits);
          allow_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      default:
        goto handle_unusual;
    }  // switch
  handle_unusual:
    if ((tag == 0) || ((tag & 7) == 4)) {
      CHK_(ptr);
      ctx->SetLastTag(tag);
      goto message_done;
    }
    ptr = UnknownFieldParse(
        tag,
        _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
        ptr, ctx);
    CHK_(ptr != nullptr);
  }  // while
message_done:
  _has_bits_.Or(has_bits);
  return ptr;
failure:
  ptr = nullptr;
  goto message_done;
#undef CHK_
}

uint8_t* GateCalculatorOptions::_InternalSerialize(
    uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:mediapipe.GateCalculatorOptions)
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  // optional bool empty_packets_as_allow = 1;
  if (cached_has_bits & 0x00000001u) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteBoolToArray(1, this->_internal_empty_packets_as_allow(), target);
  }

  // optional bool allow = 2 [default = false];
  if (cached_has_bits & 0x00000002u) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteBoolToArray(2, this->_internal_allow(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:mediapipe.GateCalculatorOptions)
  return target;
}

size_t GateCalculatorOptions::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:mediapipe.GateCalculatorOptions)
  size_t total_size = 0;

  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  if (cached_has_bits & 0x00000003u) {
    // optional bool empty_packets_as_allow = 1;
    if (cached_has_bits & 0x00000001u) {
      total_size += 1 + 1;
    }

    // optional bool allow = 2 [default = false];
    if (cached_has_bits & 0x00000002u) {
      total_size += 1 + 1;
    }

  }
  return MaybeComputeUnknownFieldsSize(total_size, &_cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData GateCalculatorOptions::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSizeCheck,
    GateCalculatorOptions::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GateCalculatorOptions::GetClassData() const { return &_class_data_; }

void GateCalculatorOptions::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message* to,
                      const ::PROTOBUF_NAMESPACE_ID::Message& from) {
  static_cast<GateCalculatorOptions *>(to)->MergeFrom(
      static_cast<const GateCalculatorOptions &>(from));
}


void GateCalculatorOptions::MergeFrom(const GateCalculatorOptions& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:mediapipe.GateCalculatorOptions)
  GOOGLE_DCHECK_NE(&from, this);
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = from._has_bits_[0];
  if (cached_has_bits & 0x00000003u) {
    if (cached_has_bits & 0x00000001u) {
      empty_packets_as_allow_ = from.empty_packets_as_allow_;
    }
    if (cached_has_bits & 0x00000002u) {
      allow_ = from.allow_;
    }
    _has_bits_[0] |= cached_has_bits;
  }
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void GateCalculatorOptions::CopyFrom(const GateCalculatorOptions& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:mediapipe.GateCalculatorOptions)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool GateCalculatorOptions::IsInitialized() const {
  return true;
}

void GateCalculatorOptions::InternalSwap(GateCalculatorOptions* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  swap(_has_bits_[0], other->_has_bits_[0]);
  ::PROTOBUF_NAMESPACE_ID::internal::memswap<
      PROTOBUF_FIELD_OFFSET(GateCalculatorOptions, allow_)
      + sizeof(GateCalculatorOptions::allow_)
      - PROTOBUF_FIELD_OFFSET(GateCalculatorOptions, empty_packets_as_allow_)>(
          reinterpret_cast<char*>(&empty_packets_as_allow_),
          reinterpret_cast<char*>(&other->empty_packets_as_allow_));
}

::PROTOBUF_NAMESPACE_ID::Metadata GateCalculatorOptions::GetMetadata() const {
  return ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(
      &descriptor_table_mediapipe_2fcalculators_2fcore_2fgate_5fcalculator_2eproto_getter, &descriptor_table_mediapipe_2fcalculators_2fcore_2fgate_5fcalculator_2eproto_once,
      file_level_metadata_mediapipe_2fcalculators_2fcore_2fgate_5fcalculator_2eproto[0]);
}
#if !defined(_MSC_VER) || (_MSC_VER >= 1900 && _MSC_VER < 1912)
const int GateCalculatorOptions::kExtFieldNumber;
#endif
PROTOBUF_ATTRIBUTE_INIT_PRIORITY ::PROTOBUF_NAMESPACE_ID::internal::ExtensionIdentifier< ::mediapipe::CalculatorOptions,
    ::PROTOBUF_NAMESPACE_ID::internal::MessageTypeTraits< ::mediapipe::GateCalculatorOptions >, 11, false >
  GateCalculatorOptions::ext(kExtFieldNumber, ::mediapipe::GateCalculatorOptions::default_instance());

// @@protoc_insertion_point(namespace_scope)
}  // namespace mediapipe
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::mediapipe::GateCalculatorOptions* Arena::CreateMaybeMessage< ::mediapipe::GateCalculatorOptions >(Arena* arena) {
  return Arena::CreateMessageInternal< ::mediapipe::GateCalculatorOptions >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
