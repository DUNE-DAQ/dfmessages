/**
 * @file TriggerDecision.hpp TriggerDecision Message Declaration
 *
 * This is part of the DUNE DAQ Application Framework, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

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