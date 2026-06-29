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
#include "dfmessages/Types.hpp"
#include "serialization/Serialization.hpp"

#include <set>

namespace dunedaq {
namespace dfmessages {

struct DataflowStatus
{
  run_number_t run_number{ TypeDefaults::s_invalid_run_number }; ///< The current run number
  trigger_number_t trigger_number{
    TypeDefaults::s_invalid_trigger_number
  }; ///< The trigger number associated with this state
  std::string decision_destination{}; ///< The connection name for the TriggerDecision destination

  trigger_type_t trigger_type_mask{ 0 };

  bool is_busy{ false }; ///< Whether the dataflow is currently busy (i.e. above the high water mark)
  size_t busy_threshold{ 0 };
  size_t free_threshold{ 0 };
  std::set<trigger_number_t> triggers_building;
  std::set<trigger_number_t> triggers_writing;
  size_t trigger_records_processed{ 0 }; ///< The total number of TriggerRecords processed for the current run
  size_t data_size_written{ 0 };         ///< The total size of data written for the current run, in bytes

  DUNE_DAQ_SERIALIZE(DataflowStatus,
                     run_number,
                     trigger_number,
                     decision_destination,
                     trigger_type_mask,
                     is_busy,
                     busy_threshold,
                     free_threshold,
                     triggers_building,
                     triggers_writing,
                     trigger_records_processed,
                     data_size_written);
};
} // namespace dfmessages
DUNE_DAQ_SERIALIZABLE(dfmessages::DataflowStatus, "DataflowStatus");
} // namespace dunedaq

#endif // DFMESSAGES_INCLUDE_DFMESSAGES_DATAFLOWSTATUS_HPP_