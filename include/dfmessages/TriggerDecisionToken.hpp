/**
 * @file dfmessages/TriggerDecisionToken.hpp TriggerDecisionToken Message Declaration
 *
 * This is part of the DUNE DAQ Application Framework, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#ifndef DFMESSAGES_INCLUDE_DFMESSAGES_TRIGGERDECISIONTOKEN_HPP_
#define DFMESSAGES_INCLUDE_DFMESSAGES_TRIGGERDECISIONTOKEN_HPP_

#include "dfmessages/Types.hpp"
#include "dfmessages/TriggerId.hpp"

#include "serialization/Serialization.hpp"

#include <string>

namespace dunedaq {
namespace dfmessages {
/**
 * @brief Represents a message indicating that the DataFlow has one additional buffer available
 */
struct TriggerDecisionToken
{
  run_number_t run_number{ TypeDefaults::s_invalid_run_number }; ///< The run number that this token corresponds to
  TriggerId trigger_id; ///< An optional trigger ID that this token represents completion of
  std::string writer_identifier;
  size_t data_size{ 0 };

  DUNE_DAQ_SERIALIZE(TriggerDecisionToken, run_number, trigger_id, writer_identifier, data_size);
};
} // namespace dfmessages
DUNE_DAQ_SERIALIZABLE(dfmessages::TriggerDecisionToken, "TriggerDecisionToken");
} // namespace dunedaq

#endif // DFMESSAGES_INCLUDE_DFMESSAGES_TRIGGERDECISIONTOKEN_HPP_
