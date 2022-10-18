/**
 * @file dfmessages/TRMonRequest.hpp TRMonRequest Message Declaration
 *
 * This is part of the DUNE DAQ Application Framework, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#ifndef DFMESSAGES_INCLUDE_DFMESSAGES_TRMONREQUEST_HPP_
#define DFMESSAGES_INCLUDE_DFMESSAGES_TRMONREQUEST_HPP_

#include "dfmessages/Types.hpp"

#include "serialization/Serialization.hpp"

#include <string>

namespace dunedaq {
namespace dfmessages {

/**
 * @brief This message represents a request for a TriggerRecord to be used in Monitoring
 */
struct TRMonRequest
{

  request_number_t request_number{ TypeDefaults::s_invalid_request_number }; ///< The number of the request
  trigger_type_t trigger_type{ TypeDefaults::s_invalid_trigger_type }; ///< The trigger type that is being requested
  run_number_t run_number{ TypeDefaults::s_invalid_run_number };       ///< The current run number
  std::string data_destination; ///< The Monitoring destination that the TR should be sent to

  DUNE_DAQ_SERIALIZE(TRMonRequest, request_number, trigger_type, run_number, data_destination);
};

/**
 * @brief Special values for TRMonRequest trigger type
 */
class TRMonTriggerTypes
{
public:
  static constexpr trigger_type_t s_any_trigger_type = 0xffff;
};

} // namespace dfmessages
DUNE_DAQ_SERIALIZABLE(dfmessages::TRMonRequest, "TRMonRequest");
} // namespace dunedaq

#endif // DFMESSAGES_INCLUDE_DFMESSAGES_TRMONREQUEST_HPP_
