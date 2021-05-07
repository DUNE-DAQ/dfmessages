
/**
 * @file dfmessages/Fragment_serialization.hpp Fragment Message Declaration
 *
 * This is part of the DUNE DAQ Application Framework, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#ifndef DFMESSAGES_INCLUDE_DFMESSAGES_FRAGMENT_SERIALIZATION_HPP_
#define DFMESSAGES_INCLUDE_DFMESSAGES_FRAGMENT_SERIALIZATION_HPP_

#include "dataformats/Fragment.hpp"
#include "serialization/Serialization.hpp"

// MsgPack serialization functions (which just put the raw bytes of
// the fragment array into a MsgPack message)
namespace msgpack {
MSGPACK_API_VERSION_NAMESPACE(MSGPACK_DEFAULT_API_NS)
{
  namespace adaptor {

  template<>
  struct pack<dunedaq::dataformats::Fragment>
  {
    template<typename Stream>
    packer<Stream>& operator()(msgpack::packer<Stream>& o, dunedaq::dataformats::Fragment const& frag) const
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
  struct as<dunedaq::dataformats::Fragment>
  {
    dunedaq::dataformats::Fragment operator()(msgpack::object const& o) const
    {
      // The second argument to the Fragment ctor is whether to copy
      // the data array into the Fragment's own storage. Putting false
      // here would be faster, but we have to copy, since the returned
      // Fragment might outlast the msgpack::object which owns/points
      // to the underlying data.
      return dunedaq::dataformats::Fragment(const_cast<char*>(o.via.bin.ptr),
                                            dunedaq::dataformats::Fragment::BufferAdoptionMode::kCopyFromBuffer);
    }
  };

  template<>
  struct pack<std::unique_ptr<dunedaq::dataformats::Fragment>>
  {
    template<typename Stream>
    packer<Stream>& operator()(msgpack::packer<Stream>& o,
                               std::unique_ptr<dunedaq::dataformats::Fragment> const& frag) const
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
  struct as<std::unique_ptr<dunedaq::dataformats::Fragment>>
  {
    std::unique_ptr<dunedaq::dataformats::Fragment> operator()(msgpack::object const& o) const
    {
      // The second argument to the Fragment ctor is whether to copy
      // the data array into the Fragment's own storage. Putting false
      // here would be faster, but we have to copy, since the returned
      // Fragment might outlast the msgpack::object which owns/points
      // to the underlying data.
      return std::make_unique<dunedaq::dataformats::Fragment>(
        const_cast<char*>(o.via.bin.ptr), dunedaq::dataformats::Fragment::BufferAdoptionMode::kCopyFromBuffer);
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
struct adl_serializer<dunedaq::dataformats::Fragment>
{
  // note: the return type is no longer 'void', and the method only takes
  // one argument
  static dunedaq::dataformats::Fragment from_json(const json& j)
  {
    std::vector<uint8_t> tmp;
    for (auto const& it : j.items()) {
      if (!it.value().is_number_integer()) {
        throw std::runtime_error("Foo");
      }
      tmp.push_back(it.value().get<uint8_t>());
    }
    return dunedaq::dataformats::Fragment(tmp.data(),
                                          dunedaq::dataformats::Fragment::BufferAdoptionMode::kCopyFromBuffer);
  }

  static void to_json(json& j, const dunedaq::dataformats::Fragment& frag)
  {
    const uint8_t* storage = static_cast<const uint8_t*>(frag.get_storage_location());
    std::vector<uint8_t> bytes(storage, storage + frag.get_size());
    j = bytes;
  }
};
template<>
struct adl_serializer<std::unique_ptr<dunedaq::dataformats::Fragment>>
{
  // note: the return type is no longer 'void', and the method only takes
  // one argument
  static std::unique_ptr<dunedaq::dataformats::Fragment> from_json(const json& j)
  {
    std::vector<uint8_t> tmp;
    for (auto const& it : j.items()) {
      if (!it.value().is_number_integer()) {
        throw std::runtime_error("Foo");
      }
      tmp.push_back(it.value().get<uint8_t>());
    }
    return std::make_unique<dunedaq::dataformats::Fragment>(
      tmp.data(), dunedaq::dataformats::Fragment::BufferAdoptionMode::kCopyFromBuffer);
  }

  static void to_json(json& j, const std::unique_ptr<dunedaq::dataformats::Fragment>& frag)
  {
    const uint8_t* storage = static_cast<const uint8_t*>(frag->get_storage_location());
    std::vector<uint8_t> bytes(storage, storage + frag->get_size());
    j = bytes;
  }
};
} // namespace nlohmann

#endif // DFMESSAGES_INCLUDE_DFMESSAGES_FRAGMENT_SERIALIZATION_HPP_
