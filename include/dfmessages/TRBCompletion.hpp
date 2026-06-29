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
#include "dfmessages/Types.hpp"
#include "serialization/Serialization.hpp"

namespace dunedaq {

namespace dfmessages {

struct TRBCompletion
{
  run_number_t run_number{ TypeDefaults::s_invalid_run_number }; ///< The current run number
  trigger_number_t trigger_number{
    TypeDefaults::s_invalid_trigger_number
  }; ///< The trigger number assigned to this TriggerDecision
  daqdataformats::SourceID source_id;                            ///< The SourceID of the TRB
  DUNE_DAQ_SERIALIZE(TRBCompletion, run_number, trigger_number, source_id);
};
} // namespace dfmessages
DUNE_DAQ_SERIALIZABLE(dfmessages::TRBCompletion, "TRBCompletion");
} // namespace dunedaq

#endif // DFMESSAGES_INCLUDE_DFMESSAGES_TRBCOMPLETION_HPP_