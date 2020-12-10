
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
};
} // namespace dfmessages
} // namespace dunedaq