/**
 * @file dfmessages/TRBCompletion.hpp TRBCompletion Message Declaration
 *
 * This is part of the DUNE DAQ Application Framework, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#ifndef DFMESSAGES_INCLUDE_DFMESSAGES_TRBCOMPLETION_HPP_
#define DFMESSAGES_INCLUDE_DFMESSAGES_TRBCOMPLETION_HPP_

#include "dfmessages/SourceID_serialization.hpp"
#include "dfmessages/TriggerId.hpp"
#include "dfmessages/Types.hpp"
#include "serialization/Serialization.hpp"

namespace dunedaq {

namespace dfmessages {

struct TRBCompletion
{
  TriggerId trigger_id;               ///< The TriggerId of the completed TriggerRecord
  daqdataformats::SourceID source_id; ///< The SourceID of the TRB
  sequence_number_t trigger_record_max_sequence_number{
    TypeDefaults::s_invalid_sequence_number
  }; ///< The max sequence number for this TriggerRecord
  DUNE_DAQ_SERIALIZE(TRBCompletion, trigger_id, source_id, trigger_record_max_sequence_number);
};
} // namespace dfmessages
DUNE_DAQ_SERIALIZABLE(dfmessages::TRBCompletion, "TRBCompletion");
} // namespace dunedaq

#endif // DFMESSAGES_INCLUDE_DFMESSAGES_TRBCOMPLETION_HPP_