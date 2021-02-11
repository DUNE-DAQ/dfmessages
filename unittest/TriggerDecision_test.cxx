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
  td.m_trigger_number = 1;
  td.m_run_number = 2;
  td.m_trigger_timestamp = 3;
  td.m_trigger_type = 4;

  GeoID gid;
  gid.m_apa_number = 1;
  gid.m_link_number = 2;
  ComponentRequest cr;
  cr.m_component = gid;
  cr.m_window_offset = 5;
  cr.m_window_width = 6;

  GeoID another_gid;
  another_gid.m_apa_number = 2;
  another_gid.m_link_number = 1;
  ComponentRequest another_cr;
  another_cr.m_component = another_gid;
  another_cr.m_window_offset = 7;
  another_cr.m_window_width = 8;

  td.m_components[gid] = cr;
  td.m_components[another_gid] = another_cr;

  auto bytes = dunedaq::serialization::serialize(td, dunedaq::serialization::kJSON);

  std::ostringstream ostr;
  for (auto& b : bytes) {
    ostr << static_cast<char>(b);
  }
  TLOG(TLVL_INFO) << "Serialized string: " << ostr.str();

  TriggerDecision td_deserialized = dunedaq::serialization::deserialize<TriggerDecision>(bytes);

  BOOST_REQUIRE_EQUAL(td.m_trigger_number, td_deserialized.m_trigger_number);
  BOOST_REQUIRE_EQUAL(td.m_run_number, td_deserialized.m_run_number);
  BOOST_REQUIRE_EQUAL(td.m_trigger_timestamp, td_deserialized.m_trigger_timestamp);
  BOOST_REQUIRE_EQUAL(td.m_trigger_type, td_deserialized.m_trigger_type);

  BOOST_REQUIRE_EQUAL(td.m_components.size(), td_deserialized.m_components.size());

  BOOST_REQUIRE_EQUAL(td.m_components[gid].m_component.m_apa_number,
                      td_deserialized.m_components[gid].m_component.m_apa_number);
  BOOST_REQUIRE_EQUAL(td.m_components[gid].m_component.m_link_number,
                      td_deserialized.m_components[gid].m_component.m_link_number);
  BOOST_REQUIRE_EQUAL(td.m_components[gid].m_window_offset, td_deserialized.m_components[gid].m_window_offset);
  BOOST_REQUIRE_EQUAL(td.m_components[gid].m_window_width, td_deserialized.m_components[gid].m_window_width);

  BOOST_REQUIRE_EQUAL(td.m_components[another_gid].m_component.m_apa_number,
                      td_deserialized.m_components[another_gid].m_component.m_apa_number);
  BOOST_REQUIRE_EQUAL(td.m_components[another_gid].m_component.m_link_number,
                      td_deserialized.m_components[another_gid].m_component.m_link_number);
  BOOST_REQUIRE_EQUAL(td.m_components[another_gid].m_window_offset,
                      td_deserialized.m_components[another_gid].m_window_offset);
  BOOST_REQUIRE_EQUAL(td.m_components[another_gid].m_window_width,
                      td_deserialized.m_components[another_gid].m_window_width);
}

BOOST_AUTO_TEST_CASE(SerDes_MsgPack)
{
  TriggerDecision td;
  td.m_trigger_number = 1;
  td.m_run_number = 2;
  td.m_trigger_timestamp = 3;
  td.m_trigger_type = 4;

  GeoID gid;
  gid.m_apa_number = 1;
  gid.m_link_number = 2;
  ComponentRequest cr;
  cr.m_component = gid;
  cr.m_window_offset = 5;
  cr.m_window_width = 6;

  GeoID another_gid;
  another_gid.m_apa_number = 2;
  another_gid.m_link_number = 1;
  ComponentRequest another_cr;
  another_cr.m_component = another_gid;
  another_cr.m_window_offset = 7;
  another_cr.m_window_width = 8;

  td.m_components[gid] = cr;
  td.m_components[another_gid] = another_cr;


  auto bytes = dunedaq::serialization::serialize(td, dunedaq::serialization::kMsgPack);
  TLOG(TLVL_INFO) << "MsgPack message size: " << bytes.size() << " bytes";
  TriggerDecision td_deserialized = dunedaq::serialization::deserialize<TriggerDecision>(bytes);

  BOOST_REQUIRE_EQUAL(td.m_trigger_number, td_deserialized.m_trigger_number);
  BOOST_REQUIRE_EQUAL(td.m_run_number, td_deserialized.m_run_number);
  BOOST_REQUIRE_EQUAL(td.m_trigger_timestamp, td_deserialized.m_trigger_timestamp);
  BOOST_REQUIRE_EQUAL(td.m_trigger_type, td_deserialized.m_trigger_type);

  BOOST_REQUIRE_EQUAL(td.m_components.size(), td_deserialized.m_components.size());

  BOOST_REQUIRE_EQUAL(td.m_components[gid].m_component.m_apa_number,
                      td_deserialized.m_components[gid].m_component.m_apa_number);
  BOOST_REQUIRE_EQUAL(td.m_components[gid].m_component.m_link_number,
                      td_deserialized.m_components[gid].m_component.m_link_number);
  BOOST_REQUIRE_EQUAL(td.m_components[gid].m_window_offset, td_deserialized.m_components[gid].m_window_offset);
  BOOST_REQUIRE_EQUAL(td.m_components[gid].m_window_width, td_deserialized.m_components[gid].m_window_width);

  BOOST_REQUIRE_EQUAL(td.m_components[another_gid].m_component.m_apa_number,
                      td_deserialized.m_components[another_gid].m_component.m_apa_number);
  BOOST_REQUIRE_EQUAL(td.m_components[another_gid].m_component.m_link_number,
                      td_deserialized.m_components[another_gid].m_component.m_link_number);
  BOOST_REQUIRE_EQUAL(td.m_components[another_gid].m_window_offset,
                      td_deserialized.m_components[another_gid].m_window_offset);
  BOOST_REQUIRE_EQUAL(td.m_components[another_gid].m_window_width,
                      td_deserialized.m_components[another_gid].m_window_width);
}

BOOST_AUTO_TEST_SUITE_END()
