/**
 * @file dfmessages/DFODecision.hpp DFODecision Message Declaration
 *
 * This is part of the DUNE DAQ Application Framework, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#ifndef DFMESSAGES_INCLUDE_DFMESSAGES_DFODECISION_HPP_
#define DFMESSAGES_INCLUDE_DFMESSAGES_DFODECISION_HPP_

#include "dfmessages/TriggerDecision.hpp"
#include "dfmessages/Types.hpp"

#include "serialization/Serialization.hpp"

#include <limits>
#include <map>
#include <vector>

namespace dunedaq {
namespace dfmessages {
/**
 * @brief A message containing information about a Trigger from Data Selection (or a DFODecisionEmulator)
 */
struct DFODecision
{
  std::string dfo_id{ "UNKNOWN_DFO" };
  TriggerDecision trigger_decision{};
  std::vector<trigger_number_t> acknowledged_completions{};

  DUNE_DAQ_SERIALIZE(DFODecision, dfo_id, trigger_decision,
                     acknowledged_completions);
};
} // namespace dfmessages

DUNE_DAQ_SERIALIZABLE(dfmessages::DFODecision, "DFODecision");

} // namespace dunedaq

#endif // DFMESSAGES_INCLUDE_DFMESSAGES_DFODECISION_HPP_
