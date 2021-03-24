/**
 * @file dfmessages/GeoID_serialization.hpp GeoID Message Declaration
 *
 * This is part of the DUNE DAQ Application Framework, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#ifndef DFMESSAGES_INCLUDE_DFMESSAGES_GEOID_SERIALIZATION_HPP_
#define DFMESSAGES_INCLUDE_DFMESSAGES_GEOID_SERIALIZATION_HPP_

#include "dataformats/GeoID.hpp"
#include "serialization/Serialization.hpp"

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
to_json(nlohmann::json& j, const GeoID& m)
{
  j["apa_number"] = m.apa_number;
  j["link_number"] = m.link_number;
}

inline void
from_json(const nlohmann::json& j, GeoID& m)
{
  j.at("apa_number").get_to(m.apa_number);
  j.at("link_number").get_to(m.link_number);
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
  struct pack<dunedaq::dataformats::GeoID>
  {
    template<typename Stream>
    packer<Stream>& operator()(msgpack::packer<Stream>& o, dunedaq::dataformats::GeoID const& m) const
    {
      // The number here is the number of members in the struct
      o.pack_array(2);
      o.pack(m.apa_number);
      o.pack(m.link_number);
      return o;
    }
  };

  template<>
  struct convert<dunedaq::dataformats::GeoID>
  {
    msgpack::object const& operator()(msgpack::object const& o, dunedaq::dataformats::GeoID& m) const
    {
      if (o.type != msgpack::type::ARRAY)
        throw msgpack::type_error();
      // The number here is the number of members in the struct
      if (o.via.array.size != 2)
        throw msgpack::type_error();
      m.apa_number = o.via.array.ptr[0].as<uint32_t>();
      m.link_number = o.via.array.ptr[1].as<uint32_t>();
      return o;
    }
  };

  } // namespace adaptor
} // namespace MSGPACK_DEFAULT_API_NS
} // namespace msgpack

#endif // DFMESSAGES_INCLUDE_DFMESSAGES_GEOID_SERIALIZATION_HPP_