/**
 * @file DataflowStatusRequest_test.cxx DataflowStatusRequest class Unit Tests
 *
 * This is part of the DUNE DAQ Application Framework, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#include "dfmessages/DataflowStatusRequest.hpp"

/**
 * @brief Name of this test module
 */
#define BOOST_TEST_MODULE DataflowStatusRequest_test // NOLINT

#include "TRACE/trace.h"
#include "boost/test/unit_test.hpp"

#include <string>
#include <vector>

using namespace dunedaq::dfmessages;

BOOST_AUTO_TEST_SUITE(DataflowStatusRequest_test)

/**
 * @brief Check that DataflowStatusRequests have appropriate Copy/Move semantics
 */
BOOST_AUTO_TEST_CASE(CopyAndMoveSemantics)
{
  BOOST_REQUIRE(std::is_copy_constructible_v<DataflowStatusRequest>);
  BOOST_REQUIRE(std::is_copy_assignable_v<DataflowStatusRequest>);
  BOOST_REQUIRE(std::is_move_constructible_v<DataflowStatusRequest>);
  BOOST_REQUIRE(std::is_move_assignable_v<DataflowStatusRequest>);
}

BOOST_AUTO_TEST_CASE(DefaultConstruction)
{
  DataflowStatusRequest dsr;
  BOOST_REQUIRE_EQUAL(dsr.trigger_id.run_number, TypeDefaults::s_invalid_run_number);
  BOOST_REQUIRE_EQUAL(dsr.trigger_id.trigger_number, TypeDefaults::s_invalid_trigger_number);
  BOOST_REQUIRE_EQUAL(dsr.reply_destination, "");
  BOOST_REQUIRE_EQUAL(dsr.iteration_number, 0);
}

BOOST_AUTO_TEST_CASE(SerDes_MsgPack)
{
  DataflowStatusRequest dsr;
  dsr.trigger_id.run_number = 1;
  dsr.trigger_id.trigger_number = 42;
  dsr.iteration_number = 3;
  dsr.reply_destination = "test_destination";

  auto bytes = dunedaq::serialization::serialize(dsr, dunedaq::serialization::kMsgPack);
  TLOG(TLVL_INFO) << "MsgPack message size: " << bytes.size() << " bytes";
  DataflowStatusRequest dsr_deserialized = dunedaq::serialization::deserialize<DataflowStatusRequest>(bytes);

  BOOST_REQUIRE_EQUAL(dsr.trigger_id, dsr_deserialized.trigger_id);
  BOOST_REQUIRE_EQUAL(dsr.iteration_number, dsr_deserialized.iteration_number);
  BOOST_REQUIRE_EQUAL(dsr.reply_destination, dsr_deserialized.reply_destination);
}

BOOST_AUTO_TEST_SUITE_END()
