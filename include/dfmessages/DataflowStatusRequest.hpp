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
#include "dfmessages/Types.hpp"
#include "serialization/Serialization.hpp"

namespace dunedaq {

namespace dfmessages {

struct DataflowStatusRequest
{
  run_number_t run_number{ TypeDefaults::s_invalid_run_number }; ///< The current run number
  trigger_number_t trigger_number{
    TypeDefaults::s_invalid_trigger_number
  }; ///< The trigger number associated with this request
  std::string reply_destination = "";

  DUNE_DAQ_SERIALIZE(DataflowStatusRequest,
                     run_number,
                     trigger_number,
                     reply_destination);
};
} // namespace dfmessages
DUNE_DAQ_SERIALIZABLE(dfmessages::DataflowStatusRequest, "DataflowStatusRequest");
} // namespace dunedaq

#endif // DFMESSAGES_INCLUDE_DFMESSAGES_DATAFLOWSTATUSREQUEST_HPP_