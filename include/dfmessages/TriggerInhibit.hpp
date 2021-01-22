/**
 * @file dfmessages/TriggerInhibit.hpp TriggerInhibit Message Declaration
 *
 * This is part of the DUNE DAQ Application Framework, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#ifndef DFMESSAGES_INCLUDE_DFMESSAGES_TRIGGERINHIBIT_HPP_
#define DFMESSAGES_INCLUDE_DFMESSAGES_TRIGGERINHIBIT_HPP_

namespace dunedaq {
namespace dfmessages {
/**
 * @brief Represents a message indicating whether TriggerDecisions should be inhibited
*/
struct TriggerInhibit
{
  bool busy; ///< Whether the system is busy
};
} // namespace dfmessages
} // namespace dunedaq

#endif // DFMESSAGES_INCLUDE_DFMESSAGES_TRIGGERINHIBIT_HPP_