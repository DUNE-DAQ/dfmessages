/**
 * @file DFODecision_test.cxx DFODecision class Unit Tests
 *
 * This is part of the DUNE DAQ Application Framework, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#include "dfmessages/DFODecision.hpp"

/**
 * @brief Name of this test module
 */
#define BOOST_TEST_MODULE DFODecision_test // NOLINT

#include "TRACE/trace.h"
#include "boost/test/unit_test.hpp"

using namespace dunedaq::dfmessages;

BOOST_AUTO_TEST_SUITE(DFODecision_test)

/**
 * @brief Check that DFODecisions have appropriate Copy/Move semantics
 */
BOOST_AUTO_TEST_CASE(CopyAndMoveSemantics)
{
  BOOST_REQUIRE(std::is_copy_constructible_v<DFODecision>);
  BOOST_REQUIRE(std::is_copy_assignable_v<DFODecision>);
  BOOST_REQUIRE(std::is_move_constructible_v<DFODecision>);
  BOOST_REQUIRE(std::is_move_assignable_v<DFODecision>);
}

BOOST_AUTO_TEST_CASE(SerDes_JSON)
{
  DFODecision dd;
  dd.dfo_id = "TEST";
  dd.acknowledged_completions = { 1, 2, 3, 4, 5 };

  TriggerDecision td;
  td.trigger_number = 1;
  td.run_number = 2;
  td.trigger_timestamp = 3;
  td.trigger_type = 4;
  td.readout_type = ReadoutType::kLocalized;

  SourceID sid;
  sid.subsystem = SourceID::Subsystem::kDetectorReadout;
  sid.id= 1;
  ComponentRequest cr;
  cr.component = sid;
  cr.window_begin = 5;
  cr.window_end = 6;

  SourceID another_sid;
  another_sid.subsystem = SourceID::Subsystem::kDetectorReadout;
  another_sid.id= 2;
  ComponentRequest another_cr;
  another_cr.component = another_sid;
  another_cr.window_begin = 7;
  another_cr.window_end = 8;

  td.components.push_back(cr);
  td.components.push_back(another_cr);
  dd.trigger_decision = td;

  auto bytes = dunedaq::serialization::serialize(dd, dunedaq::serialization::kJSON);

  std::ostringstream ostr;
  for (auto& b : bytes) {
    ostr << static_cast<char>(b);
  }
  TLOG(TLVL_INFO) << "Serialized string: " << ostr.str();

  DFODecision dd_deserialized = dunedaq::serialization::deserialize<DFODecision>(bytes);
  TriggerDecision td_deserialized = dd_deserialized.trigger_decision;

  BOOST_REQUIRE_EQUAL(dd.dfo_id, dd_deserialized.dfo_id);
  BOOST_REQUIRE_EQUAL(dd.acknowledged_completions.size(), dd_deserialized.acknowledged_completions.size());
  BOOST_REQUIRE_EQUAL(dd.acknowledged_completions[0], dd_deserialized.acknowledged_completions[0]);

  BOOST_REQUIRE_EQUAL(td.trigger_number, td_deserialized.trigger_number);
  BOOST_REQUIRE_EQUAL(td.run_number, td_deserialized.run_number);
  BOOST_REQUIRE_EQUAL(td.trigger_timestamp, td_deserialized.trigger_timestamp);
  BOOST_REQUIRE_EQUAL(td.trigger_type, td_deserialized.trigger_type);
  BOOST_REQUIRE_EQUAL(static_cast<uint16_t>(td.readout_type),               // NOLINT(build/unsigned)
                      static_cast<uint16_t>(td_deserialized.readout_type)); // NOLINT(build/unsigned)

  BOOST_REQUIRE_EQUAL(td.components.size(), td_deserialized.components.size());

  BOOST_REQUIRE_EQUAL(td.components[0].component.subsystem, td_deserialized.components[0].component.subsystem);
  BOOST_REQUIRE_EQUAL(td.components[0].component.id, td_deserialized.components[0].component.id);
  BOOST_REQUIRE_EQUAL(td.components[0].window_begin, td_deserialized.components[0].window_begin);
  BOOST_REQUIRE_EQUAL(td.components[0].window_end, td_deserialized.components[0].window_end);

  BOOST_REQUIRE_EQUAL(td.components[1].component.subsystem, td_deserialized.components[1].component.subsystem);
  BOOST_REQUIRE_EQUAL(td.components[1].component.id, td_deserialized.components[1].component.id);
  BOOST_REQUIRE_EQUAL(td.components[1].window_begin, td_deserialized.components[1].window_begin);
  BOOST_REQUIRE_EQUAL(td.components[1].window_end, td_deserialized.components[1].window_end);
}

BOOST_AUTO_TEST_CASE(SerDes_MsgPack)
{
  DFODecision dd;
  dd.dfo_id = "TEST";
  dd.acknowledged_completions = { 1, 2, 3, 4, 5 };

  TriggerDecision td;
  td.trigger_number = 1;
  td.run_number = 2;
  td.trigger_timestamp = 3;
  td.trigger_type = 4;
  td.readout_type = ReadoutType::kLocalized;

  SourceID sid;
  sid.subsystem = SourceID::Subsystem::kDetectorReadout;
  sid.id= 1;
  ComponentRequest cr;
  cr.component = sid;
  cr.window_begin = 5;
  cr.window_end = 6;

  SourceID another_sid;
  another_sid.subsystem = SourceID::Subsystem::kDetectorReadout;
  another_sid.id= 2;
  ComponentRequest another_cr;
  another_cr.component = another_sid;
  another_cr.window_begin = 7;
  another_cr.window_end = 8;

  td.components.push_back(cr);
  td.components.push_back(another_cr);
  dd.trigger_decision = td;

  auto bytes = dunedaq::serialization::serialize(dd, dunedaq::serialization::kMsgPack);
  TLOG(TLVL_INFO) << "MsgPack message size: " << bytes.size() << " bytes";
  DFODecision dd_deserialized = dunedaq::serialization::deserialize<DFODecision>(bytes);
  TriggerDecision td_deserialized = dd_deserialized.trigger_decision;

  BOOST_REQUIRE_EQUAL(dd.dfo_id, dd_deserialized.dfo_id);
  BOOST_REQUIRE_EQUAL(dd.acknowledged_completions.size(), dd_deserialized.acknowledged_completions.size());
  BOOST_REQUIRE_EQUAL(dd.acknowledged_completions[0], dd_deserialized.acknowledged_completions[0]);

  BOOST_REQUIRE_EQUAL(td.trigger_number, td_deserialized.trigger_number);
  BOOST_REQUIRE_EQUAL(td.run_number, td_deserialized.run_number);
  BOOST_REQUIRE_EQUAL(td.trigger_timestamp, td_deserialized.trigger_timestamp);
  BOOST_REQUIRE_EQUAL(td.trigger_type, td_deserialized.trigger_type);
  BOOST_REQUIRE_EQUAL(static_cast<uint16_t>(td.readout_type),               // NOLINT(build/unsigned)
                      static_cast<uint16_t>(td_deserialized.readout_type)); // NOLINT(build/unsigned)

  BOOST_REQUIRE_EQUAL(td.components.size(), td_deserialized.components.size());

  BOOST_REQUIRE_EQUAL(td.components[0].component.subsystem, td_deserialized.components[0].component.subsystem);
  BOOST_REQUIRE_EQUAL(td.components[0].component.id, td_deserialized.components[0].component.id);
  BOOST_REQUIRE_EQUAL(td.components[0].window_begin, td_deserialized.components[0].window_begin);
  BOOST_REQUIRE_EQUAL(td.components[0].window_end, td_deserialized.components[0].window_end);

  BOOST_REQUIRE_EQUAL(td.components[1].component.subsystem, td_deserialized.components[1].component.subsystem);
  BOOST_REQUIRE_EQUAL(td.components[1].component.id, td_deserialized.components[1].component.id);
  BOOST_REQUIRE_EQUAL(td.components[1].window_begin, td_deserialized.components[1].window_begin);
  BOOST_REQUIRE_EQUAL(td.components[1].window_end, td_deserialized.components[1].window_end);
}

BOOST_AUTO_TEST_SUITE_END()
