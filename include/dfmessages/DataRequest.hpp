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

#include <limits>

namespace dunedaq {
namespace dfmessages {
/**
 * @brief This message represents a request for data sent to a single component of the DAQ
 */
struct DataRequest
{
  /**
   * @brief The readout mode that should be used when fulfilling this request
   */
  enum class mode_t : int
  {
    kLocalizedReadout, ///< Normal readout
    kExtendedReadout   ///< Special readout mode to be used for SNB
  };

  request_number_t m_request_number = std::numeric_limits<request_number_t>::max(); ///< The number of the request
  trigger_number_t m_trigger_number = std::numeric_limits<trigger_number_t>::max(); ///< Trigger number the request corresponds to
  run_number_t m_run_number = std::numeric_limits<run_number_t>::max();         ///< The current run number

  timestamp_t m_trigger_timestamp = std::numeric_limits<timestamp_t>::max();  ///< Timestamp of trigger
  timestamp_diff_t m_window_offset = std::numeric_limits<timestamp_diff_t>::max(); ///< Start readout window this many ticks before the trigger timestamp
  timestamp_diff_t m_window_width = std::numeric_limits<timestamp_diff_t>::max();  ///< Window should be open for a total of this many ticks

  mode_t m_request_mode = mode_t::kLocalizedReadout; ///< Mode of the request
};

} // namespace dfmessages
} // namespace dunedaq

#endif // DFMESSAGES_INCLUDE_DFMESSAGES_DATAREQUEST_HPP_
