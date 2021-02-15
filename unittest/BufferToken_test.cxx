/**
 * @file BufferToken_test.cxx BufferToken class Unit Tests
 *
 * This is part of the DUNE DAQ Application Framework, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#include "dfmessages/BufferToken.hpp"

/**
 * @brief Name of this test module
 */
#define BOOST_TEST_MODULE BufferToken_test // NOLINT

#include "TRACE/trace.h"
#include "boost/test/unit_test.hpp"

#include <string>
#include <vector>

using namespace dunedaq::dfmessages;

BOOST_AUTO_TEST_SUITE(BufferToken_test)

/**
 * @brief Check that BufferTokens have appropriate Copy/Move semantics
 */
BOOST_AUTO_TEST_CASE(CopyAndMoveSemantics)
{
  BOOST_REQUIRE(std::is_copy_constructible_v<BufferToken>);
  BOOST_REQUIRE(std::is_copy_assignable_v<BufferToken>);
  BOOST_REQUIRE(std::is_move_constructible_v<BufferToken>);
  BOOST_REQUIRE(std::is_move_assignable_v<BufferToken>);
}

BOOST_AUTO_TEST_CASE(SerDes_JSON)
{
  BufferToken bt;
  bt.run_number = 1;

  auto bytes = dunedaq::serialization::serialize(bt, dunedaq::serialization::kJSON);

  std::ostringstream ostr;
  for (auto& b : bytes) {
    ostr << static_cast<char>(b);
  }
  TLOG(TLVL_INFO) << "Serialized string: " << ostr.str();

  BufferToken bt_deserialized = dunedaq::serialization::deserialize<BufferToken>(bytes);

  BOOST_REQUIRE_EQUAL(bt.run_number, bt_deserialized.run_number);
  BOOST_REQUIRE_EQUAL(bt.buffer_token_marker, bt_deserialized.buffer_token_marker);
}

BOOST_AUTO_TEST_CASE(SerDes_MsgPack)
{
  BufferToken bt;
  bt.run_number = 1;

  auto bytes = dunedaq::serialization::serialize(bt, dunedaq::serialization::kMsgPack);
  TLOG(TLVL_INFO) << "MsgPack message size: " << bytes.size() << " bytes";
  BufferToken bt_deserialized = dunedaq::serialization::deserialize<BufferToken>(bytes);

  BOOST_REQUIRE_EQUAL(bt.run_number, bt_deserialized.run_number);
  BOOST_REQUIRE_EQUAL(bt.buffer_token_marker, bt_deserialized.buffer_token_marker);
}

BOOST_AUTO_TEST_SUITE_END()