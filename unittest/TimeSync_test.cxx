/**
 * @file TimeSync_test.cxx TimeSync class Unit Tests
 *
 * This is part of the DUNE DAQ Application Framework, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#include "dfmessages/TimeSync.hpp"

/**
 * @brief Name of this test module
 */
#define BOOST_TEST_MODULE TimeSync_test // NOLINT

#include "boost/test/unit_test.hpp"

using namespace dunedaq::dfmessages;

BOOST_AUTO_TEST_SUITE(TimeSync_test)

/**
 * @brief Check that TimeSyncs have appropriate Copy/Move semantics
 */
BOOST_AUTO_TEST_CASE(CopyAndMoveSemantics)
{
  BOOST_REQUIRE(std::is_copy_constructible_v<TimeSync>);
  BOOST_REQUIRE(std::is_copy_assignable_v<TimeSync>);
  BOOST_REQUIRE(std::is_move_constructible_v<TimeSync>);
  BOOST_REQUIRE(std::is_move_assignable_v<TimeSync>);
}

/**
 * @brief Test the TimeSync constructor 
*/
BOOST_AUTO_TEST_CASE(Constructor)
{
  TimeSync ts(100);
  auto now = TimeSync::gettimeofday_us();

  BOOST_REQUIRE_EQUAL(ts.m_daq_time, 100);
  // Check that they are the same to within 1000 us.
  BOOST_REQUIRE_EQUAL(ts.m_system_time / 1000, now / 1000);
}

BOOST_AUTO_TEST_SUITE_END()
