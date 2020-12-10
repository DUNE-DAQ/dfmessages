#include "Common.hpp"

#include <map>
#include <vector>

namespace dunedaq {
namespace dfmessages {
struct TriggerDecision
{
  trigger_number_t TriggerNumber;
  run_number_t RunNumber;

  timestamp_t TriggerTimestamp;
  trigger_type_t TriggerType;

  component_request_map_t Components;
};
} // namespace dfmessages
} // namespace dunedaq