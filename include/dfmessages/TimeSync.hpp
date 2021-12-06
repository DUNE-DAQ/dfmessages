/**
 * @file dfmessages/TimeSync.hpp TimeSync Message Declaration
 *
 * This is part of the DUNE DAQ Application Framework, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#ifndef DFMESSAGES_INCLUDE_DFMESSAGES_TIMESYNC_HPP_
#define DFMESSAGES_INCLUDE_DFMESSAGES_TIMESYNC_HPP_

#include "dfmessages/Types.hpp"

#include "serialization/Serialization.hpp"

#include <limits>

namespace dunedaq {
namespace dfmessages {
/**
 * @brief A synthetic message used to ensure that all elements of a DAQ system are synchronized.
 */
struct TimeSync
{
  timestamp_t daq_time{ TypeDefaults::s_invalid_timestamp };        ///< The current DAQ time
  system_time_t system_time{ TypeDefaults::s_invalid_system_time }; ///< The current system time
  run_number_t run_number{ 0 };
  size_t sequence_number{ 0 };
  size_t source_pid{ 0 };

  TimeSync() = default;

  /**
   * @brief Construct a TimeSync message
   * @param daq_time The current DAQ time
   * @param sys_time The current system time. Will be initialized to gettimeofday_us() if unset
   */
  explicit TimeSync(timestamp_t daq_time, system_time_t sys_time = gettimeofday_us())
    : daq_time(daq_time)
    , system_time(sys_time)
  {}

  /**
   * @brief Get the current system time
   * @return A system_time_t containing the current system time
   *
   * system_time_t values are defined as the number of microseconds since the system clock epoch
   */
  static system_time_t gettimeofday_us()
  {
    struct timeval tv;
    gettimeofday(&tv, nullptr);
    return static_cast<system_time_t>(tv.tv_sec) * 1000000 + tv.tv_usec;
  }

  DUNE_DAQ_SERIALIZE(TimeSync, daq_time, system_time, run_number, sequence_number, source_pid);
};
} // namespace dfmessages
} // namespace dunedaq

#endif // DFMESSAGES_INCLUDE_DFMESSAGES_TIMESYNC_HPP_
