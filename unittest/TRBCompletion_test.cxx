/**
 * @file TRBCompletion_test.cxx TRBCompletion class Unit Tests
 *
 * This is part of the DUNE DAQ Application Framework, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#include "dfmessages/TRBCompletion.hpp"

/**
 * @brief Name of this test module
 */
#define BOOST_TEST_MODULE TRBCompletion_test // NOLINT

#include "TRACE/trace.h"
#include "boost/test/unit_test.hpp"

#include <string>
#include <vector>

using namespace dunedaq::dfmessages;

BOOST_AUTO_TEST_SUITE(TRBCompletion_test)

/**
 * @brief Check that TRBCompletions have appropriate Copy/Move semantics
 */
BOOST_AUTO_TEST_CASE(CopyAndMoveSemantics)
{
  BOOST_REQUIRE(std::is_copy_constructible_v<TRBCompletion>);
  BOOST_REQUIRE(std::is_copy_assignable_v<TRBCompletion>);
  BOOST_REQUIRE(std::is_move_constructible_v<TRBCompletion>);
  BOOST_REQUIRE(std::is_move_assignable_v<TRBCompletion>);
}

BOOST_AUTO_TEST_CASE(DefaultConstruction)
{
  TRBCompletion tc;
  BOOST_REQUIRE_EQUAL(tc.run_number, TypeDefaults::s_invalid_run_number);
  BOOST_REQUIRE_EQUAL(tc.trigger_number, TypeDefaults::s_invalid_trigger_number);
  BOOST_REQUIRE_EQUAL(tc.source_id, dunedaq::daqdataformats::SourceID());
}

BOOST_AUTO_TEST_CASE(SerDes_MsgPack)
{
  TRBCompletion tc;
  tc.run_number = 1;
  tc.trigger_number = 2;
  tc.source_id = dunedaq::daqdataformats::SourceID(dunedaq::daqdataformats::SourceID::Subsystem::kTRBuilder, 3);

  auto bytes = dunedaq::serialization::serialize(tc, dunedaq::serialization::kMsgPack);
  TLOG(TLVL_INFO) << "MsgPack message size: " << bytes.size() << " bytes";
  TRBCompletion tc_deserialized = dunedaq::serialization::deserialize<TRBCompletion>(bytes);

  BOOST_REQUIRE_EQUAL(tc.run_number, tc_deserialized.run_number);
  BOOST_REQUIRE_EQUAL(tc.trigger_number, tc_deserialized.trigger_number);
  BOOST_REQUIRE_EQUAL(tc.source_id.id, tc_deserialized.source_id.id);
}

BOOST_AUTO_TEST_SUITE_END()
