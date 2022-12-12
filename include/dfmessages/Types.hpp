/**
 * @file dfmessages/Types.hpp Type definitions used in dfmessages
 *
 * This is part of the DUNE DAQ Application Framework, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#ifndef DFMESSAGES_INCLUDE_DFMESSAGES_TYPES_HPP_
#define DFMESSAGES_INCLUDE_DFMESSAGES_TYPES_HPP_

#include "daqdataformats/ComponentRequest.hpp"
#include "daqdataformats/SourceID.hpp"
#include "daqdataformats/Types.hpp"

#include "serialization/Serialization.hpp"

#include <cstdint>
#include <limits>
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
using SourceID = daqdataformats::SourceID;                 ///< Copy daqdataformats::SourceID
using ComponentRequest = daqdataformats::ComponentRequest; ///< Copy daqdataformats::ComponentRequest
using run_number_t = daqdataformats::run_number_t;         ///< Copy daqdataformats::run_number_t
using trigger_number_t = daqdataformats::trigger_number_t; ///< Copy daqdataformats::trigger_number_t
/**
 * @brief A request number is represented using a 64-bit unsigned integer
 */
using request_number_t = uint64_t;                           // NOLINT(build/unsigned)
using sequence_number_t = daqdataformats::sequence_number_t; ///< Copy daqdataformats::sequence_number_t

using timestamp_t = daqdataformats::timestamp_t;           ///< Copy daqdataformats::timestamp_t
using timestamp_diff_t = daqdataformats::timestamp_diff_t; ///< Copy daqdataformats::timestamp_diff_t

using trigger_type_t = daqdataformats::trigger_type_t; ///< Copy daqdataformats::trigger_type_t

/**
 * @brief Which type of readout to use for TriggerDecision and DataRequest
 */
enum class ReadoutType : uint16_t // NOLINT(build/unsigned)
{
  kInvalid = 0,    ///< Invalid type, used for initialization
  kLocalized = 1,  ///< Local readout, send Fragments to dataflow
  kExtended = 2,   ///< Extended readout, write data to local storage
  kMonitoring = 3, ///< Monitoring readout
};

/**
 * @brief System times are represented using a 64-bit unsigned integer
 * This number is defined as the number of microseconds since the system epoch
 */
using system_time_t = uint64_t; // NOLINT(build/unsigned)

/**
 * @brief Default values for dfmessages types
 */
class TypeDefaults : public daqdataformats::TypeDefaults
{
public:
  static constexpr request_number_t s_invalid_request_number =
    std::numeric_limits<request_number_t>::max();           ///< An invalid request number
  static constexpr system_time_t s_invalid_system_time = 0; ///< An invalid system time
};

} // namespace dfmessages
} // namespace dunedaq

MSGPACK_ADD_ENUM(dunedaq::dfmessages::ReadoutType)

#endif // DFMESSAGES_INCLUDE_DFMESSAGES_TYPES_HPP_