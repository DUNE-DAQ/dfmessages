/**
 * @file DataRequest.hpp DataRequest Message Declaration
 *
 * This is part of the DUNE DAQ Application Framework, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#ifndef DFMESSAGES_INCLUDE_DFMESSAGES_DATAREQUEST_HPP_
#define DFMESSAGES_INCLUDE_DFMESSAGES_DATAREQUEST_HPP_

#include "Types.hpp"

#include <vector>

namespace dunedaq {
namespace dfmessages {
struct DataRequest
{
  enum class mode_t : int
  {
    LocalizedReadout,
    ExtendedReadout
  };

  request_number_t RequestNumber;
  trigger_number_t TriggerNumber;
  run_number_t RunNumber;

  timestamp_t TriggerTimestamp;
  timestamp_diff_t WindowOffset;
  timestamp_t WindowWidth;

  mode_t RequestMode;
};

} // namespace dfmessages
} // namespace dunedaq

#endif // DFMESSAGES_INCLUDE_DFMESSAGES_DATAREQUEST_HPP_