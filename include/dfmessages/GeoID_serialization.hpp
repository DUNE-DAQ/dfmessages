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

MSGPACK_ADD_ENUM(dunedaq::dataformats::GeoIDComponentType)
DUNE_DAQ_SERIALIZE_NON_INTRUSIVE(dunedaq::dataformats, GeoID, component_type, region_id, element_id) 

#endif // DFMESSAGES_INCLUDE_DFMESSAGES_GEOID_SERIALIZATION_HPP_
