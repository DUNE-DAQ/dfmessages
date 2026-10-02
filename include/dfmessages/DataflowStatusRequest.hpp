/**
 * @file dfmessages/DataflowStatusRequest.hpp DataflowStatusRequest Message Declaration
 *
 * This is part of the DUNE DAQ Application Framework, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#ifndef DFMESSAGES_INCLUDE_DFMESSAGES_DATAFLOWSTATUSREQUEST_HPP_
#define DFMESSAGES_INCLUDE_DFMESSAGES_DATAFLOWSTATUSREQUEST_HPP_

#include "dfmessages/SourceID_serialization.hpp"
#include "dfmessages/TriggerId.hpp"
#include "dfmessages/Types.hpp"
#include "serialization/Serialization.hpp"

#include <string>

namespace dunedaq {

namespace dfmessages {

struct DataflowStatusRequest
{
  TriggerId trigger_id{};       ///< The TriggerId of the trigger for which status is requested
  size_t iteration_number{ 0 }; ///< The iteration number associated with this request
  std::string reply_destination = "";

  DUNE_DAQ_SERIALIZE(DataflowStatusRequest, trigger_id, iteration_number, reply_destination);
};
} // namespace dfmessages
DUNE_DAQ_SERIALIZABLE(dfmessages::DataflowStatusRequest, "DataflowStatusRequest");
} // namespace dunedaq

#endif // DFMESSAGES_INCLUDE_DFMESSAGES_DATAFLOWSTATUSREQUEST_HPP_