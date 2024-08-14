/**
 * @file DataflowHeartbeat_test.cxx DataflowHeartbeat class Unit Tests
 *
 * This is part of the DUNE DAQ Application Framework, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#include "dfmessages/DataflowHeartbeat.hpp"

/**
 * @brief Name of this test module
 */
#define BOOST_TEST_MODULE DataflowHeartbeat_test // NOLINT

#include "TRACE/trace.h"
#include "boost/test/unit_test.hpp"

#include <string>
#include <vector>

using namespace dunedaq::dfmessages;

BOOST_AUTO_TEST_SUITE(DataflowHeartbeat_test)

/**
 * @brief Check that DataflowHeartbeats have appropriate Copy/Move semantics
 */
BOOST_AUTO_TEST_CASE(CopyAndMoveSemantics)
{
  BOOST_REQUIRE(std::is_copy_constructible_v<DataflowHeartbeat>);
  BOOST_REQUIRE(std::is_copy_assignable_v<DataflowHeartbeat>);
  BOOST_REQUIRE(std::is_move_constructible_v<DataflowHeartbeat>);
  BOOST_REQUIRE(std::is_move_assignable_v<DataflowHeartbeat>);
}

BOOST_AUTO_TEST_CASE(DefaultConstruction)
{
  DataflowHeartbeat tdt;
  BOOST_REQUIRE_EQUAL(tdt.run_number, TypeDefaults::s_invalid_run_number);
  BOOST_REQUIRE_EQUAL(tdt.recent_completed_triggers.size(), 0);
  BOOST_REQUIRE_EQUAL(tdt.outstanding_decisions.size(), 0);
}

BOOST_AUTO_TEST_CASE(SerDes_JSON)
{
  DataflowHeartbeat tdt;
  tdt.run_number = 1;
  tdt.recent_completed_triggers = {1,2,3};
  tdt.outstanding_decisions = { 4, 5 };

  auto bytes = dunedaq::serialization::serialize(tdt, dunedaq::serialization::kJSON);

  std::ostringstream ostr;
  for (auto& b : bytes) {
    ostr << static_cast<char>(b);
  }
  TLOG(TLVL_INFO) << "Serialized string: " << ostr.str();

  DataflowHeartbeat tdt_deserialized = dunedaq::serialization::deserialize<DataflowHeartbeat>(bytes);

  BOOST_REQUIRE_EQUAL(tdt.run_number, tdt_deserialized.run_number);
  BOOST_REQUIRE_EQUAL(tdt.recent_completed_triggers.size(), tdt_deserialized.recent_completed_triggers.size());
  BOOST_REQUIRE_EQUAL(tdt.recent_completed_triggers[0], tdt_deserialized.recent_completed_triggers[0]);
  BOOST_REQUIRE_EQUAL(tdt.outstanding_decisions.size(), tdt_deserialized.outstanding_decisions.size());
  BOOST_REQUIRE_EQUAL(tdt.outstanding_decisions[0], tdt_deserialized.outstanding_decisions[0]);
}

BOOST_AUTO_TEST_CASE(SerDes_MsgPack)
{
  DataflowHeartbeat tdt;
  tdt.run_number = 1;
  tdt.recent_completed_triggers = { 1, 2, 3 };
  tdt.outstanding_decisions = { 4, 5 };

  auto bytes = dunedaq::serialization::serialize(tdt, dunedaq::serialization::kMsgPack);
  TLOG(TLVL_INFO) << "MsgPack message size: " << bytes.size() << " bytes";
  DataflowHeartbeat tdt_deserialized = dunedaq::serialization::deserialize<DataflowHeartbeat>(bytes);

  BOOST_REQUIRE_EQUAL(tdt.run_number, tdt_deserialized.run_number);
  BOOST_REQUIRE_EQUAL(tdt.recent_completed_triggers.size(), tdt_deserialized.recent_completed_triggers.size());
  BOOST_REQUIRE_EQUAL(tdt.recent_completed_triggers[0], tdt_deserialized.recent_completed_triggers[0]);
  BOOST_REQUIRE_EQUAL(tdt.outstanding_decisions.size(), tdt_deserialized.outstanding_decisions.size());
  BOOST_REQUIRE_EQUAL(tdt.outstanding_decisions[0], tdt_deserialized.outstanding_decisions[0]);
}

BOOST_AUTO_TEST_SUITE_END()