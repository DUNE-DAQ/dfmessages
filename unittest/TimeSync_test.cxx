/**
 * @file TimeSync_test.cxx TimeSync class Unit Tests
 *
 * This is part of the DUNE DAQ Application Framework, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#include "dfmessages/TimeSync.hpp"

#define BOOST_TEST_MODULE TimeSync_test // NOLINT

#include <boost/test/unit_test.hpp>
#include <string>
#include <vector>

using namespace dunedaq::dfmessages;

BOOST_AUTO_TEST_SUITE(TimeSync_test)

BOOST_AUTO_TEST_CASE(CopyAndMoveSemantics)
{
  BOOST_REQUIRE(std::is_copy_constructible_v<TimeSync>);
  BOOST_REQUIRE(std::is_copy_assignable_v<TimeSync>);
  BOOST_REQUIRE(std::is_move_constructible_v<TimeSync>);
  BOOST_REQUIRE(std::is_move_assignable_v<TimeSync>);
}

BOOST_AUTO_TEST_SUITE_END()