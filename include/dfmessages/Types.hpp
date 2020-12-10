/**
 * @file Types.hpp Type definitions used in dfmessages
 *
 * This is part of the DUNE DAQ Application Framework, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#ifndef DFMESSAGES_INCLUDE_DFMESSAGES_TYPES_HPP_
#define DFMESSAGES_INCLUDE_DFMESSAGES_TYPES_HPP_

#include <cstdint>
#include <map>
#include <sys/time.h>
#include <utility>

namespace dunedaq {
namespace dfmessages {
using run_number_t = uint32_t;     // NOLINT(build/unsigned)
using trigger_number_t = uint64_t; // NOLINT(build/unsigned)
using request_number_t = uint64_t; // NOLINT(build/unsigned)

using timestamp_t = uint64_t;     // NOLINT(build/unsigned)
using timestamp_diff_t = int64_t; // NOLINT(build/unsigned)

using trigger_type_t = uint32_t; // NOLINT(build/unsigned)
using system_time_t = uint64_t;  // NOLINT(build/unsigned)

} // namespace dfmessages
} // namespace dunedaq

#endif // DFMESSAGES_INCLUDE_DFMESSAGES_TYPES_HPP_