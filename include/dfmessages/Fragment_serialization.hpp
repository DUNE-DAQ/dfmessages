
/**
 * @file dfmessages/Fragment_serialization.hpp Fragment Message Declaration
 *
 * This is part of the DUNE DAQ Application Framework, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#ifndef DFMESSAGES_INCLUDE_DFMESSAGES_FRAGMENT_SERIALIZATION_HPP_
#define DFMESSAGES_INCLUDE_DFMESSAGES_FRAGMENT_SERIALIZATION_HPP_

#include "daqdataformats/Fragment.hpp"
#include "serialization/Serialization.hpp"

#include <memory>
#include <vector>

namespace dunedaq {
ERS_DECLARE_ISSUE(dfmessages, CannotDeserializeFragment, "Cannot deserialize Fragment from JSON due to type mismatch", )
} // namespace dunedaq

// MsgPack serialization functions (which just put the raw bytes of
// the fragment array into a MsgPack message)
namespace msgpack {
MSGPACK_API_VERSION_NAMESPACE(MSGPACK_DEFAULT_API_NS)
{
  namespace adaptor {

  template<>
  struct pack<dunedaq::daqdataformats::Fragment>
  {
    template<typename Stream>
    packer<Stream>& operator()(msgpack::packer<Stream>& o, dunedaq::daqdataformats::Fragment const& frag) const
    {
      o.pack_bin(frag.get_size());                                                             // pack header and size
      o.pack_bin_body(static_cast<const char*>(frag.get_storage_location()), frag.get_size()); // pack payload
      return o;
    }
  };

  // Typically we use convert<> for deserialization, but Fragment isn't
  // default constructible, so we have to use as<>. See:
  // https://github.com/msgpack/msgpack-c/wiki/v2_0_cpp_adaptor#non-default-constructible-class-support-c11-only-since-120
  template<>
  struct as<dunedaq::daqdataformats::Fragment>
  {
    dunedaq::daqdataformats::Fragment operator()(msgpack::object const& o) const
    {
      // The second argument to the Fragment ctor is whether to copy
      // the data array into the Fragment's own storage. Putting false
      // here would be faster, but we have to copy, since the returned
      // Fragment might outlast the msgpack::object which owns/points
      // to the underlying data.
      return dunedaq::daqdataformats::Fragment(const_cast<char*>(o.via.bin.ptr),
                                               dunedaq::daqdataformats::Fragment::BufferAdoptionMode::kCopyFromBuffer);
    }
  };

  template<>
  struct pack<std::unique_ptr<dunedaq::daqdataformats::Fragment>>
  {
    template<typename Stream>
    packer<Stream>& operator()(msgpack::packer<Stream>& o,
                               std::unique_ptr<dunedaq::daqdataformats::Fragment> const& frag) const
    {
      o.pack_bin(frag->get_size());                                                              // pack header and size
      o.pack_bin_body(static_cast<const char*>(frag->get_storage_location()), frag->get_size()); // pack payload
      return o;
    }
  };

  // Typically we use convert<> for deserialization, but Fragment isn't
  // default constructible, so we have to use as<>. See:
  // https://github.com/msgpack/msgpack-c/wiki/v2_0_cpp_adaptor#non-default-constructible-class-support-c11-only-since-120
  template<>
  struct as<std::unique_ptr<dunedaq::daqdataformats::Fragment>>
  {
    std::unique_ptr<dunedaq::daqdataformats::Fragment> operator()(msgpack::object const& o) const
    {
      // The second argument to the Fragment ctor is whether to copy
      // the data array into the Fragment's own storage. Putting false
      // here would be faster, but we have to copy, since the returned
      // Fragment might outlast the msgpack::object which owns/points
      // to the underlying data.
      return std::make_unique<dunedaq::daqdataformats::Fragment>(
        const_cast<char*>(o.via.bin.ptr), dunedaq::daqdataformats::Fragment::BufferAdoptionMode::kCopyFromBuffer);
    }
  };
  } // namespace adaptor
} // namespace MSGPACK_DEFAULT_API_NS
} // namespace msgpack

// nlohmann::json serialization function. As with MsgPack, we have to
// do something special here because Fragment isn't default
// constructible. See
// https://nlohmann.github.io/json/features/arbitrary_types/#how-can-i-use-get-for-non-default-constructiblenon-copyable-types
namespace nlohmann {
template<>
struct adl_serializer<dunedaq::daqdataformats::Fragment>
{
  // note: the return type is no longer 'void', and the method only takes
  // one argument
  static dunedaq::daqdataformats::Fragment from_json(const json& j)
  {
    std::vector<uint8_t> tmp; // NOLINT(build/unsigned)
    for (auto const& it : j.items()) {
      if (!it.value().is_number_integer()) {
        throw dunedaq::dfmessages::CannotDeserializeFragment(ERS_HERE);
      }
      tmp.push_back(it.value().get<uint8_t>()); // NOLINT(build/unsigned)
    }
    return dunedaq::daqdataformats::Fragment(tmp.data(),
                                             dunedaq::daqdataformats::Fragment::BufferAdoptionMode::kCopyFromBuffer);
  }

  static void to_json(json& j, const dunedaq::daqdataformats::Fragment& frag)
  {
    const uint8_t* storage = static_cast<const uint8_t*>(frag.get_storage_location()); // NOLINT(build/unsigned)
    std::vector<uint8_t> bytes(storage, storage + frag.get_size());                    // NOLINT(build/unsigned)
    j = bytes;
  }
};
template<>
struct adl_serializer<std::unique_ptr<dunedaq::daqdataformats::Fragment>>
{
  // note: the return type is no longer 'void', and the method only takes
  // one argument
  static std::unique_ptr<dunedaq::daqdataformats::Fragment> from_json(const json& j)
  {
    std::vector<uint8_t> tmp; // NOLINT(build/unsigned)
    for (auto const& it : j.items()) {
      if (!it.value().is_number_integer()) {
        throw dunedaq::dfmessages::CannotDeserializeFragment(ERS_HERE);
      }
      tmp.push_back(it.value().get<uint8_t>()); // NOLINT(build/unsigned)
    }
    return std::make_unique<dunedaq::daqdataformats::Fragment>(
      tmp.data(), dunedaq::daqdataformats::Fragment::BufferAdoptionMode::kCopyFromBuffer);
  }

  static void to_json(json& j, const std::unique_ptr<dunedaq::daqdataformats::Fragment>& frag)
  {
    const uint8_t* storage = static_cast<const uint8_t*>(frag->get_storage_location()); // NOLINT(build/unsigned)
    std::vector<uint8_t> bytes(storage, storage + frag->get_size());                    // NOLINT(build/unsigned)
    j = bytes;
  }
};
} // namespace nlohmann

DUNE_DAQ_SERIALIZABLE(dunedaq::daqdataformats::Fragment);
DUNE_DAQ_SERIALIZABLE(std::unique_ptr<dunedaq::daqdataformats::Fragment>);

#endif // DFMESSAGES_INCLUDE_DFMESSAGES_FRAGMENT_SERIALIZATION_HPP_
