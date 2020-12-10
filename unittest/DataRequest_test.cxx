/**
 * @file DataRequest_test.cxx DataRequest class Unit Tests
 *
 * This is part of the DUNE DAQ Application Framework, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#include "dfmessages/DataRequest.hpp"

#define BOOST_TEST_MODULE DataRequest_test // NOLINT

#include <boost/test/unit_test.hpp>
#include <string>
#include <vector>

using namespace dunedaq::dfmessages;

BOOST_AUTO_TEST_SUITE(DataRequest_test)

BOOST_AUTO_TEST_CASE(CopyAndMoveSemantics)
{
  BOOST_REQUIRE(std::is_copy_constructible_v<DataRequest>);
  BOOST_REQUIRE(std::is_copy_assignable_v<DataRequest>);
  BOOST_REQUIRE(std::is_move_constructible_v<DataRequest>);
  BOOST_REQUIRE(std::is_move_assignable_v<DataRequest>);
}

BOOST_AUTO_TEST_SUITE_END()