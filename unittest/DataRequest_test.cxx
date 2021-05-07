/**
 * @file DataRequest_test.cxx DataRequest class Unit Tests
 *
 * This is part of the DUNE DAQ Application Framework, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#include "dfmessages/DataRequest.hpp"

/**
 * @brief Name of this test module
 */
#define BOOST_TEST_MODULE DataRequest_test // NOLINT

#include "TRACE/trace.h"
#include "boost/test/unit_test.hpp"

using namespace dunedaq::dfmessages;

BOOST_AUTO_TEST_SUITE(DataRequest_test)

/**
 * @brief Check that DataRequests have appropriate Copy/Move semantics
 */
BOOST_AUTO_TEST_CASE(CopyAndMoveSemantics)
{
  BOOST_REQUIRE(std::is_copy_constructible_v<DataRequest>);
  BOOST_REQUIRE(std::is_copy_assignable_v<DataRequest>);
  BOOST_REQUIRE(std::is_move_constructible_v<DataRequest>);
  BOOST_REQUIRE(std::is_move_assignable_v<DataRequest>);
}

BOOST_AUTO_TEST_CASE(SerDes_JSON)
{
  DataRequest dr;
  dr.request_number = 1;
  dr.trigger_number = 2;
  dr.trigger_timestamp = 3;
  dr.window_begin = 4;
  dr.window_end = 5;
  dr.readout_type = ReadoutType::kLocalized;
  dr.run_number = 6;

  auto bytes = dunedaq::serialization::serialize(dr, dunedaq::serialization::kJSON);

  std::ostringstream ostr;
  for (auto& b : bytes) {
    ostr << static_cast<char>(b);
  }
  TLOG(TLVL_INFO) << "Serialized string: " << ostr.str();

  DataRequest dr_deserialized = dunedaq::serialization::deserialize<DataRequest>(bytes);

  BOOST_REQUIRE_EQUAL(dr.request_number, dr_deserialized.request_number);
  BOOST_REQUIRE_EQUAL(dr.trigger_number, dr_deserialized.trigger_number);
  BOOST_REQUIRE_EQUAL(dr.trigger_timestamp, dr_deserialized.trigger_timestamp);
  BOOST_REQUIRE_EQUAL(dr.window_begin, dr_deserialized.window_begin);
  BOOST_REQUIRE_EQUAL(dr.window_end, dr_deserialized.window_end);
  BOOST_REQUIRE_EQUAL(dr.run_number, dr_deserialized.run_number);
  BOOST_REQUIRE_EQUAL(static_cast<uint16_t>(dr.readout_type), static_cast<uint16_t>(dr_deserialized.readout_type));
}

BOOST_AUTO_TEST_CASE(SerDes_MsgPack)
{

  DataRequest dr;
  dr.request_number = 1;
  dr.trigger_number = 2;
  dr.trigger_timestamp = 3;
  dr.window_begin = 4;
  dr.window_end = 5;
  dr.readout_type = ReadoutType::kLocalized;
  dr.run_number = 6;

  auto bytes = dunedaq::serialization::serialize(dr, dunedaq::serialization::kMsgPack);
  TLOG(TLVL_INFO) << "MsgPack message size: " << bytes.size() << " bytes";
  DataRequest dr_deserialized = dunedaq::serialization::deserialize<DataRequest>(bytes);

  BOOST_REQUIRE_EQUAL(dr.request_number, dr_deserialized.request_number);
  BOOST_REQUIRE_EQUAL(dr.trigger_number, dr_deserialized.trigger_number);
  BOOST_REQUIRE_EQUAL(dr.trigger_timestamp, dr_deserialized.trigger_timestamp);
  BOOST_REQUIRE_EQUAL(dr.window_begin, dr_deserialized.window_begin);
  BOOST_REQUIRE_EQUAL(dr.window_end, dr_deserialized.window_end);
  BOOST_REQUIRE_EQUAL(dr.run_number, dr_deserialized.run_number);
  BOOST_REQUIRE_EQUAL(static_cast<uint16_t>(dr.readout_type), static_cast<uint16_t>(dr_deserialized.readout_type));
}
BOOST_AUTO_TEST_SUITE_END()
