/**
 * @file dfmessages/Types.hpp Type definitions used in dfmessages
 *
 * This is part of the DUNE DAQ Application Framework, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#ifndef DFMESSAGES_INCLUDE_DFMESSAGES_TYPES_HPP_
#define DFMESSAGES_INCLUDE_DFMESSAGES_TYPES_HPP_

#include "dataformats/ComponentRequest.hpp"
#include "dataformats/GeoID.hpp"
#include "dataformats/Types.hpp"

#include <cstdint>
#include <map>
#include <sys/time.h>
#include <utility>

/**
 * @brief The DUNE-DAQ namespace
 */
namespace dunedaq {
/**
 * @brief Dataflow Messages
 */
namespace dfmessages {
using GeoID = dataformats::GeoID;                       ///< Copy dataformats::GeoID
using ComponentRequest = dataformats::ComponentRequest; ///< Copy dataformats::ComponentRequest
using run_number_t = dataformats::run_number_t;         ///< Copy dataformats::run_number_t
using trigger_number_t = dataformats::trigger_number_t; ///< Copy dataformats::trigger_number_t
/**
 * @brief A request number is represented using a 64-bit unsigned integer
 */
using request_number_t = uint64_t; // NOLINT(build/unsigned)

using timestamp_t = dataformats::timestamp_t;           ///< Copy dataformats::timestamp_t
using timestamp_diff_t = dataformats::timestamp_diff_t; ///< Copy dataformats::timestamp_diff_t

using trigger_type_t = dataformats::trigger_type_t; ///< Copy dataformats::trigger_type_t
/**
 * @brief System times are represented using a 64-bit unsigned integer
 * This number is defined as the number of microseconds since the system epoch
 */
using system_time_t = uint64_t; // NOLINT(build/unsigned)

class TypeDefaults : public dataformats::TypeDefaults
{
public:
  static constexpr request_number_t s_invalid_request_number =
    std::numeric_limits<request_number_t>::max(); ///< An invalid request number
  static constexpr system_time_t s_invalid_system_time = 0; ///< An invalid system time
};

} // namespace dfmessages
} // namespace dunedaq

#endif // DFMESSAGES_INCLUDE_DFMESSAGES_TYPES_HPP_