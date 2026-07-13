/**
 * @file TriggerId_test.cxx TriggerId class Unit Tests
 *
 * This is part of the DUNE DAQ Application Framework, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#include "dfmessages/TriggerId.hpp"

/**
 * @brief Name of this test module
 */
#define BOOST_TEST_MODULE TriggerId_test // NOLINT

#include "TRACE/trace.h"
#include "boost/test/unit_test.hpp"

#include <string>
#include <vector>

using namespace dunedaq::dfmessages;

BOOST_AUTO_TEST_SUITE(TriggerId_test)

/**
 * @brief Check that TriggerIds have appropriate Copy/Move semantics
 */
BOOST_AUTO_TEST_CASE(CopyAndMoveSemantics)
{
  BOOST_REQUIRE(std::is_copy_constructible_v<TriggerId>);
  BOOST_REQUIRE(std::is_copy_assignable_v<TriggerId>);
  BOOST_REQUIRE(std::is_move_constructible_v<TriggerId>);
  BOOST_REQUIRE(std::is_move_assignable_v<TriggerId>);
}

BOOST_AUTO_TEST_CASE(DefaultConstruction)
{
  TriggerId tc;
  BOOST_REQUIRE_EQUAL(tc.run_number, TypeDefaults::s_invalid_run_number);
  BOOST_REQUIRE_EQUAL(tc.trigger_number, TypeDefaults::s_invalid_trigger_number);
  BOOST_REQUIRE_EQUAL(tc.sequence_number, TypeDefaults::s_invalid_sequence_number);
}

BOOST_AUTO_TEST_CASE(SerDes_MsgPack)
{
  TriggerId tid;
  tid.run_number = 1;
  tid.trigger_number = 2;
  tid.sequence_number = 3;

  auto bytes = dunedaq::serialization::serialize(tid, dunedaq::serialization::kMsgPack);
  TLOG(TLVL_INFO) << "MsgPack message size: " << bytes.size() << " bytes";
  TriggerId tid_deserialized = dunedaq::serialization::deserialize<TriggerId>(bytes);

  BOOST_REQUIRE_EQUAL(tid.run_number, tid_deserialized.run_number);
  BOOST_REQUIRE_EQUAL(tid.trigger_number, tid_deserialized.trigger_number);
  BOOST_REQUIRE_EQUAL(tid.sequence_number, tid_deserialized.sequence_number);
}

BOOST_AUTO_TEST_SUITE_END()
