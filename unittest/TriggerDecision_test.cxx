/**
 * @file TriggerDecision_test.cxx TriggerDecision class Unit Tests
 *
 * This is part of the DUNE DAQ Application Framework, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#include "dfmessages/TriggerDecision.hpp"

/**
 * @brief Name of this test module
 */
#define BOOST_TEST_MODULE TriggerDecision_test // NOLINT

#include "TRACE/trace.h"
#include "boost/test/unit_test.hpp"

using namespace dunedaq::dfmessages;

BOOST_AUTO_TEST_SUITE(TriggerDecision_test)

/**
 * @brief Check that TriggerDecisions have appropriate Copy/Move semantics
 */
BOOST_AUTO_TEST_CASE(CopyAndMoveSemantics)
{
  BOOST_REQUIRE(std::is_copy_constructible_v<TriggerDecision>);
  BOOST_REQUIRE(std::is_copy_assignable_v<TriggerDecision>);
  BOOST_REQUIRE(std::is_move_constructible_v<TriggerDecision>);
  BOOST_REQUIRE(std::is_move_assignable_v<TriggerDecision>);
}

BOOST_AUTO_TEST_CASE(SerDes_JSON)
{
  TriggerDecision td;
  td.trigger_number = 1;
  td.run_number = 2;
  td.trigger_timestamp = 3;
  td.trigger_type = 4;
  td.readout_type = ReadoutType::kLocalized;

  GeoID gid;
  gid.apa_number = 1;
  gid.link_number = 2;
  ComponentRequest cr;
  cr.component = gid;
  cr.window_begin = 5;
  cr.window_end = 6;

  GeoID another_gid;
  another_gid.apa_number = 2;
  another_gid.link_number = 1;
  ComponentRequest another_cr;
  another_cr.component = another_gid;
  another_cr.window_begin = 7;
  another_cr.window_end = 8;

  td.components.push_back(cr);
  td.components.push_back(another_cr);

  auto bytes = dunedaq::serialization::serialize(td, dunedaq::serialization::kJSON);

  std::ostringstream ostr;
  for (auto& b : bytes) {
    ostr << static_cast<char>(b);
  }
  TLOG(TLVL_INFO) << "Serialized string: " << ostr.str();

  TriggerDecision td_deserialized = dunedaq::serialization::deserialize<TriggerDecision>(bytes);

  BOOST_REQUIRE_EQUAL(td.trigger_number, td_deserialized.trigger_number);
  BOOST_REQUIRE_EQUAL(td.run_number, td_deserialized.run_number);
  BOOST_REQUIRE_EQUAL(td.trigger_timestamp, td_deserialized.trigger_timestamp);
  BOOST_REQUIRE_EQUAL(td.trigger_type, td_deserialized.trigger_type);
  BOOST_REQUIRE_EQUAL(static_cast<uint16_t>(td.readout_type), static_cast<uint16_t>(td_deserialized.readout_type));

  BOOST_REQUIRE_EQUAL(td.components.size(), td_deserialized.components.size());

  BOOST_REQUIRE_EQUAL(td.components[0].component.apa_number, td_deserialized.components[0].component.apa_number);
  BOOST_REQUIRE_EQUAL(td.components[0].component.link_number, td_deserialized.components[0].component.link_number);
  BOOST_REQUIRE_EQUAL(td.components[0].window_begin, td_deserialized.components[0].window_begin);
  BOOST_REQUIRE_EQUAL(td.components[0].window_end, td_deserialized.components[0].window_end);

  BOOST_REQUIRE_EQUAL(td.components[1].component.apa_number,
                      td_deserialized.components[1].component.apa_number);
  BOOST_REQUIRE_EQUAL(td.components[1].component.link_number,
                      td_deserialized.components[1].component.link_number);
  BOOST_REQUIRE_EQUAL(td.components[1].window_begin, td_deserialized.components[1].window_begin);
  BOOST_REQUIRE_EQUAL(td.components[1].window_end, td_deserialized.components[1].window_end);
}

BOOST_AUTO_TEST_CASE(SerDes_MsgPack)
{
  TriggerDecision td;
  td.trigger_number = 1;
  td.run_number = 2;
  td.trigger_timestamp = 3;
  td.trigger_type = 4;
  td.readout_type = ReadoutType::kLocalized;

  GeoID gid;
  gid.apa_number = 1;
  gid.link_number = 2;
  ComponentRequest cr;
  cr.component = gid;
  cr.window_begin = 5;
  cr.window_end = 6;

  GeoID another_gid;
  another_gid.apa_number = 2;
  another_gid.link_number = 1;
  ComponentRequest another_cr;
  another_cr.component = another_gid;
  another_cr.window_begin = 7;
  another_cr.window_end = 8;

  td.components.push_back(cr);
  td.components.push_back(another_cr);

  auto bytes = dunedaq::serialization::serialize(td, dunedaq::serialization::kMsgPack);
  TLOG(TLVL_INFO) << "MsgPack message size: " << bytes.size() << " bytes";
  TriggerDecision td_deserialized = dunedaq::serialization::deserialize<TriggerDecision>(bytes);

  BOOST_REQUIRE_EQUAL(td.trigger_number, td_deserialized.trigger_number);
  BOOST_REQUIRE_EQUAL(td.run_number, td_deserialized.run_number);
  BOOST_REQUIRE_EQUAL(td.trigger_timestamp, td_deserialized.trigger_timestamp);
  BOOST_REQUIRE_EQUAL(td.trigger_type, td_deserialized.trigger_type);
  BOOST_REQUIRE_EQUAL(static_cast<uint16_t>(td.readout_type), static_cast<uint16_t>(td_deserialized.readout_type));

  BOOST_REQUIRE_EQUAL(td.components.size(), td_deserialized.components.size());

  BOOST_REQUIRE_EQUAL(td.components[0].component.apa_number, td_deserialized.components[0].component.apa_number);
  BOOST_REQUIRE_EQUAL(td.components[0].component.link_number, td_deserialized.components[0].component.link_number);
  BOOST_REQUIRE_EQUAL(td.components[0].window_begin, td_deserialized.components[0].window_begin);
  BOOST_REQUIRE_EQUAL(td.components[0].window_end, td_deserialized.components[0].window_end);

  BOOST_REQUIRE_EQUAL(td.components[1].component.apa_number,
                      td_deserialized.components[1].component.apa_number);
  BOOST_REQUIRE_EQUAL(td.components[1].component.link_number,
                      td_deserialized.components[1].component.link_number);
  BOOST_REQUIRE_EQUAL(td.components[1].window_begin, td_deserialized.components[1].window_begin);
  BOOST_REQUIRE_EQUAL(td.components[1].window_end, td_deserialized.components[1].window_end);
}

BOOST_AUTO_TEST_SUITE_END()
