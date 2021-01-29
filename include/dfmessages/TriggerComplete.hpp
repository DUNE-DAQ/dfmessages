/**
 * @file dfmessages/TriggerComplete.hpp TriggerComplete Message Declaration
 *
 * This is part of the DUNE DAQ Application Framework, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#ifndef DFMESSAGES_INCLUDE_DFMESSAGES_TRIGGERCOMPLETE_HPP_
#define DFMESSAGES_INCLUDE_DFMESSAGES_TRIGGERCOMPLETE_HPP_

#include "dfmessages/Types.hpp"

namespace dunedaq {
namespace dfmessages {
/**
 * @brief Represents a message indicating that a given TriggerDecision has been completely processed by the DataFlow
 */
struct TriggerComplete
{
  trigger_number_t m_trigger_number; ///< The trigger number of the completed trigger
  run_number_t m_run_number;         ///< The run number of the completed trigger
};
} // namespace dfmessages
} // namespace dunedaq

#endif // DFMESSAGES_INCLUDE_DFMESSAGES_TRIGGERCOMPLETE_HPP_