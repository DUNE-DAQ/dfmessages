/**
 * @file dfmessages/SourceID_serialization.hpp SourceID Message Declaration
 *
 * This is part of the DUNE DAQ Application Framework, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#ifndef DFMESSAGES_INCLUDE_DFMESSAGES_SOURCEID_SERIALIZATION_HPP_
#define DFMESSAGES_INCLUDE_DFMESSAGES_SOURCEID_SERIALIZATION_HPP_

#include "daqdataformats/SourceID.hpp"
#include "serialization/Serialization.hpp"

MSGPACK_ADD_ENUM(dunedaq::daqdataformats::SourceID::Subsystem)
DUNE_DAQ_SERIALIZE_NON_INTRUSIVE(dunedaq::daqdataformats, SourceID, version, subsystem, id)

#endif // DFMESSAGES_INCLUDE_DFMESSAGES_SOURCEID_SERIALIZATION_HPP_
