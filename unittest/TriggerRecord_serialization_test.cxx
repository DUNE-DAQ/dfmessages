/**
 * @file TriggerRecord_serialization_test.cxx TriggerRecord class Unit Tests
 *
 * This is part of the DUNE DAQ Application Framework, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#include "dataformats/TriggerRecord.hpp"
#include "serialization/Serialization.hpp"

/**
 * @brief Name of this test module
 */
#define BOOST_TEST_MODULE TriggerRecord_serialization_test // NOLINT

#include "boost/test/unit_test.hpp"

#include <string>
#include <vector>

using namespace dunedaq::dataformats;

BOOST_AUTO_TEST_SUITE(TriggerRecord_serialization_test)

BOOST_AUTO_TEST_CASE(SerDes_MsgPack)
{
  /** TODO: Implement SerDes_MsgPack test for TriggerRecord */
}

BOOST_AUTO_TEST_CASE(SerDes_JSON)
{
  /** TODO: Implement SerDes_JSON test for TriggerRecord */
}

BOOST_AUTO_TEST_SUITE_END()