/**
 * @file HSIEvent_test.cxx HSIEvent class Unit Tests
 *
 * This is part of the DUNE DAQ Application Framework, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#include "dfmessages/HSIEvent.hpp"

/**
 * @brief Name of this test module
 */
#define BOOST_TEST_MODULE HSIEvent_test // NOLINT

#include "TRACE/trace.h"
#include "boost/test/unit_test.hpp"

using namespace dunedaq::dfmessages;

BOOST_AUTO_TEST_SUITE(HSIEvent_test)

/**
 * @brief Check that HSIEvents have appropriate Copy/Move semantics
 */
BOOST_AUTO_TEST_CASE(CopyAndMoveSemantics)
{
  BOOST_REQUIRE(std::is_copy_constructible_v<HSIEvent>);
  BOOST_REQUIRE(std::is_copy_assignable_v<HSIEvent>);
  BOOST_REQUIRE(std::is_move_constructible_v<HSIEvent>);
  BOOST_REQUIRE(std::is_move_assignable_v<HSIEvent>);
}

BOOST_AUTO_TEST_CASE(DefaultConstructor)
{
  HSIEvent test_hsievent;
  BOOST_REQUIRE_EQUAL(test_hsievent.header, 0);
  BOOST_REQUIRE_EQUAL(test_hsievent.signal_map, 0);
  BOOST_REQUIRE_EQUAL(test_hsievent.timestamp, TypeDefaults::s_invalid_timestamp);
  BOOST_REQUIRE_EQUAL(test_hsievent.sequence_counter, 0);
}

BOOST_AUTO_TEST_CASE(SerDes_JSON)
{
  HSIEvent he(0x12345678, 0x11111111, 0x1234123456785678, 0x22222222);

  auto bytes = dunedaq::serialization::serialize(he, dunedaq::serialization::kJSON);

  std::ostringstream ostr;
  for (auto& b : bytes) {
    ostr << static_cast<char>(b);
  }
  TLOG(TLVL_INFO) << "Serialized string: " << ostr.str();

  HSIEvent he_deserialized = dunedaq::serialization::deserialize<HSIEvent>(bytes);

  BOOST_REQUIRE_EQUAL(he.header, he_deserialized.header);
  BOOST_REQUIRE_EQUAL(he.signal_map, he_deserialized.signal_map);
  BOOST_REQUIRE_EQUAL(he.timestamp, he_deserialized.timestamp);
  BOOST_REQUIRE_EQUAL(he.sequence_counter, he_deserialized.sequence_counter);
}

BOOST_AUTO_TEST_CASE(SerDes_MsgPack)
{

  HSIEvent he(0x12345678, 0x11111111, 0x1234123456785678, 0x22222222);

  auto bytes = dunedaq::serialization::serialize(he, dunedaq::serialization::kMsgPack);
  TLOG(TLVL_INFO) << "MsgPack message size: " << bytes.size() << " bytes";

  HSIEvent he_deserialized = dunedaq::serialization::deserialize<HSIEvent>(bytes);

  BOOST_REQUIRE_EQUAL(he.header, he_deserialized.header);
  BOOST_REQUIRE_EQUAL(he.signal_map, he_deserialized.signal_map);
  BOOST_REQUIRE_EQUAL(he.timestamp, he_deserialized.timestamp);
  BOOST_REQUIRE_EQUAL(he.sequence_counter, he_deserialized.sequence_counter);
}

BOOST_AUTO_TEST_SUITE_END()
