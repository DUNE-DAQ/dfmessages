/**
 * @file Types.hpp Type definitions used in dfmessages
 *
 * This is part of the DUNE DAQ Application Framework, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#ifndef DFMESSAGES_INCLUDE_DFMESSAGES_TYPES_HPP_
#define DFMESSAGES_INCLUDE_DFMESSAGES_TYPES_HPP_

#include "cdf/GeoID.hpp"
#include "cdf/ComponentRequest.hpp"
#include "cdf/Types.hpp"

#include <cstdint>
#include <map>
#include <sys/time.h>
#include <utility>

namespace dunedaq {
namespace dfmessages {
using GeoID = cdf::GeoID;
using ComponentRequest = cdf::ComponentRequest;
using run_number_t = cdf::run_number_t;
using trigger_number_t = cdf::trigger_number_t;
using request_number_t = uint64_t; // NOLINT(build/unsigned)

using timestamp_t = cdf::timestamp_t;
using timestamp_diff_t = cdf::timestamp_diff_t;

using trigger_type_t = cdf::trigger_type_t;
using system_time_t = uint64_t; // NOLINT(build/unsigned)

} // namespace dfmessages
} // namespace dunedaq

#endif // DFMESSAGES_INCLUDE_DFMESSAGES_TYPES_HPP_