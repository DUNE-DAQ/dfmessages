/**
 * @file DataRequest.hpp DataRequest Message Declaration
 *
 * This is part of the DUNE DAQ Application Framework, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#ifndef DFMESSAGES_INCLUDE_DFMESSAGES_DATAREQUEST_HPP_
#define DFMESSAGES_INCLUDE_DFMESSAGES_DATAREQUEST_HPP_

#include "dfmessages/Types.hpp"

#include <vector>

namespace dunedaq {
namespace dfmessages {
struct DataRequest
{
  enum class mode_t : int
  {
    kLocalizedReadout,
    kExtendedReadout
  };

  request_number_t request_number;
  trigger_number_t trigger_number;
  run_number_t run_number;

  timestamp_t trigger_timestamp;
  timestamp_diff_t window_offset;
  timestamp_t window_width;

  mode_t request_mode;
};

} // namespace dfmessages
} // namespace dunedaq

#endif // DFMESSAGES_INCLUDE_DFMESSAGES_DATAREQUEST_HPP_