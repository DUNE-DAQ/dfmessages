#include "Common.hpp"

#include <map>
#include <vector>

namespace dunedaq {
namespace dfmessages {
struct TriggerDecision
{
  size_t TriggerNumber;
  timestamp_t TriggerTimestamp;
  timestamp_diff_t WindowOffset;
  timestamp_t WindowWidth;
  link_request_t Components;
};
} // namespace dfmessages
} // namespace dunedaq