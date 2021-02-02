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
  dr.m_request_number = 1;
  dr.m_trigger_number = 2;
  dr.m_trigger_timestamp = 3;
  dr.m_window_offset = 4;
  dr.m_window_width = 5;
  dr.m_request_mode = DataRequest::mode_t::kLocalizedReadout;

  auto bytes = dunedaq::serialization::serialize(dr, dunedaq::serialization::kJSON);

  std::ostringstream ostr;
  for (auto& b : bytes) {
    ostr << static_cast<char>(b);
  }
  TLOG(TLVL_INFO) << "Serialized string: " << ostr.str();

  DataRequest dr_deserialized = dunedaq::serialization::deserialize<DataRequest>(bytes);

  BOOST_REQUIRE_EQUAL(dr.m_request_number, dr_deserialized.m_request_number);
  BOOST_REQUIRE_EQUAL(dr.m_trigger_number, dr_deserialized.m_trigger_number);
  BOOST_REQUIRE_EQUAL(dr.m_trigger_timestamp, dr_deserialized.m_trigger_timestamp);
  BOOST_REQUIRE_EQUAL(dr.m_window_offset, dr_deserialized.m_window_offset);
  BOOST_REQUIRE_EQUAL(dr.m_window_width, dr_deserialized.m_window_width);
  BOOST_REQUIRE_EQUAL(static_cast<int>(dr.m_request_mode), static_cast<int>(dr_deserialized.m_request_mode));
}

BOOST_AUTO_TEST_CASE(SerDes_MsgPack)
{

  DataRequest dr;
  dr.m_request_number = 1;
  dr.m_trigger_number = 2;
  dr.m_trigger_timestamp = 3;
  dr.m_window_offset = 4;
  dr.m_window_width = 5;
  dr.m_request_mode = DataRequest::mode_t::kLocalizedReadout;

  auto bytes = dunedaq::serialization::serialize(dr, dunedaq::serialization::kMsgPack);
  DataRequest dr_deserialized = dunedaq::serialization::deserialize<DataRequest>(bytes);

  BOOST_REQUIRE_EQUAL(dr.m_request_number, dr_deserialized.m_request_number);
  BOOST_REQUIRE_EQUAL(dr.m_trigger_number, dr_deserialized.m_trigger_number);
  BOOST_REQUIRE_EQUAL(dr.m_trigger_timestamp, dr_deserialized.m_trigger_timestamp);
  BOOST_REQUIRE_EQUAL(dr.m_window_offset, dr_deserialized.m_window_offset);
  BOOST_REQUIRE_EQUAL(dr.m_window_width, dr_deserialized.m_window_width);
  BOOST_REQUIRE_EQUAL(static_cast<int>(dr.m_request_mode), static_cast<int>(dr_deserialized.m_request_mode));
}
BOOST_AUTO_TEST_SUITE_END()
