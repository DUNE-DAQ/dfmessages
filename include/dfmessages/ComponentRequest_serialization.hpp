/**
 * @file dfmessages/ComponentRequest_serialization.hpp ComponentRequest Message Declaration
 *
 * This is part of the DUNE DAQ Application Framework, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#ifndef DFMESSAGES_INCLUDE_DFMESSAGES_COMPONENTREQUEST_SERIALIZATION_HPP_
#define DFMESSAGES_INCLUDE_DFMESSAGES_COMPONENTREQUEST_SERIALIZATION_HPP_

#include "dataformats/ComponentRequest.hpp"
#include "dfmessages/GeoID_serialization.hpp"

namespace dunedaq {
namespace dataformats {
// These two functions provide the serialization/deserialization
// functionality for nlohmann::json. They don't need to be in the same file as the
// definition of the type, but they do need to be in the same
// namespace. I assume that it's not strictly required to name the map
// keys the same thing as the variable, but it seems sensible
//
// For full instructions, see:
// https://nlohmann.github.io/json/features/arbitrary_types/
inline void
to_json(nlohmann::json& j, const ComponentRequest& m)
{
  j["window_begin"] = m.window_begin;
  j["window_end"] = m.window_end;
  j["component"] = m.component;
}

inline void
from_json(const nlohmann::json& j, ComponentRequest& m)
{
  j.at("window_begin").get_to(m.window_begin);
  j.at("window_end").get_to(m.window_end);
  j.at("component").get_to(m.component);
}

}
}

// These two functions provide the serialization/deserialization
// functionality for MsgPack
namespace msgpack {
MSGPACK_API_VERSION_NAMESPACE(MSGPACK_DEFAULT_API_NS)
{
  namespace adaptor {

  template<>
  struct pack<dunedaq::dataformats::ComponentRequest>
  {
    template<typename Stream>
    packer<Stream>& operator()(msgpack::packer<Stream>& o, dunedaq::dataformats::ComponentRequest const& m) const
    {
      // The number here is the number of members in the struct
      o.pack_array(3);
      o.pack(m.window_begin);
      o.pack(m.window_end);
      o.pack(m.component);
      return o;
    }
  };

  template<>
  struct convert<dunedaq::dataformats::ComponentRequest>
  {
    msgpack::object const& operator()(msgpack::object const& o, dunedaq::dataformats::ComponentRequest& m) const
    {
      if (o.type != msgpack::type::ARRAY)
        throw msgpack::type_error();
      // The number here is the number of members in the struct
      if (o.via.array.size != 3)
        throw msgpack::type_error();
      m.window_begin = o.via.array.ptr[0].as<dunedaq::dataformats::timestamp_t>();
      m.window_end = o.via.array.ptr[1].as<dunedaq::dataformats::timestamp_t>();
      m.component = o.via.array.ptr[2].as<dunedaq::dataformats::GeoID>();
      return o;
    }
  };

  } // namespace adaptor
} // namespace MSGPACK_DEFAULT_API_NS
} // namespace msgpack

#endif // DFMESSAGES_INCLUDE_DFMESSAGES_COMPONENTREQUEST_SERIALIZATION_HPP_