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

#include <memory>
#include <string>
#include <utility>
#include <vector>

using namespace dunedaq::daqdataformats;

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
  BOOST_REQUIRE_EQUAL(frag_deserialized.get_element_id().subsystem, test_frag.get_element_id().subsystem);
  BOOST_REQUIRE_EQUAL(frag_deserialized.get_element_id().id, test_frag.get_element_id().id);
  BOOST_REQUIRE_EQUAL(frag_deserialized.get_error_bits(), test_frag.get_error_bits());
  BOOST_REQUIRE_EQUAL(frag_deserialized.get_fragment_type_code(), test_frag.get_fragment_type_code());
  BOOST_REQUIRE_EQUAL(frag_deserialized.get_size(), test_frag.get_size());

  BOOST_REQUIRE_EQUAL(*(static_cast<uint8_t*>(frag_deserialized.get_data()) + 0), // NOLINT(build/unsigned)
                      *(static_cast<uint8_t*>(test_frag.get_data()) + 0));        // NOLINT(build/unsigned)
  BOOST_REQUIRE_EQUAL(*(static_cast<uint8_t*>(frag_deserialized.get_data()) + 1), // NOLINT(build/unsigned)
                      *(static_cast<uint8_t*>(test_frag.get_data()) + 1));        // NOLINT(build/unsigned)
  BOOST_REQUIRE_EQUAL(*(static_cast<uint8_t*>(frag_deserialized.get_data()) + 2), // NOLINT(build/unsigned)
                      *(static_cast<uint8_t*>(test_frag.get_data()) + 2));        // NOLINT(build/unsigned)
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
  BOOST_REQUIRE_EQUAL(frag_deserialized.get_element_id().subsystem, test_frag.get_element_id().subsystem);
  BOOST_REQUIRE_EQUAL(frag_deserialized.get_element_id().id, test_frag.get_element_id().id);
  BOOST_REQUIRE_EQUAL(frag_deserialized.get_error_bits(), test_frag.get_error_bits());
  BOOST_REQUIRE_EQUAL(frag_deserialized.get_fragment_type_code(), test_frag.get_fragment_type_code());
  BOOST_REQUIRE_EQUAL(frag_deserialized.get_size(), test_frag.get_size());

  BOOST_REQUIRE_EQUAL(*(static_cast<uint8_t*>(frag_deserialized.get_data()) + 0), // NOLINT(build/unsigned)
                      *(static_cast<uint8_t*>(test_frag.get_data()) + 0));        // NOLINT(build/unsigned)
  BOOST_REQUIRE_EQUAL(*(static_cast<uint8_t*>(frag_deserialized.get_data()) + 1), // NOLINT(build/unsigned)
                      *(static_cast<uint8_t*>(test_frag.get_data()) + 1));        // NOLINT(build/unsigned)
  BOOST_REQUIRE_EQUAL(*(static_cast<uint8_t*>(frag_deserialized.get_data()) + 2), // NOLINT(build/unsigned)
                      *(static_cast<uint8_t*>(test_frag.get_data()) + 2));        // NOLINT(build/unsigned)
}

BOOST_AUTO_TEST_CASE(Ptr_SerDes_MsgPack)
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

  auto test_frag = std::make_unique<Fragment>(frag, Fragment::BufferAdoptionMode::kTakeOverBuffer);
  auto bytes = dunedaq::serialization::serialize(test_frag, dunedaq::serialization::kMsgPack);

  auto frag_deserialized = dunedaq::serialization::deserialize<std::unique_ptr<Fragment>>(bytes);

  BOOST_REQUIRE_EQUAL(frag_deserialized->get_trigger_number(), test_frag->get_trigger_number());
  BOOST_REQUIRE_EQUAL(frag_deserialized->get_run_number(), test_frag->get_run_number());
  BOOST_REQUIRE_EQUAL(frag_deserialized->get_trigger_timestamp(), test_frag->get_trigger_timestamp());
  BOOST_REQUIRE_EQUAL(frag_deserialized->get_window_begin(), test_frag->get_window_begin());
  BOOST_REQUIRE_EQUAL(frag_deserialized->get_window_end(), test_frag->get_window_end());
  BOOST_REQUIRE_EQUAL(frag_deserialized->get_element_id().subsystem, test_frag->get_element_id().subsystem);
  BOOST_REQUIRE_EQUAL(frag_deserialized->get_element_id().id, test_frag->get_element_id().id);
  BOOST_REQUIRE_EQUAL(frag_deserialized->get_error_bits(), test_frag->get_error_bits());
  BOOST_REQUIRE_EQUAL(frag_deserialized->get_fragment_type_code(), test_frag->get_fragment_type_code());
  BOOST_REQUIRE_EQUAL(frag_deserialized->get_size(), test_frag->get_size());

  BOOST_REQUIRE_EQUAL(*(static_cast<uint8_t*>(frag_deserialized->get_data()) + 0), // NOLINT(build/unsigned)
                      *(static_cast<uint8_t*>(test_frag->get_data()) + 0));        // NOLINT(build/unsigned)
  BOOST_REQUIRE_EQUAL(*(static_cast<uint8_t*>(frag_deserialized->get_data()) + 1), // NOLINT(build/unsigned)
                      *(static_cast<uint8_t*>(test_frag->get_data()) + 1));        // NOLINT(build/unsigned)
  BOOST_REQUIRE_EQUAL(*(static_cast<uint8_t*>(frag_deserialized->get_data()) + 2), // NOLINT(build/unsigned)
                      *(static_cast<uint8_t*>(test_frag->get_data()) + 2));        // NOLINT(build/unsigned)
}

BOOST_AUTO_TEST_CASE(Ptr_SerDes_JSON)
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

  auto test_frag = std::make_unique<Fragment>(frag, Fragment::BufferAdoptionMode::kTakeOverBuffer);

  auto bytes = dunedaq::serialization::serialize(test_frag, dunedaq::serialization::kJSON);

  auto frag_deserialized = dunedaq::serialization::deserialize<std::unique_ptr<Fragment>>(bytes);

  BOOST_REQUIRE_EQUAL(frag_deserialized->get_size(), test_frag->get_size());
  BOOST_REQUIRE_EQUAL(frag_deserialized->get_trigger_number(), test_frag->get_trigger_number());
  BOOST_REQUIRE_EQUAL(frag_deserialized->get_run_number(), test_frag->get_run_number());
  BOOST_REQUIRE_EQUAL(frag_deserialized->get_trigger_timestamp(), test_frag->get_trigger_timestamp());
  BOOST_REQUIRE_EQUAL(frag_deserialized->get_window_begin(), test_frag->get_window_begin());
  BOOST_REQUIRE_EQUAL(frag_deserialized->get_window_end(), test_frag->get_window_end());
  BOOST_REQUIRE_EQUAL(frag_deserialized->get_element_id().subsystem, test_frag->get_element_id().subsystem);
  BOOST_REQUIRE_EQUAL(frag_deserialized->get_element_id().id, test_frag->get_element_id().id);
  BOOST_REQUIRE_EQUAL(frag_deserialized->get_error_bits(), test_frag->get_error_bits());
  BOOST_REQUIRE_EQUAL(frag_deserialized->get_fragment_type_code(), test_frag->get_fragment_type_code());
  BOOST_REQUIRE_EQUAL(frag_deserialized->get_size(), test_frag->get_size());

  BOOST_REQUIRE_EQUAL(*(static_cast<uint8_t*>(frag_deserialized->get_data()) + 0), // NOLINT(build/unsigned)
                      *(static_cast<uint8_t*>(test_frag->get_data()) + 0));        // NOLINT(build/unsigned)
  BOOST_REQUIRE_EQUAL(*(static_cast<uint8_t*>(frag_deserialized->get_data()) + 1), // NOLINT(build/unsigned)
                      *(static_cast<uint8_t*>(test_frag->get_data()) + 1));        // NOLINT(build/unsigned)
  BOOST_REQUIRE_EQUAL(*(static_cast<uint8_t*>(frag_deserialized->get_data()) + 2), // NOLINT(build/unsigned)
                      *(static_cast<uint8_t*>(test_frag->get_data()) + 2));        // NOLINT(build/unsigned)
}

BOOST_AUTO_TEST_CASE(Bad_JSON)
{
  std::string test_string = "J{ \"test_value\": \"test string\" }";
  std::vector<unsigned char> bytes(test_string.begin(), test_string.end());
  BOOST_REQUIRE_EXCEPTION(dunedaq::serialization::deserialize<Fragment>(bytes),
                          dunedaq::dfmessages::CannotDeserializeFragment,
                          [&](dunedaq::dfmessages::CannotDeserializeFragment) { return true; });
  BOOST_REQUIRE_EXCEPTION(dunedaq::serialization::deserialize<std::unique_ptr<Fragment>>(bytes),
                          dunedaq::dfmessages::CannotDeserializeFragment,
                          [&](dunedaq::dfmessages::CannotDeserializeFragment) { return true; });
}

BOOST_AUTO_TEST_CASE(Ptr_to_Fragment)
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

  auto test_frag = std::make_unique<Fragment>(frag, Fragment::BufferAdoptionMode::kTakeOverBuffer);
  auto bytes = dunedaq::serialization::serialize(test_frag, dunedaq::serialization::kMsgPack);

  auto frag_deserialized = dunedaq::serialization::deserialize<Fragment>(bytes);

  BOOST_REQUIRE_EQUAL(frag_deserialized.get_trigger_number(), test_frag->get_trigger_number());
  BOOST_REQUIRE_EQUAL(frag_deserialized.get_run_number(), test_frag->get_run_number());
  BOOST_REQUIRE_EQUAL(frag_deserialized.get_trigger_timestamp(), test_frag->get_trigger_timestamp());
  BOOST_REQUIRE_EQUAL(frag_deserialized.get_window_begin(), test_frag->get_window_begin());
  BOOST_REQUIRE_EQUAL(frag_deserialized.get_window_end(), test_frag->get_window_end());
  BOOST_REQUIRE_EQUAL(frag_deserialized.get_element_id().subsystem, test_frag->get_element_id().subsystem);
  BOOST_REQUIRE_EQUAL(frag_deserialized.get_element_id().id, test_frag->get_element_id().id);
  BOOST_REQUIRE_EQUAL(frag_deserialized.get_error_bits(), test_frag->get_error_bits());
  BOOST_REQUIRE_EQUAL(frag_deserialized.get_fragment_type_code(), test_frag->get_fragment_type_code());
  BOOST_REQUIRE_EQUAL(frag_deserialized.get_size(), test_frag->get_size());

  BOOST_REQUIRE_EQUAL(*(static_cast<uint8_t*>(frag_deserialized.get_data()) + 0), // NOLINT(build/unsigned)
                      *(static_cast<uint8_t*>(test_frag->get_data()) + 0));       // NOLINT(build/unsigned)
  BOOST_REQUIRE_EQUAL(*(static_cast<uint8_t*>(frag_deserialized.get_data()) + 1), // NOLINT(build/unsigned)
                      *(static_cast<uint8_t*>(test_frag->get_data()) + 1));       // NOLINT(build/unsigned)
  BOOST_REQUIRE_EQUAL(*(static_cast<uint8_t*>(frag_deserialized.get_data()) + 2), // NOLINT(build/unsigned)
                      *(static_cast<uint8_t*>(test_frag->get_data()) + 2));       // NOLINT(build/unsigned)
}

BOOST_AUTO_TEST_CASE(Fragment_to_Ptr)
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

  auto frag_deserialized = dunedaq::serialization::deserialize<std::unique_ptr<Fragment>>(bytes);

  BOOST_REQUIRE_EQUAL(frag_deserialized->get_trigger_number(), test_frag.get_trigger_number());
  BOOST_REQUIRE_EQUAL(frag_deserialized->get_run_number(), test_frag.get_run_number());
  BOOST_REQUIRE_EQUAL(frag_deserialized->get_trigger_timestamp(), test_frag.get_trigger_timestamp());
  BOOST_REQUIRE_EQUAL(frag_deserialized->get_window_begin(), test_frag.get_window_begin());
  BOOST_REQUIRE_EQUAL(frag_deserialized->get_window_end(), test_frag.get_window_end());
  BOOST_REQUIRE_EQUAL(frag_deserialized->get_element_id().subsystem, test_frag.get_element_id().subsystem);
  BOOST_REQUIRE_EQUAL(frag_deserialized->get_element_id().id, test_frag.get_element_id().id);
  BOOST_REQUIRE_EQUAL(frag_deserialized->get_error_bits(), test_frag.get_error_bits());
  BOOST_REQUIRE_EQUAL(frag_deserialized->get_fragment_type_code(), test_frag.get_fragment_type_code());
  BOOST_REQUIRE_EQUAL(frag_deserialized->get_size(), test_frag.get_size());

  BOOST_REQUIRE_EQUAL(*(static_cast<uint8_t*>(frag_deserialized->get_data()) + 0), // NOLINT(build/unsigned)
                      *(static_cast<uint8_t*>(test_frag.get_data()) + 0));         // NOLINT(build/unsigned)
  BOOST_REQUIRE_EQUAL(*(static_cast<uint8_t*>(frag_deserialized->get_data()) + 1), // NOLINT(build/unsigned)
                      *(static_cast<uint8_t*>(test_frag.get_data()) + 1));         // NOLINT(build/unsigned)
  BOOST_REQUIRE_EQUAL(*(static_cast<uint8_t*>(frag_deserialized->get_data()) + 2), // NOLINT(build/unsigned)
                      *(static_cast<uint8_t*>(test_frag.get_data()) + 2));         // NOLINT(build/unsigned)
}

BOOST_AUTO_TEST_SUITE_END()