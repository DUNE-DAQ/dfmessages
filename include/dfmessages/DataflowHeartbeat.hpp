/**
 * @file dfmessages/DataflowHeartbeat.hpp DataflowHeartbeat Message Declaration
 *
 * This is part of the DUNE DAQ Application Framework, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#ifndef DFMESSAGES_INCLUDE_DFMESSAGES_DATAFLOWHEARTBEAT_HPP_
#define DFMESSAGES_INCLUDE_DFMESSAGES_DATAFLOWHEARTBEAT_HPP_

#include "dfmessages/Types.hpp"

#include "serialization/Serialization.hpp"

#include <string>

namespace dunedaq {
namespace dfmessages {
/**
 * @brief Represents a message indicating the current status of a DataFlow application
 */
struct DataflowHeartbeat
{
  run_number_t run_number{ TypeDefaults::s_invalid_run_number }; ///< The run number that this heartbeat corresponds to
  std::vector<trigger_number_t> recent_completed_triggers{}; ///< A list of recently-completed triggers
  std::vector<trigger_number_t> outstanding_decisions{}; ///< A list of trigger decisions that the app is currently working on

  std::string
    decision_destination; ///< Connection name for TriggerDecisions sent to the Dataflow process originating this heartbeat

  DUNE_DAQ_SERIALIZE(DataflowHeartbeat, run_number, recent_completed_triggers, outstanding_decisions, decision_destination);
};
} // namespace dfmessages
DUNE_DAQ_SERIALIZABLE(dfmessages::DataflowHeartbeat, "DataflowHeartbeat");
} // namespace dunedaq

#endif // DFMESSAGES_INCLUDE_DFMESSAGES_DATAFLOWHEARTBEAT_HPP_
