/**
 * @file TriggerInhibit.hpp TriggerInhibit Message Declaration
 *
 * This is part of the DUNE DAQ Application Framework, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

namespace dunedaq {
namespace dfmessages {
struct TriggerInhibit
{
  bool Busy;
};
} // namespace dfmessages
} // namespace dunedaq