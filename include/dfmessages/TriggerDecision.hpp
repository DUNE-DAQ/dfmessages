/**
 * @file dfmessages/TriggerDecision.hpp TriggerDecision Message Declaration
 *
 * This is part of the DUNE DAQ Application Framework, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#ifndef DFMESSAGES_INCLUDE_DFMESSAGES_TRIGGERDECISION_HPP_
#define DFMESSAGES_INCLUDE_DFMESSAGES_TRIGGERDECISION_HPP_

#include "dfmessages/ComponentRequest_serialization.hpp"
#include "dfmessages/Types.hpp"

#include "serialization/Serialization.hpp"

#include <limits>
#include <map>
#include <vector>

namespace dunedaq {
namespace dfmessages {
/**
 * @brief A message containing information about a Trigger from Data Selection (or a TriggerDecisionEmulator)
 */
struct TriggerDecision
{
  trigger_number_t trigger_number{
    TypeDefaults::s_invalid_trigger_number
  }; ///< The trigger number assigned to this TriggerDecision
  run_number_t run_number{ TypeDefaults::s_invalid_run_number }; ///< The current run number

  timestamp_t trigger_timestamp{ TypeDefaults::s_invalid_timestamp };  ///< The DAQ timestamp
  trigger_type_t trigger_type{ TypeDefaults::s_invalid_trigger_type }; ///< The type of the trigger
  ReadoutType readout_type{ ReadoutType::kInvalid }; ///< The type of readout to use (i.e. where to route data)

  std::vector<ComponentRequest> components; ///< The DAQ components which should be read out to create the TriggerRecord

  DUNE_DAQ_SERIALIZE(TriggerDecision,
                     trigger_number,
                     run_number,
                     trigger_timestamp,
                     trigger_type,
                     readout_type,
                     components);
};
} // namespace dfmessages

DUNE_DAQ_SERIALIZABLE(dfmessages::TriggerDecision, "TriggerDecision");

} // namespace dunedaq

#endif // DFMESSAGES_INCLUDE_DFMESSAGES_TRIGGERDECISION_HPP_
