#include "Common.hpp"

namespace dunedaq {
namespace dfmessages {
struct TriggerInhibit
{
  bool Busy;
  timestamp_t DAQTime;
  system_time_t SystemTime;

  TriggerInhibit(bool busy, timestamp_t daqTime, system_time_t sysTime = gettimeofday_us())
    : Busy(busy)
    , DAQTime(daqTime)
    , SystemTime(sysTime)
  {}
};
} // namespace dfmessages
} // namespace dunedaq