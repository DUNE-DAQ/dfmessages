/**
 * @file dfmessages/TriggerRecordHeader_serialization.hpp TriggerRecordHeader Message Declaration
 *
 * This is part of the DUNE DAQ Application Framework, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#ifndef DFMESSAGES_INCLUDE_DFMESSAGES_TRIGGERRECORDHEADER_SERIALIZATION_HPP_
#define DFMESSAGES_INCLUDE_DFMESSAGES_TRIGGERRECORDHEADER_SERIALIZATION_HPP_

#include "daqdataformats/TriggerRecordHeader.hpp"
#include "serialization/Serialization.hpp"

#include <vector>

namespace dunedaq {
// Disable coverage collection LCOV_EXCL_START
ERS_DECLARE_ISSUE(dfmessages,
                  CannotDeserializeTriggerRecordHeader,
                  "Cannot deserialize TriggerRecordHeader from JSON due to type mismatch", )
// Re-enable coverage collection LCOV_EXCL_STOP
} // namespace dunedaq

// MsgPack serialization functions (which just put the raw bytes of
// the fragment array into a MsgPack message)
namespace msgpack {
MSGPACK_API_VERSION_NAMESPACE(MSGPACK_DEFAULT_API_NS)
{
  namespace adaptor {

  template<>
  struct pack<dunedaq::daqdataformats::TriggerRecordHeader>
  {
    template<typename Stream>
    packer<Stream>& operator()(msgpack::packer<Stream>& o,
                               dunedaq::daqdataformats::TriggerRecordHeader const& trh) const
    {
      size_t size = trh.get_total_size_bytes();
      o.pack_bin(size);                                                            // pack header and size
      o.pack_bin_body(static_cast<const char*>(trh.get_storage_location()), size); // pack payload
      return o;
    }
  };

  // Typically we use convert<> for deserialization, but TriggerRecordHeader isn't
  // default constructible, so we have to use as<>. See:
  // https://github.com/msgpack/msgpack-c/wiki/v2_0_cpp_adaptor#non-default-constructible-class-support-c11-only-since-120
  template<>
  struct as<dunedaq::daqdataformats::TriggerRecordHeader>
  {
    dunedaq::daqdataformats::TriggerRecordHeader operator()(msgpack::object const& o) const
    {
      return dunedaq::daqdataformats::TriggerRecordHeader(const_cast<char*>(o.via.bin.ptr), true);
    }
  };

  } // namespace adaptor
} // namespace MSGPACK_DEFAULT_API_NS
} // namespace msgpack

// nlohmann::json serialization function. As with MsgPack, we have to
// do something special here because TriggerRecordHeader isn't default
// constructible. See
// https://nlohmann.github.io/json/features/arbitrary_types/#how-can-i-use-get-for-non-default-constructiblenon-copyable-types
namespace nlohmann {
template<>
struct adl_serializer<dunedaq::daqdataformats::TriggerRecordHeader>
{
  // note: the return type is no longer 'void', and the method only takes
  // one argument
  static dunedaq::daqdataformats::TriggerRecordHeader from_json(const json& j)
  {
    std::vector<uint8_t> tmp; // NOLINT(build/unsigned)
    for (auto const& it : j.items()) {
      if (!it.value().is_number_integer()) {
        throw dunedaq::dfmessages::CannotDeserializeTriggerRecordHeader(ERS_HERE);
      }
      tmp.push_back(it.value().get<uint8_t>()); // NOLINT(build/unsigned)
    }
    return dunedaq::daqdataformats::TriggerRecordHeader(tmp.data(), true);
  }

  static void to_json(json& j, const dunedaq::daqdataformats::TriggerRecordHeader& trh)
  {
    const uint8_t* storage = static_cast<const uint8_t*>(trh.get_storage_location()); // NOLINT(build/unsigned)
    std::vector<uint8_t> bytes(storage, storage + trh.get_total_size_bytes());        // NOLINT(build/unsigned)
    j = bytes;
  }
};
} // namespace nlohmann

DUNE_DAQ_SERIALIZABLE(dunedaq::daqdataformats::TriggerRecordHeader);

#endif // DFMESSAGES_INCLUDE_DFMESSAGES_TRIGGERRECORDHEADER_SERIALIZATION_HPP_
