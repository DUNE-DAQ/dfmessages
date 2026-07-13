
/**
 * @file TriggerId.hpp
 *
 * This is part of the DUNE DAQ Software Suite, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#ifndef DFMESSAGES_INCLUDE_DFMESSAGES_TRIGGERID_HPP_
#define DFMESSAGES_INCLUDE_DFMESSAGES_TRIGGERID_HPP_

#include "daqdataformats/Fragment.hpp"
#include "dfmessages/TriggerDecision.hpp"
#include "dfmessages/Types.hpp"

namespace dunedaq {

namespace dfmessages {

/**
 * @brief TriggerId is a little class that defines a unique identifier for a
 * trigger decision/record It also provides an operator < to be used by map to
 * optimise bookkeeping
 */
struct TriggerId
{

  TriggerId() = default;

  TriggerId(run_number_t r, trigger_number_t t, sequence_number_t s = TypeDefaults::s_invalid_sequence_number)
    : run_number(r)
    , trigger_number(t)
    , sequence_number(s)
  {
    ;
  }

  explicit TriggerId(const TriggerDecision& td, sequence_number_t s = TypeDefaults::s_invalid_sequence_number)
    : run_number(td.run_number)
    , trigger_number(td.trigger_number)
    , sequence_number(s)
  {
    ;
  }
  explicit TriggerId(daqdataformats::Fragment& f)
    : run_number(f.get_run_number())
    , trigger_number(f.get_trigger_number())
    , sequence_number(f.get_sequence_number())
  {
    ;
  }

  daqdataformats::run_number_t run_number{ TypeDefaults::s_invalid_run_number };
  daqdataformats::trigger_number_t trigger_number{ TypeDefaults::s_invalid_trigger_number };
  daqdataformats::sequence_number_t sequence_number{ TypeDefaults::s_invalid_sequence_number };

  bool operator<(const TriggerId& other) const noexcept
  {
    return std::tuple(trigger_number, sequence_number, run_number) <
           std::tuple(other.trigger_number, other.sequence_number, other.run_number);
  }

  bool operator==(const TriggerId& other) const noexcept
  {
    return std::tie(trigger_number, sequence_number, run_number) ==
           std::tie(other.trigger_number, other.sequence_number, other.run_number);
  }

  friend std::ostream& operator<<(std::ostream& out, const TriggerId& id) noexcept
  {
    out << id.trigger_number << '-' << id.sequence_number << '/' << id.run_number;
    return out;
  }

  friend TraceStreamer& operator<<(TraceStreamer& out, const TriggerId& id) noexcept
  {
    return out << id.trigger_number << '.' << id.sequence_number << "/" << id.run_number;
  }

  friend std::istream& operator>>(std::istream& in, TriggerId& id)
  {
    char t1, t2;
    in >> id.trigger_number >> t1 >> id.sequence_number >> t2 >> id.run_number;
    return in;
  }

  DUNE_DAQ_SERIALIZE(TriggerId, trigger_number, sequence_number, run_number);
};

} // namespace dfmessages

DUNE_DAQ_SERIALIZABLE(dfmessages::TriggerId, "TriggerId");
} // namespace dunedaq

#endif // DFMESSAGES_INCLUDE_DFMESSAGES_TRIGGERID_HPP_
