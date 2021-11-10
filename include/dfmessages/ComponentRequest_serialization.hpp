/**
 * @file dfmessages/ComponentRequest_serialization.hpp ComponentRequest Message Declaration
 *
 * This is part of the DUNE DAQ Application Framework, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#ifndef DFMESSAGES_INCLUDE_DFMESSAGES_COMPONENTREQUEST_SERIALIZATION_HPP_
#define DFMESSAGES_INCLUDE_DFMESSAGES_COMPONENTREQUEST_SERIALIZATION_HPP_

#include "daqdataformats/ComponentRequest.hpp"
#include "dfmessages/GeoID_serialization.hpp"

DUNE_DAQ_SERIALIZE_NON_INTRUSIVE(dunedaq::daqdataformats, ComponentRequest, window_begin, window_end, component)

#endif // DFMESSAGES_INCLUDE_DFMESSAGES_COMPONENTREQUEST_SERIALIZATION_HPP_
