/**
 * @file dfmessages/TriggerRecord_serialization.hpp TriggerRecord Message Declaration
 *
 * This is part of the DUNE DAQ Application Framework, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#ifndef DFMESSAGES_INCLUDE_DFMESSAGES_TRIGGERRECORD_SERIALIZATION_HPP_
#define DFMESSAGES_INCLUDE_DFMESSAGES_TRIGGERRECORD_SERIALIZATION_HPP_

#include "daqdataformats/TriggerRecord.hpp"
#include "dfmessages/Fragment_serialization.hpp"
#include "dfmessages/TriggerRecordHeader_serialization.hpp"
#include "serialization/Serialization.hpp"

#include <memory>
#include <utility>
#include <vector>

namespace dunedaq {
// Disable coverage collection LCOV_EXCL_START
ERS_DECLARE_ISSUE(dfmessages,
                  CannotDeserializeTriggerRecord,
                  "Cannot deserialize TriggerRecord from JSON due to type mismatch", )
// Re-enable coverage collection LCOV_EXCL_STOP
} // namespace dunedaq

// MsgPack serialization functions (which just put the raw bytes of
// the fragment array into a MsgPack message)
namespace msgpack {
MSGPACK_API_VERSION_NAMESPACE(MSGPACK_DEFAULT_API_NS)
{
  namespace adaptor {

  template<>
  struct pack<dunedaq::daqdataformats::TriggerRecord>
  {
    template<typename Stream>
    packer<Stream>& operator()(msgpack::packer<Stream>& o, dunedaq::daqdataformats::TriggerRecord const& tr) const
    {
      auto& trh = tr.get_header_ref();
      auto& frags = tr.get_fragments_ref();

      o.pack_array(1 + frags.size());
      o.pack(trh);
      for (auto& fragptr : frags) {
        o.pack(fragptr);
      }
      return o;
    }
  };

  // Typically we use convert<> for deserialization, but TriggerRecord isn't
  // default constructible, so we have to use as<>. See:
  // https://github.com/msgpack/msgpack-c/wiki/v2_0_cpp_adaptor#non-default-constructible-class-support-c11-only-since-120
  template<>
  struct as<dunedaq::daqdataformats::TriggerRecord>
  {
    dunedaq::daqdataformats::TriggerRecord operator()(msgpack::object const& o) const
    {
      dunedaq::daqdataformats::TriggerRecord tr(o.via.array.ptr[0].as<dunedaq::daqdataformats::TriggerRecordHeader>());

      for (size_t ii = 1; ii < o.via.array.size; ++ii) {
        auto fragptr = o.via.array.ptr[ii].as<std::unique_ptr<dunedaq::daqdataformats::Fragment>>();
        tr.add_fragment(std::move(fragptr));
      }

      return tr;
    }
  };

  template<>
  struct pack<std::unique_ptr<dunedaq::daqdataformats::TriggerRecord>>
  {
    template<typename Stream>
    packer<Stream>& operator()(msgpack::packer<Stream>& o,
                               std::unique_ptr<dunedaq::daqdataformats::TriggerRecord> const& tr) const
    {
      auto& trh = tr->get_header_ref();
      auto& frags = tr->get_fragments_ref();

      o.pack_array(1 + frags.size());
      o.pack(trh);
      for (auto& fragptr : frags) {
        o.pack(fragptr);
      }
      return o;
    }
  };

  // Typically we use convert<> for deserialization, but TriggerRecord isn't
  // default constructible, so we have to use as<>. See:
  // https://github.com/msgpack/msgpack-c/wiki/v2_0_cpp_adaptor#non-default-constructible-class-support-c11-only-since-120
  template<>
  struct as<std::unique_ptr<dunedaq::daqdataformats::TriggerRecord>>
  {
    std::unique_ptr<dunedaq::daqdataformats::TriggerRecord> operator()(msgpack::object const& o) const
    {
      auto tr = std::make_unique<dunedaq::daqdataformats::TriggerRecord>(
        o.via.array.ptr[0].as<dunedaq::daqdataformats::TriggerRecordHeader>());

      for (size_t ii = 1; ii < o.via.array.size; ++ii) {
        auto fragptr = o.via.array.ptr[ii].as<std::unique_ptr<dunedaq::daqdataformats::Fragment>>();
        tr->add_fragment(std::move(fragptr));
      }

      return tr;
    }
  };
  } // namespace adaptor
} // namespace MSGPACK_DEFAULT_API_NS
} // namespace msgpack

// nlohmann::json serialization function. As with MsgPack, we have to
// do something special here because TriggerRecord isn't default
// constructible. See
// https://nlohmann.github.io/json/features/arbitrary_types/#how-can-i-use-get-for-non-default-constructiblenon-copyable-types
namespace nlohmann {
template<>
struct adl_serializer<dunedaq::daqdataformats::TriggerRecord>
{
  // note: the return type is no longer 'void', and the method only takes
  // one argument
  static dunedaq::daqdataformats::TriggerRecord from_json(const json& j)
  {
    if (!j.contains("header")) {
      throw dunedaq::dfmessages::CannotDeserializeTriggerRecord(ERS_HERE);
    }

    dunedaq::daqdataformats::TriggerRecordHeader trh = j["header"];
    dunedaq::daqdataformats::TriggerRecord tr(trh);

    if (j.contains("fragments")) {
      std::vector<std::unique_ptr<dunedaq::daqdataformats::Fragment>> frags = j["fragments"];
      tr.set_fragments(std::move(frags));
    }

    return tr;
  }

  static void to_json(json& j, const dunedaq::daqdataformats::TriggerRecord& tr)
  {
    auto& trh = tr.get_header_ref();
    auto& frags = tr.get_fragments_ref();

    j["header"] = trh;
    j["fragments"] = json::array();
    for (auto& fragptr : frags) {
      j["fragments"].push_back(fragptr);
    }
  }
};
template<>
struct adl_serializer<std::unique_ptr<dunedaq::daqdataformats::TriggerRecord>>
{
  // note: the return type is no longer 'void', and the method only takes
  // one argument
  static std::unique_ptr<dunedaq::daqdataformats::TriggerRecord> from_json(const json& j)
  {
    if (!j.contains("header")) {
      throw dunedaq::dfmessages::CannotDeserializeTriggerRecord(ERS_HERE);
    }

    dunedaq::daqdataformats::TriggerRecordHeader trh = j["header"];
    auto tr = std::make_unique<dunedaq::daqdataformats::TriggerRecord>(trh);

    if (j.contains("fragments")) {
      std::vector<std::unique_ptr<dunedaq::daqdataformats::Fragment>> frags = j["fragments"];
      tr->set_fragments(std::move(frags));
    }

    return tr;
  }

  static void to_json(json& j, const std::unique_ptr<dunedaq::daqdataformats::TriggerRecord>& tr)
  {
    auto& trh = tr->get_header_ref();
    auto& frags = tr->get_fragments_ref();

    j["header"] = trh;
    j["fragments"] = json::array();
    for (auto& fragptr : frags) {
      j["fragments"].push_back(fragptr);
    }
  }
};
} // namespace nlohmann

#endif // DFMESSAGES_INCLUDE_DFMESSAGES_TRIGGERRECORD_SERIALIZATION_HPP_
