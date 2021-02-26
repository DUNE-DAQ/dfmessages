/**
 * @file TriggerInhibit_test.cxx TriggerInhibit class Unit Tests
 *
 * This is part of the DUNE DAQ Application Framework, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#include "dfmessages/TriggerInhibit.hpp"

/**
 * @brief Name of this test module
 */
#define BOOST_TEST_MODULE TriggerInhibit_test // NOLINT

#include "TRACE/trace.h"
#include "boost/test/unit_test.hpp"

#include <string>
#include <vector>

using namespace dunedaq::dfmessages;

BOOST_AUTO_TEST_SUITE(TriggerInhibit_test)

/**
 * @brief Check that TriggerInhibits have appropriate Copy/Move semantics
 */
BOOST_AUTO_TEST_CASE(CopyAndMoveSemantics)
{
  BOOST_REQUIRE(std::is_copy_constructible_v<TriggerInhibit>);
  BOOST_REQUIRE(std::is_copy_assignable_v<TriggerInhibit>);
  BOOST_REQUIRE(std::is_move_constructible_v<TriggerInhibit>);
  BOOST_REQUIRE(std::is_move_assignable_v<TriggerInhibit>);
}

BOOST_AUTO_TEST_CASE(SerDes_JSON)
{
  TriggerInhibit ti;
  ti.busy = true;

  auto bytes = dunedaq::serialization::serialize(ti, dunedaq::serialization::kJSON);

  std::ostringstream ostr;
  for (auto& b : bytes) {
    ostr << static_cast<char>(b);
  }
  TLOG(TLVL_INFO) << "Serialized string: " << ostr.str();

  TriggerInhibit ti_deserialized = dunedaq::serialization::deserialize<TriggerInhibit>(bytes);

  BOOST_REQUIRE_EQUAL(ti.busy, ti_deserialized.busy);
}

BOOST_AUTO_TEST_CASE(SerDes_MsgPack)
{

  TriggerInhibit ti;
  ti.busy = true;

  auto bytes = dunedaq::serialization::serialize(ti, dunedaq::serialization::kMsgPack);
  TLOG(TLVL_INFO) << "MsgPack message size: " << bytes.size() << " bytes";
  TriggerInhibit ti_deserialized = dunedaq::serialization::deserialize<TriggerInhibit>(bytes);

  BOOST_REQUIRE_EQUAL(ti.busy, ti_deserialized.busy);
}

BOOST_AUTO_TEST_SUITE_END()