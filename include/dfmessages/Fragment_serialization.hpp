
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
#include "logging/Logging.hpp" // NOTE: if ISSUES ARE DECLARED BEFORE include logging/Logging.hpp, TLOG_DEBUG<<issue wont work.

#include <memory>
#include <vector>

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

DUNE_DAQ_SERIALIZABLE(dunedaq::daqdataformats::Fragment, "Fragment");
DUNE_DAQ_SERIALIZABLE(std::unique_ptr<dunedaq::daqdataformats::Fragment>, "Fragment");

#endif // DFMESSAGES_INCLUDE_DFMESSAGES_FRAGMENT_SERIALIZATION_HPP_
