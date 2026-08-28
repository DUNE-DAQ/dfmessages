/**
 * @file dfmessages/DataflowStatus.hpp DataflowStatus Message Declaration
 *
 * This is part of the DUNE DAQ Application Framework, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#ifndef DFMESSAGES_INCLUDE_DFMESSAGES_DATAFLOWSTATUS_HPP_
#define DFMESSAGES_INCLUDE_DFMESSAGES_DATAFLOWSTATUS_HPP_

#include "dfmessages/SourceID_serialization.hpp"
#include "dfmessages/TriggerId.hpp"
#include "dfmessages/Types.hpp"
#include "serialization/Serialization.hpp"

#include <set>
#include <string>

namespace dunedaq {
namespace dfmessages {

struct DataflowStatus
{
  TriggerId trigger_id{};             ///< The TriggerId of the TriggerRecord that this status is associated with
  size_t iteration_number{ 0 };       ///< The iteration number associated with this state
  std::string decision_destination{}; ///< The connection name for the TriggerDecision destination
  std::string request_destination{};  ///< The connection name for the DataflowStatusRequest destination

  trigger_type_t trigger_type_mask{ 0 };

  bool is_busy{ false }; ///< Whether the dataflow is currently busy (i.e. above the high water mark)
  size_t busy_threshold{ 0 };
  size_t free_threshold{ 0 };
  std::set<TriggerId> triggers_building;
  std::set<TriggerId> triggers_writing;
  std::set<TriggerId> recently_completed_triggers; ///< The set of trigger numbers that have recently completed
                                                          ///< (i.e. have been written to disk)
  size_t trigger_records_processed{ 0 }; ///< The total number of TriggerRecords processed for the current run
  size_t data_size_written{ 0 };         ///< The total size of data written for the current run, in bytes

  DUNE_DAQ_SERIALIZE(DataflowStatus,
                     trigger_id,
                     iteration_number,
                     decision_destination,
                     request_destination,
                     trigger_type_mask,
                     is_busy,
                     busy_threshold,
                     free_threshold,
                     triggers_building,
                     triggers_writing,
                     recently_completed_triggers,
                     trigger_records_processed,
                     data_size_written);
};
} // namespace dfmessages
DUNE_DAQ_SERIALIZABLE(dfmessages::DataflowStatus, "DataflowStatus");
} // namespace dunedaq

#endif // DFMESSAGES_INCLUDE_DFMESSAGES_DATAFLOWSTATUS_HPP_