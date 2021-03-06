/**
 * @file dfmessages/DataRequest.hpp DataRequest Message Declaration
 *
 * This is part of the DUNE DAQ Application Framework, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#ifndef DFMESSAGES_INCLUDE_DFMESSAGES_DATAREQUEST_HPP_
#define DFMESSAGES_INCLUDE_DFMESSAGES_DATAREQUEST_HPP_

#include "dfmessages/Types.hpp"

#include "serialization/Serialization.hpp"

#include <limits>

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
  timestamp_t window_begin{ TypeDefaults::s_invalid_timestamp };      ///< Start of readout window
  timestamp_t window_end{ TypeDefaults::s_invalid_timestamp };        ///< End of readout window

  ReadoutType readout_type{ ReadoutType::kInvalid };                            ///< Mode of the request
  sequence_number_t sequence_number{ TypeDefaults::s_invalid_sequence_number }; ///< Sequence Number of the request

  DUNE_DAQ_SERIALIZE(DataRequest,
                     request_number,
                     trigger_number,
                     run_number,
                     trigger_timestamp,
                     window_begin,
                     window_end,
                     readout_type,
                     sequence_number);
};

} // namespace dfmessages
} // namespace dunedaq

#endif // DFMESSAGES_INCLUDE_DFMESSAGES_DATAREQUEST_HPP_
