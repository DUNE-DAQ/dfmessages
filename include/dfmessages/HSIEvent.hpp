/**
 * @file dfmessages/HSIEvent.hpp HSIEvent Message Declaration
 *
 * This is part of the DUNE DAQ Application Framework, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#ifndef DFMESSAGES_INCLUDE_DFMESSAGES_HSIEVENT_HPP_
#define DFMESSAGES_INCLUDE_DFMESSAGES_HSIEVENT_HPP_

#include "daqdataformats/Types.hpp"
#include "dfmessages/Types.hpp"

#include "serialization/Serialization.hpp"

#include <cstddef>
#include <limits>

namespace dunedaq {
namespace dfmessages {
/**
 * @brief A message used to convey an HSI event.
 */
struct HSIEvent
{
  uint32_t header{ 0 };     ///< Header field. Only contains HSI device ID at the moment // NOLINT(build/unsigned)
  uint32_t signal_map{ 0 }; ///< Bit map of signals. 1 bit, 1 signal // NOLINT(build/unsigned)
  daqdataformats::timestamp_t timestamp{ dfmessages::TypeDefaults::s_invalid_timestamp }; ///< Timestamp of HSI event
  uint32_t sequence_counter{ 0 }; ///< Event sequence number // NOLINT(build/unsigned)
  run_number_t run_number{ 0 };

  HSIEvent() = default;

  /**
   * @brief Construct a HSIEvent message
   * @param header Feild containing HSI device ID
   * @param signal_map Bit map of signal(s) with detected edge(s)
   * @param timestamp Timestamp of edge(s)
   * @param sequence_counter Sequence counter of generated HSI messages
   * @param run_number Run number in which the message is created
   */
  explicit HSIEvent(uint32_t head,    // NOLINT(build/unsigned)
                    uint32_t signals, // NOLINT(build/unsigned)
                    daqdataformats::timestamp_t ts,
                    uint32_t seq_count,   // NOLINT(build/unsigned)
                    run_number_t run_num) // NOLINT(build/unsigned)
    : header(head)
    , signal_map(signals)
    , timestamp(ts)
    , sequence_counter(seq_count)
    , run_number(run_num)
  {}

  DUNE_DAQ_SERIALIZE(HSIEvent, header, signal_map, timestamp, sequence_counter, run_number);
};
static_assert(sizeof(HSIEvent) == 24, "HSIEvent size unexpected!");
static_assert(offsetof(HSIEvent, header) == 0, "HSIEvent header field not at expected offset!");
static_assert(offsetof(HSIEvent, signal_map) == 4, "HSIEvent signal_map field not at expected offset!");
static_assert(offsetof(HSIEvent, timestamp) == 8, "HSIEvent timestamp field not at expected offset!");
static_assert(offsetof(HSIEvent, sequence_counter) == 16, "HSIEvent sequence_counter field not at expected offset!");
static_assert(offsetof(HSIEvent, run_number) == 20, "HSIEvent run_number field not at expected offset!");
} // namespace dfmessages

DUNE_DAQ_SERIALIZABLE(dfmessages::HSIEvent);

} // namespace dunedaq

#endif // DFMESSAGES_INCLUDE_DFMESSAGES_HSIEVENT_HPP_
