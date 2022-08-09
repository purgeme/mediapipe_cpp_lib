// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: mediapipe/gpu/scale_mode.proto

#include "mediapipe/gpu/scale_mode.pb.h"

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
constexpr ScaleMode::ScaleMode(
  ::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized){}
struct ScaleModeDefaultTypeInternal {
  constexpr ScaleModeDefaultTypeInternal()
    : _instance(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized{}) {}
  ~ScaleModeDefaultTypeInternal() {}
  union {
    ScaleMode _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT ScaleModeDefaultTypeInternal _ScaleMode_default_instance_;
}  // namespace mediapipe
static ::PROTOBUF_NAMESPACE_ID::Metadata file_level_metadata_mediapipe_2fgpu_2fscale_5fmode_2eproto[1];
static const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* file_level_enum_descriptors_mediapipe_2fgpu_2fscale_5fmode_2eproto[1];
static constexpr ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor const** file_level_service_descriptors_mediapipe_2fgpu_2fscale_5fmode_2eproto = nullptr;

const uint32_t TableStruct_mediapipe_2fgpu_2fscale_5fmode_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::mediapipe::ScaleMode, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
};
static const ::PROTOBUF_NAMESPACE_ID::internal::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, -1, sizeof(::mediapipe::ScaleMode)},
};

static ::PROTOBUF_NAMESPACE_ID::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::mediapipe::_ScaleMode_default_instance_),
};

const char descriptor_table_protodef_mediapipe_2fgpu_2fscale_5fmode_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\036mediapipe/gpu/scale_mode.proto\022\tmediap"
  "ipe\"I\n\tScaleMode\"<\n\004Mode\022\013\n\007DEFAULT\020\000\022\013\n"
  "\007STRETCH\020\001\022\007\n\003FIT\020\002\022\021\n\rFILL_AND_CROP\020\003"
  ;
static ::PROTOBUF_NAMESPACE_ID::internal::once_flag descriptor_table_mediapipe_2fgpu_2fscale_5fmode_2eproto_once;
const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_mediapipe_2fgpu_2fscale_5fmode_2eproto = {
  false, false, 118, descriptor_table_protodef_mediapipe_2fgpu_2fscale_5fmode_2eproto, "mediapipe/gpu/scale_mode.proto", 
  &descriptor_table_mediapipe_2fgpu_2fscale_5fmode_2eproto_once, nullptr, 0, 1,
  schemas, file_default_instances, TableStruct_mediapipe_2fgpu_2fscale_5fmode_2eproto::offsets,
  file_level_metadata_mediapipe_2fgpu_2fscale_5fmode_2eproto, file_level_enum_descriptors_mediapipe_2fgpu_2fscale_5fmode_2eproto, file_level_service_descriptors_mediapipe_2fgpu_2fscale_5fmode_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable* descriptor_table_mediapipe_2fgpu_2fscale_5fmode_2eproto_getter() {
  return &descriptor_table_mediapipe_2fgpu_2fscale_5fmode_2eproto;
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY static ::PROTOBUF_NAMESPACE_ID::internal::AddDescriptorsRunner dynamic_init_dummy_mediapipe_2fgpu_2fscale_5fmode_2eproto(&descriptor_table_mediapipe_2fgpu_2fscale_5fmode_2eproto);
namespace mediapipe {
const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* ScaleMode_Mode_descriptor() {
  ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&descriptor_table_mediapipe_2fgpu_2fscale_5fmode_2eproto);
  return file_level_enum_descriptors_mediapipe_2fgpu_2fscale_5fmode_2eproto[0];
}
bool ScaleMode_Mode_IsValid(int value) {
  switch (value) {
    case 0:
    case 1:
    case 2:
    case 3:
      return true;
    default:
      return false;
  }
}

#if (__cplusplus < 201703) && (!defined(_MSC_VER) || (_MSC_VER >= 1900 && _MSC_VER < 1912))
constexpr ScaleMode_Mode ScaleMode::DEFAULT;
constexpr ScaleMode_Mode ScaleMode::STRETCH;
constexpr ScaleMode_Mode ScaleMode::FIT;
constexpr ScaleMode_Mode ScaleMode::FILL_AND_CROP;
constexpr ScaleMode_Mode ScaleMode::Mode_MIN;
constexpr ScaleMode_Mode ScaleMode::Mode_MAX;
constexpr int ScaleMode::Mode_ARRAYSIZE;
#endif  // (__cplusplus < 201703) && (!defined(_MSC_VER) || (_MSC_VER >= 1900 && _MSC_VER < 1912))

// ===================================================================

class ScaleMode::_Internal {
 public:
};

ScaleMode::ScaleMode(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::internal::ZeroFieldsBase(arena, is_message_owned) {
  // @@protoc_insertion_point(arena_constructor:mediapipe.ScaleMode)
}
ScaleMode::ScaleMode(const ScaleMode& from)
  : ::PROTOBUF_NAMESPACE_ID::internal::ZeroFieldsBase() {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  // @@protoc_insertion_point(copy_constructor:mediapipe.ScaleMode)
}





const ::PROTOBUF_NAMESPACE_ID::Message::ClassData ScaleMode::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::internal::ZeroFieldsBase::CopyImpl,
    ::PROTOBUF_NAMESPACE_ID::internal::ZeroFieldsBase::MergeImpl,
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*ScaleMode::GetClassData() const { return &_class_data_; }







::PROTOBUF_NAMESPACE_ID::Metadata ScaleMode::GetMetadata() const {
  return ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(
      &descriptor_table_mediapipe_2fgpu_2fscale_5fmode_2eproto_getter, &descriptor_table_mediapipe_2fgpu_2fscale_5fmode_2eproto_once,
      file_level_metadata_mediapipe_2fgpu_2fscale_5fmode_2eproto[0]);
}

// @@protoc_insertion_point(namespace_scope)
}  // namespace mediapipe
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::mediapipe::ScaleMode* Arena::CreateMaybeMessage< ::mediapipe::ScaleMode >(Arena* arena) {
  return Arena::CreateMessageInternal< ::mediapipe::ScaleMode >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
