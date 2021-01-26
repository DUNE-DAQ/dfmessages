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

#include <vector>

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
    kExtendedReadout,  ///< Special readout mode to be used for SNB
    kInvalidMode       ///< Not a valid mode, used for initialization. Should always be last
  };

  request_number_t m_request_number{ TypeDefaults::s_invalid_request_number }; ///< The number of the request
  trigger_number_t m_trigger_number{
    TypeDefaults::s_invalid_trigger_number
  };                                                               ///< Trigger number the request corresponds to
  run_number_t m_run_number{ TypeDefaults::s_invalid_run_number }; ///< The current run number

  timestamp_t m_trigger_timestamp{ TypeDefaults::s_invalid_timestamp }; ///< Timestamp of trigger
  timestamp_diff_t m_window_offset{
    TypeDefaults::s_invalid_timestamp_diff
  }; ///< Start readout window this many ticks before the trigger timestamp
  timestamp_diff_t m_window_width{
    TypeDefaults::s_invalid_timestamp_diff
  }; ///< Window should be open for a total of this many ticks

  mode_t m_request_mode{ mode_t::kInvalidMode }; ///< Mode of the request
};

} // namespace dfmessages
} // namespace dunedaq

#endif // DFMESSAGES_INCLUDE_DFMESSAGES_DATAREQUEST_HPP_