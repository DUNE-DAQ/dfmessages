/**
 * @file ComponentRequest.hpp Represents the requested timestamp range for a single component
 *
 * This is part of the DUNE DAQ Application Framework, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#ifndef DFMESSAGES_INCLUDE_DFMESSAGES_COMPONENTREQUEST_HPP_
#define DFMESSAGES_INCLUDE_DFMESSAGES_COMPONENTREQUEST_HPP_

#include "Types.hpp"

namespace dunedaq {
namespace dfmessages {
struct ComponentRequest
{
  timestamp_t RequestTimestamp;
  timestamp_diff_t RequestOffset;
  timestamp_t RequestWidth;
};
} // namespace dfmessages
} // namespace dunedaq

#endif // DFMESSAGES_INCLUDE_DFMESSAGES_COMPONENTREQUEST_HPP_