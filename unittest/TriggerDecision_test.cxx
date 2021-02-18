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

  GeoID gid;
  gid.apa_number = 1;
  gid.link_number = 2;
  ComponentRequest cr;
  cr.component = gid;
  cr.window_start = 5;
  cr.window_end = 6;

  GeoID another_gid;
  another_gid.apa_number = 2;
  another_gid.link_number = 1;
  ComponentRequest another_cr;
  another_cr.component = another_gid;
  another_cr.window_start = 7;
  another_cr.window_end = 8;

  td.components[gid] = cr;
  td.components[another_gid] = another_cr;

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

  BOOST_REQUIRE_EQUAL(td.components.size(), td_deserialized.components.size());

  BOOST_REQUIRE_EQUAL(td.components[gid].component.apa_number,
                      td_deserialized.components[gid].component.apa_number);
  BOOST_REQUIRE_EQUAL(td.components[gid].component.link_number,
                      td_deserialized.components[gid].component.link_number);
  BOOST_REQUIRE_EQUAL(td.components[gid].window_start, td_deserialized.components[gid].window_start);
  BOOST_REQUIRE_EQUAL(td.components[gid].window_end, td_deserialized.components[gid].window_end);

  BOOST_REQUIRE_EQUAL(td.components[another_gid].component.apa_number,
                      td_deserialized.components[another_gid].component.apa_number);
  BOOST_REQUIRE_EQUAL(td.components[another_gid].component.link_number,
                      td_deserialized.components[another_gid].component.link_number);
  BOOST_REQUIRE_EQUAL(td.components[another_gid].window_start,
                      td_deserialized.components[another_gid].window_start);
  BOOST_REQUIRE_EQUAL(td.components[another_gid].window_end,
                      td_deserialized.components[another_gid].window_end);
}

BOOST_AUTO_TEST_CASE(SerDes_MsgPack)
{
  TriggerDecision td;
  td.trigger_number = 1;
  td.run_number = 2;
  td.trigger_timestamp = 3;
  td.trigger_type = 4;

  GeoID gid;
  gid.apa_number = 1;
  gid.link_number = 2;
  ComponentRequest cr;
  cr.component = gid;
  cr.window_start = 5;
  cr.window_end = 6;

  GeoID another_gid;
  another_gid.apa_number = 2;
  another_gid.link_number = 1;
  ComponentRequest another_cr;
  another_cr.component = another_gid;
  another_cr.window_start = 7;
  another_cr.window_end = 8;

  td.components[gid] = cr;
  td.components[another_gid] = another_cr;


  auto bytes = dunedaq::serialization::serialize(td, dunedaq::serialization::kMsgPack);
  TLOG(TLVL_INFO) << "MsgPack message size: " << bytes.size() << " bytes";
  TriggerDecision td_deserialized = dunedaq::serialization::deserialize<TriggerDecision>(bytes);

  BOOST_REQUIRE_EQUAL(td.trigger_number, td_deserialized.trigger_number);
  BOOST_REQUIRE_EQUAL(td.run_number, td_deserialized.run_number);
  BOOST_REQUIRE_EQUAL(td.trigger_timestamp, td_deserialized.trigger_timestamp);
  BOOST_REQUIRE_EQUAL(td.trigger_type, td_deserialized.trigger_type);

  BOOST_REQUIRE_EQUAL(td.components.size(), td_deserialized.components.size());

  BOOST_REQUIRE_EQUAL(td.components[gid].component.apa_number,
                      td_deserialized.components[gid].component.apa_number);
  BOOST_REQUIRE_EQUAL(td.components[gid].component.link_number,
                      td_deserialized.components[gid].component.link_number);
  BOOST_REQUIRE_EQUAL(td.components[gid].window_start, td_deserialized.components[gid].window_start);
  BOOST_REQUIRE_EQUAL(td.components[gid].window_end, td_deserialized.components[gid].window_end);

  BOOST_REQUIRE_EQUAL(td.components[another_gid].component.apa_number,
                      td_deserialized.components[another_gid].component.apa_number);
  BOOST_REQUIRE_EQUAL(td.components[another_gid].component.link_number,
                      td_deserialized.components[another_gid].component.link_number);
  BOOST_REQUIRE_EQUAL(td.components[another_gid].window_start,
                      td_deserialized.components[another_gid].window_start);
  BOOST_REQUIRE_EQUAL(td.components[another_gid].window_end,
                      td_deserialized.components[another_gid].window_end);
}

BOOST_AUTO_TEST_SUITE_END()
