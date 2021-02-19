/**
 * @file TriggerDecisionToken_test.cxx TriggerDecisionToken class Unit Tests
 *
 * This is part of the DUNE DAQ Application Framework, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#include "dfmessages/TriggerDecisionToken.hpp"

/**
 * @brief Name of this test module
 */
#define BOOST_TEST_MODULE TriggerDecisionToken_test // NOLINT

#include "TRACE/trace.h"
#include "boost/test/unit_test.hpp"

#include <string>
#include <vector>

using namespace dunedaq::dfmessages;

BOOST_AUTO_TEST_SUITE(TriggerDecisionToken_test)

/**
 * @brief Check that TriggerDecisionTokens have appropriate Copy/Move semantics
 */
BOOST_AUTO_TEST_CASE(CopyAndMoveSemantics)
{
  BOOST_REQUIRE(std::is_copy_constructible_v<TriggerDecisionToken>);
  BOOST_REQUIRE(std::is_copy_assignable_v<TriggerDecisionToken>);
  BOOST_REQUIRE(std::is_move_constructible_v<TriggerDecisionToken>);
  BOOST_REQUIRE(std::is_move_assignable_v<TriggerDecisionToken>);
}

BOOST_AUTO_TEST_CASE(SerDes_JSON)
{
  TriggerDecisionToken bt;
  bt.run_number = 1;

  auto bytes = dunedaq::serialization::serialize(bt, dunedaq::serialization::kJSON);

  std::ostringstream ostr;
  for (auto& b : bytes) {
    ostr << static_cast<char>(b);
  }
  TLOG(TLVL_INFO) << "Serialized string: " << ostr.str();

  TriggerDecisionToken bt_deserialized = dunedaq::serialization::deserialize<TriggerDecisionToken>(bytes);

  BOOST_REQUIRE_EQUAL(bt.run_number, bt_deserialized.run_number);
}

BOOST_AUTO_TEST_CASE(SerDes_MsgPack)
{
  TriggerDecisionToken bt;
  bt.run_number = 1;

  auto bytes = dunedaq::serialization::serialize(bt, dunedaq::serialization::kMsgPack);
  TLOG(TLVL_INFO) << "MsgPack message size: " << bytes.size() << " bytes";
  TriggerDecisionToken bt_deserialized = dunedaq::serialization::deserialize<TriggerDecisionToken>(bytes);

  BOOST_REQUIRE_EQUAL(bt.run_number, bt_deserialized.run_number);
}

BOOST_AUTO_TEST_SUITE_END()