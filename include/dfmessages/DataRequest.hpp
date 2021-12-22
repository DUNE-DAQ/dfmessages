/**
 * @file dfmessages/DataRequest.hpp DataRequest Message Declaration
 *
 * This is part of the DUNE DAQ Application Framework, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#ifndef DFMESSAGES_INCLUDE_DFMESSAGES_DATAREQUEST_HPP_
#define DFMESSAGES_INCLUDE_DFMESSAGES_DATAREQUEST_HPP_

#include "dfmessages/ComponentRequest_serialization.hpp"
#include "dfmessages/Types.hpp"

#include "serialization/Serialization.hpp"

#include <limits>
#include <string>

namespace dunedaq {
namespace dfmessages {
/**
 * @brief This message represents a request for data sent to a single component of the DAQ
 */
struct DataRequest
{

  request_number_t request_number{ TypeDefaults::s_invalid_request_number }; ///< The number of the request
  trigger_number_t trigger_number{
    TypeDefaults::s_invalid_trigger_number
  };                                                             ///< Trigger number the request corresponds to
  run_number_t run_number{ TypeDefaults::s_invalid_run_number }; ///< The current run number

  timestamp_t trigger_timestamp{ TypeDefaults::s_invalid_timestamp }; ///< Timestamp of trigger
  ComponentRequest request_information;

  ReadoutType readout_type{ ReadoutType::kInvalid };                            ///< Mode of the request
  sequence_number_t sequence_number{ TypeDefaults::s_invalid_sequence_number }; ///< Sequence Number of the request

  std::string data_destination;

  DUNE_DAQ_SERIALIZE(DataRequest,
                     request_number,
                     trigger_number,
                     run_number,
                     trigger_timestamp,
                     request_information,
                     readout_type,
                     sequence_number,
                     data_destination);
};

} // namespace dfmessages
} // namespace dunedaq

#endif // DFMESSAGES_INCLUDE_DFMESSAGES_DATAREQUEST_HPP_
