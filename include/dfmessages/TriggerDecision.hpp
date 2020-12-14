/**
 * @file TriggerDecision.hpp TriggerDecision Message Declaration
 *
 * This is part of the DUNE DAQ Application Framework, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#ifndef DFMESSAGES_INCLUDE_DFMESSAGES_TRIGGERDECISION_HPP_
#define DFMESSAGES_INCLUDE_DFMESSAGES_TRIGGERDECISION_HPP_

#include "dfmessages/Types.hpp"

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

  std::map<GeoID, ComponentRequest> Components;
};
} // namespace dfmessages
} // namespace dunedaq

#endif // DFMESSAGES_INCLUDE_DFMESSAGES_TRIGGERDECISION_HPP_