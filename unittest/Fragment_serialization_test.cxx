/**
 * @file Fragment_serialization_test.cxx Fragment class Unit Tests
 *
 * This is part of the DUNE DAQ Application Framework, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#include "dfmessages/Fragment_serialization.hpp"

/**
 * @brief Name of this test module
 */
#define BOOST_TEST_MODULE Fragment_serialization_test // NOLINT

#include "boost/test/unit_test.hpp"

#include <string>
#include <utility>
#include <vector>

using namespace dunedaq::dataformats;

BOOST_AUTO_TEST_SUITE(Fragment_serialization_test)

BOOST_AUTO_TEST_CASE(SerDes_MsgPack)
{
  FragmentHeader header;
  header.size = sizeof(FragmentHeader) + 4;
  header.trigger_number = 1;
  header.trigger_timestamp = 2;
  header.run_number = 3;

  auto frag = malloc(sizeof(FragmentHeader) + 4);
  memcpy(frag, &header, sizeof(FragmentHeader));

  uint8_t one = 1, two = 2, three = 3, four = 4;                               // NOLINT(build/unsigned)
  memcpy(static_cast<uint8_t*>(frag) + sizeof(FragmentHeader), &one, 1);       // NOLINT(build/unsigned)
  memcpy(static_cast<uint8_t*>(frag) + sizeof(FragmentHeader) + 1, &two, 1);   // NOLINT(build/unsigned)
  memcpy(static_cast<uint8_t*>(frag) + sizeof(FragmentHeader) + 2, &three, 1); // NOLINT(build/unsigned)
  memcpy(static_cast<uint8_t*>(frag) + sizeof(FragmentHeader) + 3, &four, 1);  // NOLINT(build/unsigned)

  Fragment test_frag(frag, Fragment::BufferAdoptionMode::kTakeOverBuffer);
  auto bytes = dunedaq::serialization::serialize(test_frag, dunedaq::serialization::kMsgPack);

  Fragment frag_deserialized = dunedaq::serialization::deserialize<Fragment>(bytes);

  BOOST_REQUIRE_EQUAL(frag_deserialized.get_trigger_number(), test_frag.get_trigger_number());
  BOOST_REQUIRE_EQUAL(frag_deserialized.get_run_number(), test_frag.get_run_number());
  BOOST_REQUIRE_EQUAL(frag_deserialized.get_trigger_timestamp(), test_frag.get_trigger_timestamp());
  BOOST_REQUIRE_EQUAL(frag_deserialized.get_window_begin(), test_frag.get_window_begin());
  BOOST_REQUIRE_EQUAL(frag_deserialized.get_window_end(), test_frag.get_window_end());
  BOOST_REQUIRE_EQUAL(frag_deserialized.get_link_id().component_type, test_frag.get_link_id().component_type);
  BOOST_REQUIRE_EQUAL(frag_deserialized.get_link_id().region_id, test_frag.get_link_id().region_id);
  BOOST_REQUIRE_EQUAL(frag_deserialized.get_link_id().element_id, test_frag.get_link_id().element_id);
  BOOST_REQUIRE_EQUAL(frag_deserialized.get_error_bits(), test_frag.get_error_bits());
  BOOST_REQUIRE_EQUAL(frag_deserialized.get_fragment_type_code(), test_frag.get_fragment_type_code());
  BOOST_REQUIRE_EQUAL(frag_deserialized.get_size(), test_frag.get_size());

  BOOST_REQUIRE_EQUAL(*(static_cast<uint8_t*>(frag_deserialized.get_data()) + 0),
                      *(static_cast<uint8_t*>(test_frag.get_data()) + 0));
  BOOST_REQUIRE_EQUAL(*(static_cast<uint8_t*>(frag_deserialized.get_data()) + 1),
                      *(static_cast<uint8_t*>(test_frag.get_data()) + 1));
  BOOST_REQUIRE_EQUAL(*(static_cast<uint8_t*>(frag_deserialized.get_data()) + 2),
                      *(static_cast<uint8_t*>(test_frag.get_data()) + 2));
}

BOOST_AUTO_TEST_CASE(SerDes_JSON)
{
  FragmentHeader header;
  header.size = sizeof(FragmentHeader) + 4;
  header.trigger_number = 1;
  header.trigger_timestamp = 2;
  header.run_number = 3;

  auto frag = malloc(sizeof(FragmentHeader) + 4);
  memcpy(frag, &header, sizeof(FragmentHeader));

  uint8_t one = 1, two = 2, three = 3, four = 4;                               // NOLINT(build/unsigned)
  memcpy(static_cast<uint8_t*>(frag) + sizeof(FragmentHeader), &one, 1);       // NOLINT(build/unsigned)
  memcpy(static_cast<uint8_t*>(frag) + sizeof(FragmentHeader) + 1, &two, 1);   // NOLINT(build/unsigned)
  memcpy(static_cast<uint8_t*>(frag) + sizeof(FragmentHeader) + 2, &three, 1); // NOLINT(build/unsigned)
  memcpy(static_cast<uint8_t*>(frag) + sizeof(FragmentHeader) + 3, &four, 1);  // NOLINT(build/unsigned)

  Fragment test_frag(frag, Fragment::BufferAdoptionMode::kTakeOverBuffer);

  auto bytes = dunedaq::serialization::serialize(test_frag, dunedaq::serialization::kJSON);

  Fragment frag_deserialized = dunedaq::serialization::deserialize<Fragment>(bytes);

  BOOST_REQUIRE_EQUAL(frag_deserialized.get_size(), test_frag.get_size());
  BOOST_REQUIRE_EQUAL(frag_deserialized.get_trigger_number(), test_frag.get_trigger_number());
  BOOST_REQUIRE_EQUAL(frag_deserialized.get_run_number(), test_frag.get_run_number());
  BOOST_REQUIRE_EQUAL(frag_deserialized.get_trigger_timestamp(), test_frag.get_trigger_timestamp());
  BOOST_REQUIRE_EQUAL(frag_deserialized.get_window_begin(), test_frag.get_window_begin());
  BOOST_REQUIRE_EQUAL(frag_deserialized.get_window_end(), test_frag.get_window_end());
  BOOST_REQUIRE_EQUAL(frag_deserialized.get_link_id().component_type, test_frag.get_link_id().component_type);
  BOOST_REQUIRE_EQUAL(frag_deserialized.get_link_id().region_id, test_frag.get_link_id().region_id);
  BOOST_REQUIRE_EQUAL(frag_deserialized.get_link_id().element_id, test_frag.get_link_id().element_id);
  BOOST_REQUIRE_EQUAL(frag_deserialized.get_error_bits(), test_frag.get_error_bits());
  BOOST_REQUIRE_EQUAL(frag_deserialized.get_fragment_type_code(), test_frag.get_fragment_type_code());
  BOOST_REQUIRE_EQUAL(frag_deserialized.get_size(), test_frag.get_size());

  BOOST_REQUIRE_EQUAL(*(static_cast<uint8_t*>(frag_deserialized.get_data()) + 0),
                      *(static_cast<uint8_t*>(test_frag.get_data()) + 0));
  BOOST_REQUIRE_EQUAL(*(static_cast<uint8_t*>(frag_deserialized.get_data()) + 1),
                      *(static_cast<uint8_t*>(test_frag.get_data()) + 1));
  BOOST_REQUIRE_EQUAL(*(static_cast<uint8_t*>(frag_deserialized.get_data()) + 2),
                      *(static_cast<uint8_t*>(test_frag.get_data()) + 2));
}

BOOST_AUTO_TEST_SUITE_END()