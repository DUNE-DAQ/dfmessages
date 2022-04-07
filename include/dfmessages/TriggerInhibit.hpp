/**
 * @file dfmessages/TriggerInhibit.hpp TriggerInhibit Message Declaration
 *
 * This is part of the DUNE DAQ Application Framework, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#ifndef DFMESSAGES_INCLUDE_DFMESSAGES_TRIGGERINHIBIT_HPP_
#define DFMESSAGES_INCLUDE_DFMESSAGES_TRIGGERINHIBIT_HPP_

#include "dfmessages/Types.hpp"
#include "serialization/Serialization.hpp"

#include <cstddef>

namespace dunedaq {
namespace dfmessages {
/**
 * @brief Represents a message indicating whether TriggerDecisions should be inhibited
 */
struct TriggerInhibit
{
  bool busy = false;           ///< Whether the system is busy
  run_number_t run_number = 0; ///< Current run number

  DUNE_DAQ_SERIALIZE(TriggerInhibit, busy, run_number);
};
static_assert(sizeof(TriggerInhibit) == 8, "TriggerInhibit size unexpected!");
static_assert(offsetof(TriggerInhibit, busy) == 0, "TriggerInhibit busy field not at expected offset!");
static_assert(offsetof(TriggerInhibit, run_number) == 4, "TriggerInhibit run_number field not at expected offset!");
} // namespace dfmessages
} // namespace dunedaq

#endif // DFMESSAGES_INCLUDE_DFMESSAGES_TRIGGERINHIBIT_HPP_
