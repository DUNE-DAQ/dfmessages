/**
 * @file DataflowStatus_test.cxx DataflowStatus class Unit Tests
 *
 * This is part of the DUNE DAQ Application Framework, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#include "dfmessages/DataflowStatus.hpp"

/**
 * @brief Name of this test module
 */
#define BOOST_TEST_MODULE DataflowStatus_test // NOLINT

#include "TRACE/trace.h"
#include "boost/test/unit_test.hpp"

#include <string>
#include <vector>

using namespace dunedaq::dfmessages;

BOOST_AUTO_TEST_SUITE(DataflowStatus_test)

/**
 * @brief Check that DataflowStatuses have appropriate Copy/Move semantics
 */
BOOST_AUTO_TEST_CASE(CopyAndMoveSemantics)
{
  BOOST_REQUIRE(std::is_copy_constructible_v<DataflowStatus>);
  BOOST_REQUIRE(std::is_copy_assignable_v<DataflowStatus>);
  BOOST_REQUIRE(std::is_move_constructible_v<DataflowStatus>);
  BOOST_REQUIRE(std::is_move_assignable_v<DataflowStatus>);
}

BOOST_AUTO_TEST_CASE(DefaultConstruction)
{
  DataflowStatus ds;
  BOOST_REQUIRE_EQUAL(ds.run_number, TypeDefaults::s_invalid_run_number);
  BOOST_REQUIRE_EQUAL(ds.decision_destination, "");
  BOOST_REQUIRE_EQUAL(ds.is_busy, false);
  BOOST_REQUIRE_EQUAL(ds.busy_threshold, 0);
  BOOST_REQUIRE(ds.triggers_building.empty());
  BOOST_REQUIRE(ds.triggers_writing.empty());
  BOOST_REQUIRE_EQUAL(ds.trigger_records_processed, 0);
  BOOST_REQUIRE_EQUAL(ds.data_size_written, 0);
}

BOOST_AUTO_TEST_CASE(SerDes_MsgPack)
{
  DataflowStatus ds;
  ds.run_number = 1;
  ds.decision_destination = "decision_conn";
  ds.is_busy = true;
  ds.busy_threshold = 5;
  ds.triggers_building = { 10, 11, 12 };
  ds.triggers_writing = { 20, 21 };
  ds.trigger_records_processed = 100;
  ds.data_size_written = 1234567;

  auto bytes = dunedaq::serialization::serialize(ds, dunedaq::serialization::kMsgPack);
  TLOG(TLVL_INFO) << "MsgPack message size: " << bytes.size() << " bytes";
  DataflowStatus ds_deserialized = dunedaq::serialization::deserialize<DataflowStatus>(bytes);

  BOOST_REQUIRE_EQUAL(ds.run_number, ds_deserialized.run_number);
  BOOST_REQUIRE_EQUAL(ds.decision_destination, ds_deserialized.decision_destination);
  BOOST_REQUIRE_EQUAL(ds.is_busy, ds_deserialized.is_busy);
  BOOST_REQUIRE_EQUAL(ds.triggers_building.size(), ds_deserialized.triggers_building.size());
  BOOST_REQUIRE_EQUAL(*ds.triggers_building.begin(), *ds_deserialized.triggers_building.begin());
  BOOST_REQUIRE_EQUAL(ds.triggers_writing.size(), ds_deserialized.triggers_writing.size());
  BOOST_REQUIRE_EQUAL(*ds.triggers_writing.begin(), *ds_deserialized.triggers_writing.begin());
  BOOST_REQUIRE_EQUAL(ds.trigger_records_processed, ds_deserialized.trigger_records_processed);
  BOOST_REQUIRE_EQUAL(ds.data_size_written, ds_deserialized.data_size_written);
}

BOOST_AUTO_TEST_SUITE_END()
