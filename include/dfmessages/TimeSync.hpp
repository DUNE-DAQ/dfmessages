/**
 * @file TimeSync.hpp TimeSync Message Declaration
 *
 * This is part of the DUNE DAQ Application Framework, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#ifndef DFMESSAGES_INCLUDE_DFMESSAGES_TIMESYNC_HPP_
#define DFMESSAGES_INCLUDE_DFMESSAGES_TIMESYNC_HPP_

#include "dfmessages/Types.hpp"

namespace dunedaq {
namespace dfmessages {
struct TimeSync
{
  timestamp_t DAQ_time;
  system_time_t system_time;

  explicit TimeSync(timestamp_t daq_time, system_time_t sys_time = gettimeofday_us())
    : DAQ_time(daq_time)
    , system_time(sys_time)
  {}

  static system_time_t gettimeofday_us()
  {
    struct timeval tv;
    gettimeofday(&tv, nullptr);
    return static_cast<system_time_t>(tv.tv_sec) * 1000000 + tv.tv_usec;
  }
};
} // namespace dfmessages
} // namespace dunedaq

#endif // DFMESSAGES_INCLUDE_DFMESSAGES_TIMESYNC_HPP_