/**
 * @file Common.hpp Common type definitions and namespace-scope functions
 *
 * This is part of the DUNE DAQ Application Framework, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#include <cstdint>
#include <map>
#include <sys/time.h>
#include <utility>

namespace dunedaq {
namespace dfmessages {
using run_number_t = uint32_t;
using trigger_number_t = uint64_t;
using request_number_t = uint64_t;

using timestamp_t = uint64_t;
using timestamp_diff_t = int64_t;

using trigger_type_t = uint32_t;
using system_time_t = uint64_t;

} // namespace dfmessages
} // namespace dunedaq