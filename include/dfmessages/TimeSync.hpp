/**
 * @file TimeSync.hpp TimeSync Message Declaration
 *
 * This is part of the DUNE DAQ Application Framework, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */
#include "Common.hpp"

namespace dunedaq {
namespace dfmessages {
struct TimeSync
{
  timestamp_t DAQTime;
  system_time_t SystemTime;

  TimeSync(timestamp_t daqTime, system_time_t sysTime = gettimeofday_us())
    : DAQTime(daqTime)
    , SystemTime(sysTime)
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