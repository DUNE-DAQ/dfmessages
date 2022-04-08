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

#include <cstddef>
#include <limits>

namespace dunedaq {
namespace dfmessages {
/**
 * @brief A synthetic message used to ensure that all elements of a DAQ system are synchronized.
 */
struct TimeSync
{
  /// The current DAQ time
  timestamp_t daq_time{ TypeDefaults::s_invalid_timestamp };
  /// The current system time
  system_time_t system_time{ TypeDefaults::s_invalid_system_time };
  /// Sequence Number of this message, for debugging
  uint64_t sequence_number{ 0 }; // NOLINT(build/unsigned)
  /// Run number at time of creation
  run_number_t run_number{ 0 };
  /// PID of the creating process, for debugging
  uint32_t source_pid{ 0 }; // NOLINT(build/unsigned)

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
static_assert(sizeof(TimeSync) == 32, "TimeSync size unexpected!");
static_assert(offsetof(TimeSync, daq_time) == 0, "TimeSync daq_time field not at expected offset!");
static_assert(offsetof(TimeSync, system_time) == 8, "TimeSync system_time field not at expected offset!");
static_assert(offsetof(TimeSync, sequence_number) == 16, "TimeSync sequence_number field not at expected offset!");
static_assert(offsetof(TimeSync, run_number) == 24, "TimeSync run_number field not at expected offset!");
static_assert(offsetof(TimeSync, source_pid) == 28, "TimeSync source_pid field not at expected offset!");
} // namespace dfmessages
DUNE_DAQ_SERIALIZABLE(dfmessages::TimeSync);
} // namespace dunedaq

#endif // DFMESSAGES_INCLUDE_DFMESSAGES_TIMESYNC_HPP_
