/**
 * @file ComponentRequest_serialization_test.cxx ComponentRequest class Unit Tests
 *
 * This is part of the DUNE DAQ Application Framework, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#include "dfmessages/ComponentRequest_serialization.hpp"

/**
 * @brief Name of this test module
 */
#define BOOST_TEST_MODULE ComponentRequest_serialization_test // NOLINT

#include "boost/test/unit_test.hpp"

#include <string>
#include <utility>
#include <vector>

using namespace dunedaq::daqdataformats;

BOOST_AUTO_TEST_SUITE(BOOST_TEST_MODULE)

BOOST_AUTO_TEST_CASE(SerDes_MsgPack)
{
  ComponentRequest component_request;
  component_request.component = SourceID{ SourceID::Subsystem::kDetectorReadout, 1 };
  component_request.window_begin = 12345;
  component_request.window_end = 45678;
  auto bytes = dunedaq::serialization::serialize(component_request, dunedaq::serialization::kMsgPack);

  ComponentRequest cr_deserialized = dunedaq::serialization::deserialize<ComponentRequest>(bytes);

  BOOST_REQUIRE_EQUAL(component_request.window_begin, cr_deserialized.window_begin);
  BOOST_REQUIRE_EQUAL(component_request.window_end, cr_deserialized.window_end);
  BOOST_REQUIRE_EQUAL(component_request.component.subsystem, cr_deserialized.component.subsystem);
  BOOST_REQUIRE_EQUAL(component_request.component.id, cr_deserialized.component.id);
}

BOOST_AUTO_TEST_CASE(SerDes_JSON)
{
  ComponentRequest component_request;
  component_request.component = SourceID{ SourceID::Subsystem::kDetectorReadout, 1 };
  component_request.window_begin = 12345;
  component_request.window_end = 45678;
  auto bytes = dunedaq::serialization::serialize(component_request, dunedaq::serialization::kJSON);

  ComponentRequest cr_deserialized = dunedaq::serialization::deserialize<ComponentRequest>(bytes);

  BOOST_REQUIRE_EQUAL(component_request.window_begin, cr_deserialized.window_begin);
  BOOST_REQUIRE_EQUAL(component_request.window_end, cr_deserialized.window_end);
  BOOST_REQUIRE_EQUAL(component_request.component.subsystem, cr_deserialized.component.subsystem);
  BOOST_REQUIRE_EQUAL(component_request.component.id, cr_deserialized.component.id);
}

BOOST_AUTO_TEST_SUITE_END()
