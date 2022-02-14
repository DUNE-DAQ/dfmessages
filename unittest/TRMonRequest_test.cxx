/**
 * @file TRMonRequest_test.cxx TRMonRequest class Unit Tests
 *
 * This is part of the DUNE DAQ Application Framework, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#include "dfmessages/TRMonRequest.hpp"

/**
 * @brief Name of this test module
 */
#define BOOST_TEST_MODULE TRMonRequest_test // NOLINT

#include "TRACE/trace.h"
#include "boost/test/unit_test.hpp"

using namespace dunedaq::dfmessages;

BOOST_AUTO_TEST_SUITE(TRMonRequest_test)

/**
 * @brief Check that TRMonRequests have appropriate Copy/Move semantics
 */
BOOST_AUTO_TEST_CASE(CopyAndMoveSemantics)
{
  BOOST_REQUIRE(std::is_copy_constructible_v<TRMonRequest>);
  BOOST_REQUIRE(std::is_copy_assignable_v<TRMonRequest>);
  BOOST_REQUIRE(std::is_move_constructible_v<TRMonRequest>);
  BOOST_REQUIRE(std::is_move_assignable_v<TRMonRequest>);
}

BOOST_AUTO_TEST_CASE(SerDes_JSON)
{
  TRMonRequest dr;
  dr.request_number = 1;
  dr.trigger_type = TRMonTriggerTypes::s_any_trigger_type;
  dr.run_number = 3;
  dr.data_destination = "test";

  auto bytes = dunedaq::serialization::serialize(dr, dunedaq::serialization::kJSON);

  std::ostringstream ostr;
  for (auto& b : bytes) {
    ostr << static_cast<char>(b);
  }
  TLOG(TLVL_INFO) << "Serialized string: " << ostr.str();

  TRMonRequest dr_deserialized = dunedaq::serialization::deserialize<TRMonRequest>(bytes);

  BOOST_REQUIRE_EQUAL(dr.request_number, dr_deserialized.request_number);
  BOOST_REQUIRE_EQUAL(dr.trigger_type, dr_deserialized.trigger_type);
  BOOST_REQUIRE_EQUAL(dr.run_number, dr_deserialized.run_number);
  BOOST_REQUIRE_EQUAL(dr.data_destination, dr_deserialized.data_destination);
}

BOOST_AUTO_TEST_CASE(SerDes_MsgPack)
{

  TRMonRequest dr;
  dr.request_number = 1;
  dr.trigger_type = 2;
  dr.run_number = 3;
  dr.data_destination = "test";

  auto bytes = dunedaq::serialization::serialize(dr, dunedaq::serialization::kMsgPack);
  TLOG(TLVL_INFO) << "MsgPack message size: " << bytes.size() << " bytes";
  TRMonRequest dr_deserialized = dunedaq::serialization::deserialize<TRMonRequest>(bytes);

  BOOST_REQUIRE_EQUAL(dr.request_number, dr_deserialized.request_number);
  BOOST_REQUIRE_EQUAL(dr.trigger_type, dr_deserialized.trigger_type);
  BOOST_REQUIRE_EQUAL(dr.run_number, dr_deserialized.run_number);
  BOOST_REQUIRE_EQUAL(dr.data_destination, dr_deserialized.data_destination);
}
BOOST_AUTO_TEST_SUITE_END()
