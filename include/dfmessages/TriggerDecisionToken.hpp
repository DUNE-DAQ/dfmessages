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

#include "serialization/Serialization.hpp"

namespace dunedaq {
namespace dfmessages {
/**
 * @brief Represents a message indicating that the DataFlow has one additional buffer available
 */
struct TriggerDecisionToken
{
  run_number_t run_number; ///< The run number that this token corresponds to

  DUNE_DAQ_SERIALIZE(TriggerDecisionToken, run_number);
};
} // namespace dfmessages
} // namespace dunedaq

#endif // DFMESSAGES_INCLUDE_DFMESSAGES_TRIGGERDECISIONTOKEN_HPP_
