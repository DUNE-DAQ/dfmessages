/**
 * @file TriggerRecord_serialization_test.cxx TriggerRecord class serialization Unit Tests
 *
 * This is part of the DUNE DAQ Application Framework, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#include "dfmessages/TriggerRecord_serialization.hpp"

/**
 * @brief Name of this test module
 */
#define BOOST_TEST_MODULE TriggerRecord_serialization_test // NOLINT

#include "boost/test/unit_test.hpp"

#include <memory>
#include <string>
#include <utility>
#include <vector>

using namespace dunedaq::daqdataformats;

BOOST_AUTO_TEST_SUITE(TriggerRecord_serialization_test)

BOOST_AUTO_TEST_CASE(SerDes_MsgPack)
{
  // Setup
  std::vector<ComponentRequest> components;
  components.emplace_back();
  components.back().component.subsystem = SourceID::Subsystem::kDetectorReadout;
  components.back().component.id = 2;
  components.back().window_begin = 3;
  components.back().window_end = 4;
  components.emplace_back();
  components.back().component.subsystem = SourceID::Subsystem::kDetectorReadout;
  components.back().component.id = 6;
  components.back().window_begin = 7;
  components.back().window_end = 8;

  TriggerRecordHeader record_header(components);
  record_header.set_trigger_number(1);
  record_header.set_trigger_timestamp(2);
  record_header.set_run_number(3);
  record_header.set_trigger_type(4);
  record_header.set_sequence_number(5);
  record_header.set_max_sequence_number(6);

  TriggerRecord record(record_header);

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

  auto another_frag = malloc(sizeof(FragmentHeader) + 8);
  header.size = sizeof(FragmentHeader) + 8;
  memcpy(another_frag, &header, sizeof(FragmentHeader));

  uint8_t five = 5, six = 6, seven = 7, eight = 8;                                      // NOLINT(build/unsigned)
  uint8_t nine = 9, ten = 10, eleven = 11, twelve = 12;                                 // NOLINT(build/unsigned)
  memcpy(static_cast<uint8_t*>(another_frag) + sizeof(FragmentHeader), &five, 1);       // NOLINT(build/unsigned)
  memcpy(static_cast<uint8_t*>(another_frag) + sizeof(FragmentHeader) + 1, &six, 1);    // NOLINT(build/unsigned)
  memcpy(static_cast<uint8_t*>(another_frag) + sizeof(FragmentHeader) + 2, &seven, 1);  // NOLINT(build/unsigned)
  memcpy(static_cast<uint8_t*>(another_frag) + sizeof(FragmentHeader) + 3, &eight, 1);  // NOLINT(build/unsigned)
  memcpy(static_cast<uint8_t*>(another_frag) + sizeof(FragmentHeader) + 4, &nine, 1);   // NOLINT(build/unsigned)
  memcpy(static_cast<uint8_t*>(another_frag) + sizeof(FragmentHeader) + 5, &ten, 1);    // NOLINT(build/unsigned)
  memcpy(static_cast<uint8_t*>(another_frag) + sizeof(FragmentHeader) + 6, &eleven, 1); // NOLINT(build/unsigned)
  memcpy(static_cast<uint8_t*>(another_frag) + sizeof(FragmentHeader) + 7, &twelve, 1); // NOLINT(build/unsigned)

  auto test_frag = std::make_unique<Fragment>(frag, Fragment::BufferAdoptionMode::kTakeOverBuffer);
  auto another_test_frag = std::make_unique<Fragment>(another_frag, Fragment::BufferAdoptionMode::kTakeOverBuffer);

  record.add_fragment(std::move(test_frag));
  record.add_fragment(std::move(another_test_frag));

  // SERIALIZE
  auto bytes = dunedaq::serialization::serialize(record, dunedaq::serialization::kMsgPack);

  // DESERIALIZE
  TriggerRecord deserialized = dunedaq::serialization::deserialize<TriggerRecord>(bytes);

  // TEST
  BOOST_REQUIRE_EQUAL(deserialized.get_header_data().num_requested_components, 2);
  BOOST_REQUIRE_EQUAL(deserialized.get_header_data().trigger_number, 1);
  BOOST_REQUIRE_EQUAL(deserialized.get_header_data().trigger_timestamp, 2);
  BOOST_REQUIRE_EQUAL(deserialized.get_header_data().run_number, 3);
  BOOST_REQUIRE_EQUAL(deserialized.get_header_data().trigger_type, 4);
  BOOST_REQUIRE_EQUAL(deserialized.get_header_data().sequence_number, 5);
  BOOST_REQUIRE_EQUAL(deserialized.get_header_data().max_sequence_number, 6);

  BOOST_REQUIRE_EQUAL(deserialized.get_fragments_ref().size(), 2);

  BOOST_REQUIRE_EQUAL(deserialized.get_fragments_ref().at(0)->get_trigger_number(), 1);
  BOOST_REQUIRE_EQUAL(deserialized.get_fragments_ref().at(0)->get_trigger_timestamp(), 2);
  BOOST_REQUIRE_EQUAL(deserialized.get_fragments_ref().at(0)->get_run_number(), 3);
  BOOST_REQUIRE_EQUAL(deserialized.get_fragments_ref().at(1)->get_trigger_number(), 1);
  BOOST_REQUIRE_EQUAL(deserialized.get_fragments_ref().at(1)->get_trigger_timestamp(), 2);
  BOOST_REQUIRE_EQUAL(deserialized.get_fragments_ref().at(1)->get_run_number(), 3);

  BOOST_REQUIRE_EQUAL(
    *(static_cast<uint8_t*>(deserialized.get_fragments_ref().at(0)->get_data()) + 0), // NOLINT(build/unsigned)
    1);                                                                               // NOLINT(build/unsigned)
  BOOST_REQUIRE_EQUAL(
    *(static_cast<uint8_t*>(deserialized.get_fragments_ref().at(0)->get_data()) + 1), // NOLINT(build/unsigned)
    2);                                                                               // NOLINT(build/unsigned)
  BOOST_REQUIRE_EQUAL(
    *(static_cast<uint8_t*>(deserialized.get_fragments_ref().at(0)->get_data()) + 2), // NOLINT(build/unsigned)
    3);                                                                               // NOLINT(build/unsigned)
  BOOST_REQUIRE_EQUAL(
    *(static_cast<uint8_t*>(deserialized.get_fragments_ref().at(0)->get_data()) + 3), // NOLINT(build/unsigned)
    4);                                                                               // NOLINT(build/unsigned)

  BOOST_REQUIRE_EQUAL(
    *(static_cast<uint8_t*>(deserialized.get_fragments_ref().at(1)->get_data()) + 0), // NOLINT(build/unsigned)
    5);                                                                               // NOLINT(build/unsigned)
  BOOST_REQUIRE_EQUAL(
    *(static_cast<uint8_t*>(deserialized.get_fragments_ref().at(1)->get_data()) + 1), // NOLINT(build/unsigned)
    6);                                                                               // NOLINT(build/unsigned)
  BOOST_REQUIRE_EQUAL(
    *(static_cast<uint8_t*>(deserialized.get_fragments_ref().at(1)->get_data()) + 2), // NOLINT(build/unsigned)
    7);                                                                               // NOLINT(build/unsigned)
  BOOST_REQUIRE_EQUAL(
    *(static_cast<uint8_t*>(deserialized.get_fragments_ref().at(1)->get_data()) + 3), // NOLINT(build/unsigned)
    8);                                                                               // NOLINT(build/unsigned)
  BOOST_REQUIRE_EQUAL(
    *(static_cast<uint8_t*>(deserialized.get_fragments_ref().at(1)->get_data()) + 4), // NOLINT(build/unsigned)
    9);                                                                               // NOLINT(build/unsigned)
  BOOST_REQUIRE_EQUAL(
    *(static_cast<uint8_t*>(deserialized.get_fragments_ref().at(1)->get_data()) + 5), // NOLINT(build/unsigned)
    10);                                                                              // NOLINT(build/unsigned
  BOOST_REQUIRE_EQUAL(
    *(static_cast<uint8_t*>(deserialized.get_fragments_ref().at(1)->get_data()) + 6), // NOLINT(build/unsigned)
    11);                                                                              // NOLINT(build/unsigned)
  BOOST_REQUIRE_EQUAL(
    *(static_cast<uint8_t*>(deserialized.get_fragments_ref().at(1)->get_data()) + 7), // NOLINT(build/unsigned)
    12);                                                                              // NOLINT(build/unsigned)
}

BOOST_AUTO_TEST_CASE(SerDes_JSON)
{

  // Setup
  std::vector<ComponentRequest> components;
  components.emplace_back();
  components.back().component.subsystem = SourceID::Subsystem::kDetectorReadout;
  components.back().component.id = 2;
  components.back().window_begin = 3;
  components.back().window_end = 4;
  components.emplace_back();
  components.back().component.subsystem = SourceID::Subsystem::kDetectorReadout;
  components.back().component.id = 6;
  components.back().window_begin = 7;
  components.back().window_end = 8;

  TriggerRecordHeader record_header(components);
  record_header.set_trigger_number(1);
  record_header.set_trigger_timestamp(2);
  record_header.set_run_number(3);
  record_header.set_trigger_type(4);
  record_header.set_sequence_number(5);
  record_header.set_max_sequence_number(6);

  TriggerRecord record(record_header);

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

  auto another_frag = malloc(sizeof(FragmentHeader) + 8);
  header.size = sizeof(FragmentHeader) + 8;
  memcpy(another_frag, &header, sizeof(FragmentHeader));

  uint8_t five = 5, six = 6, seven = 7, eight = 8;                                      // NOLINT(build/unsigned)
  uint8_t nine = 9, ten = 10, eleven = 11, twelve = 12;                                 // NOLINT(build/unsigned)
  memcpy(static_cast<uint8_t*>(another_frag) + sizeof(FragmentHeader), &five, 1);       // NOLINT(build/unsigned)
  memcpy(static_cast<uint8_t*>(another_frag) + sizeof(FragmentHeader) + 1, &six, 1);    // NOLINT(build/unsigned)
  memcpy(static_cast<uint8_t*>(another_frag) + sizeof(FragmentHeader) + 2, &seven, 1);  // NOLINT(build/unsigned)
  memcpy(static_cast<uint8_t*>(another_frag) + sizeof(FragmentHeader) + 3, &eight, 1);  // NOLINT(build/unsigned)
  memcpy(static_cast<uint8_t*>(another_frag) + sizeof(FragmentHeader) + 4, &nine, 1);   // NOLINT(build/unsigned)
  memcpy(static_cast<uint8_t*>(another_frag) + sizeof(FragmentHeader) + 5, &ten, 1);    // NOLINT(build/unsigned)
  memcpy(static_cast<uint8_t*>(another_frag) + sizeof(FragmentHeader) + 6, &eleven, 1); // NOLINT(build/unsigned)
  memcpy(static_cast<uint8_t*>(another_frag) + sizeof(FragmentHeader) + 7, &twelve, 1); // NOLINT(build/unsigned)

  auto test_frag = std::make_unique<Fragment>(frag, Fragment::BufferAdoptionMode::kTakeOverBuffer);
  auto another_test_frag = std::make_unique<Fragment>(another_frag, Fragment::BufferAdoptionMode::kTakeOverBuffer);

  record.add_fragment(std::move(test_frag));
  record.add_fragment(std::move(another_test_frag));

  // SERIALIZE
  auto bytes = dunedaq::serialization::serialize(record, dunedaq::serialization::kJSON);

  // DESERIALIZE
  TriggerRecord deserialized = dunedaq::serialization::deserialize<TriggerRecord>(bytes);

  // TEST
  BOOST_REQUIRE_EQUAL(deserialized.get_header_data().num_requested_components, 2);
  BOOST_REQUIRE_EQUAL(deserialized.get_header_data().trigger_number, 1);
  BOOST_REQUIRE_EQUAL(deserialized.get_header_data().trigger_timestamp, 2);
  BOOST_REQUIRE_EQUAL(deserialized.get_header_data().run_number, 3);
  BOOST_REQUIRE_EQUAL(deserialized.get_header_data().trigger_type, 4);
  BOOST_REQUIRE_EQUAL(deserialized.get_header_data().sequence_number, 5);
  BOOST_REQUIRE_EQUAL(deserialized.get_header_data().max_sequence_number, 6);

  BOOST_REQUIRE_EQUAL(deserialized.get_fragments_ref().size(), 2);

  BOOST_REQUIRE_EQUAL(deserialized.get_fragments_ref().at(0)->get_trigger_number(), 1);
  BOOST_REQUIRE_EQUAL(deserialized.get_fragments_ref().at(0)->get_trigger_timestamp(), 2);
  BOOST_REQUIRE_EQUAL(deserialized.get_fragments_ref().at(0)->get_run_number(), 3);
  BOOST_REQUIRE_EQUAL(deserialized.get_fragments_ref().at(1)->get_trigger_number(), 1);
  BOOST_REQUIRE_EQUAL(deserialized.get_fragments_ref().at(1)->get_trigger_timestamp(), 2);
  BOOST_REQUIRE_EQUAL(deserialized.get_fragments_ref().at(1)->get_run_number(), 3);

  BOOST_REQUIRE_EQUAL(
    *(static_cast<uint8_t*>(deserialized.get_fragments_ref().at(0)->get_data()) + 0), // NOLINT(build/unsigned)
    1);                                                                               // NOLINT(build/unsigned)
  BOOST_REQUIRE_EQUAL(
    *(static_cast<uint8_t*>(deserialized.get_fragments_ref().at(0)->get_data()) + 1), // NOLINT(build/unsigned)
    2);                                                                               // NOLINT(build/unsigned)
  BOOST_REQUIRE_EQUAL(
    *(static_cast<uint8_t*>(deserialized.get_fragments_ref().at(0)->get_data()) + 2), // NOLINT(build/unsigned)
    3);                                                                               // NOLINT(build/unsigned)
  BOOST_REQUIRE_EQUAL(
    *(static_cast<uint8_t*>(deserialized.get_fragments_ref().at(0)->get_data()) + 3), // NOLINT(build/unsigned)
    4);                                                                               // NOLINT(build/unsigned)

  BOOST_REQUIRE_EQUAL(
    *(static_cast<uint8_t*>(deserialized.get_fragments_ref().at(1)->get_data()) + 0), // NOLINT(build/unsigned)
    5);                                                                               // NOLINT(build/unsigned)
  BOOST_REQUIRE_EQUAL(
    *(static_cast<uint8_t*>(deserialized.get_fragments_ref().at(1)->get_data()) + 1), // NOLINT(build/unsigned)
    6);                                                                               // NOLINT(build/unsigned)
  BOOST_REQUIRE_EQUAL(
    *(static_cast<uint8_t*>(deserialized.get_fragments_ref().at(1)->get_data()) + 2), // NOLINT(build/unsigned)
    7);                                                                               // NOLINT(build/unsigned)
  BOOST_REQUIRE_EQUAL(
    *(static_cast<uint8_t*>(deserialized.get_fragments_ref().at(1)->get_data()) + 3), // NOLINT(build/unsigned)
    8);                                                                               // NOLINT(build/unsigned)
  BOOST_REQUIRE_EQUAL(
    *(static_cast<uint8_t*>(deserialized.get_fragments_ref().at(1)->get_data()) + 4), // NOLINT(build/unsigned)
    9);                                                                               // NOLINT(build/unsigned)
  BOOST_REQUIRE_EQUAL(
    *(static_cast<uint8_t*>(deserialized.get_fragments_ref().at(1)->get_data()) + 5), // NOLINT(build/unsigned)
    10);                                                                              // NOLINT(build/unsigned
  BOOST_REQUIRE_EQUAL(
    *(static_cast<uint8_t*>(deserialized.get_fragments_ref().at(1)->get_data()) + 6), // NOLINT(build/unsigned)
    11);                                                                              // NOLINT(build/unsigned)
  BOOST_REQUIRE_EQUAL(
    *(static_cast<uint8_t*>(deserialized.get_fragments_ref().at(1)->get_data()) + 7), // NOLINT(build/unsigned)
    12);                                                                              // NOLINT(build/unsigned)
}

BOOST_AUTO_TEST_CASE(Ptr_SerDes_MsgPack)
{
  // Setup
  std::vector<ComponentRequest> components;
  components.emplace_back();
  components.back().component.subsystem = SourceID::Subsystem::kDetectorReadout;
  components.back().component.id = 2;
  components.back().window_begin = 3;
  components.back().window_end = 4;
  components.emplace_back();
  components.back().component.subsystem = SourceID::Subsystem::kDetectorReadout;
  components.back().component.id = 6;
  components.back().window_begin = 7;
  components.back().window_end = 8;

  TriggerRecordHeader record_header(components);
  record_header.set_trigger_number(1);
  record_header.set_trigger_timestamp(2);
  record_header.set_run_number(3);
  record_header.set_trigger_type(4);
  record_header.set_sequence_number(5);
  record_header.set_max_sequence_number(6);

  auto record = std::make_unique<TriggerRecord>(record_header);

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

  auto another_frag = malloc(sizeof(FragmentHeader) + 8);
  header.size = sizeof(FragmentHeader) + 8;
  memcpy(another_frag, &header, sizeof(FragmentHeader));

  uint8_t five = 5, six = 6, seven = 7, eight = 8;                                      // NOLINT(build/unsigned)
  uint8_t nine = 9, ten = 10, eleven = 11, twelve = 12;                                 // NOLINT(build/unsigned)
  memcpy(static_cast<uint8_t*>(another_frag) + sizeof(FragmentHeader), &five, 1);       // NOLINT(build/unsigned)
  memcpy(static_cast<uint8_t*>(another_frag) + sizeof(FragmentHeader) + 1, &six, 1);    // NOLINT(build/unsigned)
  memcpy(static_cast<uint8_t*>(another_frag) + sizeof(FragmentHeader) + 2, &seven, 1);  // NOLINT(build/unsigned)
  memcpy(static_cast<uint8_t*>(another_frag) + sizeof(FragmentHeader) + 3, &eight, 1);  // NOLINT(build/unsigned)
  memcpy(static_cast<uint8_t*>(another_frag) + sizeof(FragmentHeader) + 4, &nine, 1);   // NOLINT(build/unsigned)
  memcpy(static_cast<uint8_t*>(another_frag) + sizeof(FragmentHeader) + 5, &ten, 1);    // NOLINT(build/unsigned)
  memcpy(static_cast<uint8_t*>(another_frag) + sizeof(FragmentHeader) + 6, &eleven, 1); // NOLINT(build/unsigned)
  memcpy(static_cast<uint8_t*>(another_frag) + sizeof(FragmentHeader) + 7, &twelve, 1); // NOLINT(build/unsigned)

  auto test_frag = std::make_unique<Fragment>(frag, Fragment::BufferAdoptionMode::kTakeOverBuffer);
  auto another_test_frag = std::make_unique<Fragment>(another_frag, Fragment::BufferAdoptionMode::kTakeOverBuffer);

  record->add_fragment(std::move(test_frag));
  record->add_fragment(std::move(another_test_frag));

  // SERIALIZE
  auto bytes = dunedaq::serialization::serialize(record, dunedaq::serialization::kMsgPack);

  // DESERIALIZE
  auto deserialized = dunedaq::serialization::deserialize<std::unique_ptr<TriggerRecord>>(bytes);

  // TEST
  BOOST_REQUIRE_EQUAL(deserialized->get_header_data().num_requested_components, 2);
  BOOST_REQUIRE_EQUAL(deserialized->get_header_data().trigger_number, 1);
  BOOST_REQUIRE_EQUAL(deserialized->get_header_data().trigger_timestamp, 2);
  BOOST_REQUIRE_EQUAL(deserialized->get_header_data().run_number, 3);
  BOOST_REQUIRE_EQUAL(deserialized->get_header_data().trigger_type, 4);
  BOOST_REQUIRE_EQUAL(deserialized->get_header_data().sequence_number, 5);
  BOOST_REQUIRE_EQUAL(deserialized->get_header_data().max_sequence_number, 6);

  BOOST_REQUIRE_EQUAL(deserialized->get_fragments_ref().size(), 2);

  BOOST_REQUIRE_EQUAL(deserialized->get_fragments_ref().at(0)->get_trigger_number(), 1);
  BOOST_REQUIRE_EQUAL(deserialized->get_fragments_ref().at(0)->get_trigger_timestamp(), 2);
  BOOST_REQUIRE_EQUAL(deserialized->get_fragments_ref().at(0)->get_run_number(), 3);
  BOOST_REQUIRE_EQUAL(deserialized->get_fragments_ref().at(1)->get_trigger_number(), 1);
  BOOST_REQUIRE_EQUAL(deserialized->get_fragments_ref().at(1)->get_trigger_timestamp(), 2);
  BOOST_REQUIRE_EQUAL(deserialized->get_fragments_ref().at(1)->get_run_number(), 3);

  BOOST_REQUIRE_EQUAL(
    *(static_cast<uint8_t*>(deserialized->get_fragments_ref().at(0)->get_data()) + 0), // NOLINT(build/unsigned)
    1);                                                                                // NOLINT(build/unsigned)
  BOOST_REQUIRE_EQUAL(
    *(static_cast<uint8_t*>(deserialized->get_fragments_ref().at(0)->get_data()) + 1), // NOLINT(build/unsigned)
    2);                                                                                // NOLINT(build/unsigned)
  BOOST_REQUIRE_EQUAL(
    *(static_cast<uint8_t*>(deserialized->get_fragments_ref().at(0)->get_data()) + 2), // NOLINT(build/unsigned)
    3);                                                                                // NOLINT(build/unsigned)
  BOOST_REQUIRE_EQUAL(
    *(static_cast<uint8_t*>(deserialized->get_fragments_ref().at(0)->get_data()) + 3), // NOLINT(build/unsigned)
    4);                                                                                // NOLINT(build/unsigned)

  BOOST_REQUIRE_EQUAL(
    *(static_cast<uint8_t*>(deserialized->get_fragments_ref().at(1)->get_data()) + 0), // NOLINT(build/unsigned)
    5);                                                                                // NOLINT(build/unsigned)
  BOOST_REQUIRE_EQUAL(
    *(static_cast<uint8_t*>(deserialized->get_fragments_ref().at(1)->get_data()) + 1), // NOLINT(build/unsigned)
    6);                                                                                // NOLINT(build/unsigned)
  BOOST_REQUIRE_EQUAL(
    *(static_cast<uint8_t*>(deserialized->get_fragments_ref().at(1)->get_data()) + 2), // NOLINT(build/unsigned)
    7);                                                                                // NOLINT(build/unsigned)
  BOOST_REQUIRE_EQUAL(
    *(static_cast<uint8_t*>(deserialized->get_fragments_ref().at(1)->get_data()) + 3), // NOLINT(build/unsigned)
    8);                                                                                // NOLINT(build/unsigned)
  BOOST_REQUIRE_EQUAL(
    *(static_cast<uint8_t*>(deserialized->get_fragments_ref().at(1)->get_data()) + 4), // NOLINT(build/unsigned)
    9);                                                                                // NOLINT(build/unsigned)
  BOOST_REQUIRE_EQUAL(
    *(static_cast<uint8_t*>(deserialized->get_fragments_ref().at(1)->get_data()) + 5), // NOLINT(build/unsigned)
    10);                                                                               // NOLINT(build/unsigned
  BOOST_REQUIRE_EQUAL(
    *(static_cast<uint8_t*>(deserialized->get_fragments_ref().at(1)->get_data()) + 6), // NOLINT(build/unsigned)
    11);                                                                               // NOLINT(build/unsigned)
  BOOST_REQUIRE_EQUAL(
    *(static_cast<uint8_t*>(deserialized->get_fragments_ref().at(1)->get_data()) + 7), // NOLINT(build/unsigned)
    12);                                                                               // NOLINT(build/unsigned)
}

BOOST_AUTO_TEST_CASE(Ptr_SerDes_JSON)
{

  // Setup
  std::vector<ComponentRequest> components;
  components.emplace_back();
  components.back().component.subsystem = SourceID::Subsystem::kDetectorReadout;
  components.back().component.id = 2;
  components.back().window_begin = 3;
  components.back().window_end = 4;
  components.emplace_back();
  components.back().component.subsystem = SourceID::Subsystem::kDetectorReadout;
  components.back().component.id = 6;
  components.back().window_begin = 7;
  components.back().window_end = 8;

  TriggerRecordHeader record_header(components);
  record_header.set_trigger_number(1);
  record_header.set_trigger_timestamp(2);
  record_header.set_run_number(3);
  record_header.set_trigger_type(4);
  record_header.set_sequence_number(5);
  record_header.set_max_sequence_number(6);

  auto record = std::make_unique<TriggerRecord>(record_header);

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

  auto another_frag = malloc(sizeof(FragmentHeader) + 8);
  header.size = sizeof(FragmentHeader) + 8;
  memcpy(another_frag, &header, sizeof(FragmentHeader));

  uint8_t five = 5, six = 6, seven = 7, eight = 8;                                      // NOLINT(build/unsigned)
  uint8_t nine = 9, ten = 10, eleven = 11, twelve = 12;                                 // NOLINT(build/unsigned)
  memcpy(static_cast<uint8_t*>(another_frag) + sizeof(FragmentHeader), &five, 1);       // NOLINT(build/unsigned)
  memcpy(static_cast<uint8_t*>(another_frag) + sizeof(FragmentHeader) + 1, &six, 1);    // NOLINT(build/unsigned)
  memcpy(static_cast<uint8_t*>(another_frag) + sizeof(FragmentHeader) + 2, &seven, 1);  // NOLINT(build/unsigned)
  memcpy(static_cast<uint8_t*>(another_frag) + sizeof(FragmentHeader) + 3, &eight, 1);  // NOLINT(build/unsigned)
  memcpy(static_cast<uint8_t*>(another_frag) + sizeof(FragmentHeader) + 4, &nine, 1);   // NOLINT(build/unsigned)
  memcpy(static_cast<uint8_t*>(another_frag) + sizeof(FragmentHeader) + 5, &ten, 1);    // NOLINT(build/unsigned)
  memcpy(static_cast<uint8_t*>(another_frag) + sizeof(FragmentHeader) + 6, &eleven, 1); // NOLINT(build/unsigned)
  memcpy(static_cast<uint8_t*>(another_frag) + sizeof(FragmentHeader) + 7, &twelve, 1); // NOLINT(build/unsigned)

  auto test_frag = std::make_unique<Fragment>(frag, Fragment::BufferAdoptionMode::kTakeOverBuffer);
  auto another_test_frag = std::make_unique<Fragment>(another_frag, Fragment::BufferAdoptionMode::kTakeOverBuffer);

  record->add_fragment(std::move(test_frag));
  record->add_fragment(std::move(another_test_frag));

  // SERIALIZE
  auto bytes = dunedaq::serialization::serialize(record, dunedaq::serialization::kJSON);

  // DESERIALIZE
  auto deserialized = dunedaq::serialization::deserialize<std::unique_ptr<TriggerRecord>>(bytes);

  // TEST
  BOOST_REQUIRE_EQUAL(deserialized->get_header_data().num_requested_components, 2);
  BOOST_REQUIRE_EQUAL(deserialized->get_header_data().trigger_number, 1);
  BOOST_REQUIRE_EQUAL(deserialized->get_header_data().trigger_timestamp, 2);
  BOOST_REQUIRE_EQUAL(deserialized->get_header_data().run_number, 3);
  BOOST_REQUIRE_EQUAL(deserialized->get_header_data().trigger_type, 4);
  BOOST_REQUIRE_EQUAL(deserialized->get_header_data().sequence_number, 5);
  BOOST_REQUIRE_EQUAL(deserialized->get_header_data().max_sequence_number, 6);

  BOOST_REQUIRE_EQUAL(deserialized->get_fragments_ref().size(), 2);

  BOOST_REQUIRE_EQUAL(deserialized->get_fragments_ref().at(0)->get_trigger_number(), 1);
  BOOST_REQUIRE_EQUAL(deserialized->get_fragments_ref().at(0)->get_trigger_timestamp(), 2);
  BOOST_REQUIRE_EQUAL(deserialized->get_fragments_ref().at(0)->get_run_number(), 3);
  BOOST_REQUIRE_EQUAL(deserialized->get_fragments_ref().at(1)->get_trigger_number(), 1);
  BOOST_REQUIRE_EQUAL(deserialized->get_fragments_ref().at(1)->get_trigger_timestamp(), 2);
  BOOST_REQUIRE_EQUAL(deserialized->get_fragments_ref().at(1)->get_run_number(), 3);

  BOOST_REQUIRE_EQUAL(
    *(static_cast<uint8_t*>(deserialized->get_fragments_ref().at(0)->get_data()) + 0), // NOLINT(build/unsigned)
    1);                                                                                // NOLINT(build/unsigned)
  BOOST_REQUIRE_EQUAL(
    *(static_cast<uint8_t*>(deserialized->get_fragments_ref().at(0)->get_data()) + 1), // NOLINT(build/unsigned)
    2);                                                                                // NOLINT(build/unsigned)
  BOOST_REQUIRE_EQUAL(
    *(static_cast<uint8_t*>(deserialized->get_fragments_ref().at(0)->get_data()) + 2), // NOLINT(build/unsigned)
    3);                                                                                // NOLINT(build/unsigned)
  BOOST_REQUIRE_EQUAL(
    *(static_cast<uint8_t*>(deserialized->get_fragments_ref().at(0)->get_data()) + 3), // NOLINT(build/unsigned)
    4);                                                                                // NOLINT(build/unsigned)

  BOOST_REQUIRE_EQUAL(
    *(static_cast<uint8_t*>(deserialized->get_fragments_ref().at(1)->get_data()) + 0), // NOLINT(build/unsigned)
    5);                                                                                // NOLINT(build/unsigned)
  BOOST_REQUIRE_EQUAL(
    *(static_cast<uint8_t*>(deserialized->get_fragments_ref().at(1)->get_data()) + 1), // NOLINT(build/unsigned)
    6);                                                                                // NOLINT(build/unsigned)
  BOOST_REQUIRE_EQUAL(
    *(static_cast<uint8_t*>(deserialized->get_fragments_ref().at(1)->get_data()) + 2), // NOLINT(build/unsigned)
    7);                                                                                // NOLINT(build/unsigned)
  BOOST_REQUIRE_EQUAL(
    *(static_cast<uint8_t*>(deserialized->get_fragments_ref().at(1)->get_data()) + 3), // NOLINT(build/unsigned)
    8);                                                                                // NOLINT(build/unsigned)
  BOOST_REQUIRE_EQUAL(
    *(static_cast<uint8_t*>(deserialized->get_fragments_ref().at(1)->get_data()) + 4), // NOLINT(build/unsigned)
    9);                                                                                // NOLINT(build/unsigned)
  BOOST_REQUIRE_EQUAL(
    *(static_cast<uint8_t*>(deserialized->get_fragments_ref().at(1)->get_data()) + 5), // NOLINT(build/unsigned)
    10);                                                                               // NOLINT(build/unsigned
  BOOST_REQUIRE_EQUAL(
    *(static_cast<uint8_t*>(deserialized->get_fragments_ref().at(1)->get_data()) + 6), // NOLINT(build/unsigned)
    11);                                                                               // NOLINT(build/unsigned)
  BOOST_REQUIRE_EQUAL(
    *(static_cast<uint8_t*>(deserialized->get_fragments_ref().at(1)->get_data()) + 7), // NOLINT(build/unsigned)
    12);                                                                               // NOLINT(build/unsigned)
}

BOOST_AUTO_TEST_CASE(SerDes_Ptr_to_TriggerRecord)
{
  // Setup
  std::vector<ComponentRequest> components;
  components.emplace_back();
  components.back().component.subsystem = SourceID::Subsystem::kDetectorReadout;
  components.back().component.id = 2;
  components.back().window_begin = 3;
  components.back().window_end = 4;
  components.emplace_back();
  components.back().component.subsystem = SourceID::Subsystem::kDetectorReadout;
  components.back().component.id = 6;
  components.back().window_begin = 7;
  components.back().window_end = 8;

  TriggerRecordHeader record_header(components);
  record_header.set_trigger_number(1);
  record_header.set_trigger_timestamp(2);
  record_header.set_run_number(3);
  record_header.set_trigger_type(4);
  record_header.set_sequence_number(5);
  record_header.set_max_sequence_number(6);

  auto record = std::make_unique<TriggerRecord>(record_header);

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

  auto another_frag = malloc(sizeof(FragmentHeader) + 8);
  header.size = sizeof(FragmentHeader) + 8;
  memcpy(another_frag, &header, sizeof(FragmentHeader));

  uint8_t five = 5, six = 6, seven = 7, eight = 8;                                      // NOLINT(build/unsigned)
  uint8_t nine = 9, ten = 10, eleven = 11, twelve = 12;                                 // NOLINT(build/unsigned)
  memcpy(static_cast<uint8_t*>(another_frag) + sizeof(FragmentHeader), &five, 1);       // NOLINT(build/unsigned)
  memcpy(static_cast<uint8_t*>(another_frag) + sizeof(FragmentHeader) + 1, &six, 1);    // NOLINT(build/unsigned)
  memcpy(static_cast<uint8_t*>(another_frag) + sizeof(FragmentHeader) + 2, &seven, 1);  // NOLINT(build/unsigned)
  memcpy(static_cast<uint8_t*>(another_frag) + sizeof(FragmentHeader) + 3, &eight, 1);  // NOLINT(build/unsigned)
  memcpy(static_cast<uint8_t*>(another_frag) + sizeof(FragmentHeader) + 4, &nine, 1);   // NOLINT(build/unsigned)
  memcpy(static_cast<uint8_t*>(another_frag) + sizeof(FragmentHeader) + 5, &ten, 1);    // NOLINT(build/unsigned)
  memcpy(static_cast<uint8_t*>(another_frag) + sizeof(FragmentHeader) + 6, &eleven, 1); // NOLINT(build/unsigned)
  memcpy(static_cast<uint8_t*>(another_frag) + sizeof(FragmentHeader) + 7, &twelve, 1); // NOLINT(build/unsigned)

  auto test_frag = std::make_unique<Fragment>(frag, Fragment::BufferAdoptionMode::kTakeOverBuffer);
  auto another_test_frag = std::make_unique<Fragment>(another_frag, Fragment::BufferAdoptionMode::kTakeOverBuffer);

  record->add_fragment(std::move(test_frag));
  record->add_fragment(std::move(another_test_frag));

  // SERIALIZE
  auto bytes = dunedaq::serialization::serialize(record, dunedaq::serialization::kMsgPack);

  // DESERIALIZE
  TriggerRecord deserialized = dunedaq::serialization::deserialize<TriggerRecord>(bytes);

  // TEST
  BOOST_REQUIRE_EQUAL(deserialized.get_header_data().num_requested_components, 2);
  BOOST_REQUIRE_EQUAL(deserialized.get_header_data().trigger_number, 1);
  BOOST_REQUIRE_EQUAL(deserialized.get_header_data().trigger_timestamp, 2);
  BOOST_REQUIRE_EQUAL(deserialized.get_header_data().run_number, 3);
  BOOST_REQUIRE_EQUAL(deserialized.get_header_data().trigger_type, 4);
  BOOST_REQUIRE_EQUAL(deserialized.get_header_data().sequence_number, 5);
  BOOST_REQUIRE_EQUAL(deserialized.get_header_data().max_sequence_number, 6);

  BOOST_REQUIRE_EQUAL(deserialized.get_fragments_ref().size(), 2);

  BOOST_REQUIRE_EQUAL(deserialized.get_fragments_ref().at(0)->get_trigger_number(), 1);
  BOOST_REQUIRE_EQUAL(deserialized.get_fragments_ref().at(0)->get_trigger_timestamp(), 2);
  BOOST_REQUIRE_EQUAL(deserialized.get_fragments_ref().at(0)->get_run_number(), 3);
  BOOST_REQUIRE_EQUAL(deserialized.get_fragments_ref().at(1)->get_trigger_number(), 1);
  BOOST_REQUIRE_EQUAL(deserialized.get_fragments_ref().at(1)->get_trigger_timestamp(), 2);
  BOOST_REQUIRE_EQUAL(deserialized.get_fragments_ref().at(1)->get_run_number(), 3);

  BOOST_REQUIRE_EQUAL(
    *(static_cast<uint8_t*>(deserialized.get_fragments_ref().at(0)->get_data()) + 0), // NOLINT(build/unsigned)
    1);                                                                               // NOLINT(build/unsigned)
  BOOST_REQUIRE_EQUAL(
    *(static_cast<uint8_t*>(deserialized.get_fragments_ref().at(0)->get_data()) + 1), // NOLINT(build/unsigned)
    2);                                                                               // NOLINT(build/unsigned)
  BOOST_REQUIRE_EQUAL(
    *(static_cast<uint8_t*>(deserialized.get_fragments_ref().at(0)->get_data()) + 2), // NOLINT(build/unsigned)
    3);                                                                               // NOLINT(build/unsigned)
  BOOST_REQUIRE_EQUAL(
    *(static_cast<uint8_t*>(deserialized.get_fragments_ref().at(0)->get_data()) + 3), // NOLINT(build/unsigned)
    4);                                                                               // NOLINT(build/unsigned)

  BOOST_REQUIRE_EQUAL(
    *(static_cast<uint8_t*>(deserialized.get_fragments_ref().at(1)->get_data()) + 0), // NOLINT(build/unsigned)
    5);                                                                               // NOLINT(build/unsigned)
  BOOST_REQUIRE_EQUAL(
    *(static_cast<uint8_t*>(deserialized.get_fragments_ref().at(1)->get_data()) + 1), // NOLINT(build/unsigned)
    6);                                                                               // NOLINT(build/unsigned)
  BOOST_REQUIRE_EQUAL(
    *(static_cast<uint8_t*>(deserialized.get_fragments_ref().at(1)->get_data()) + 2), // NOLINT(build/unsigned)
    7);                                                                               // NOLINT(build/unsigned)
  BOOST_REQUIRE_EQUAL(
    *(static_cast<uint8_t*>(deserialized.get_fragments_ref().at(1)->get_data()) + 3), // NOLINT(build/unsigned)
    8);                                                                               // NOLINT(build/unsigned)
  BOOST_REQUIRE_EQUAL(
    *(static_cast<uint8_t*>(deserialized.get_fragments_ref().at(1)->get_data()) + 4), // NOLINT(build/unsigned)
    9);                                                                               // NOLINT(build/unsigned)
  BOOST_REQUIRE_EQUAL(
    *(static_cast<uint8_t*>(deserialized.get_fragments_ref().at(1)->get_data()) + 5), // NOLINT(build/unsigned)
    10);                                                                              // NOLINT(build/unsigned
  BOOST_REQUIRE_EQUAL(
    *(static_cast<uint8_t*>(deserialized.get_fragments_ref().at(1)->get_data()) + 6), // NOLINT(build/unsigned)
    11);                                                                              // NOLINT(build/unsigned)
  BOOST_REQUIRE_EQUAL(
    *(static_cast<uint8_t*>(deserialized.get_fragments_ref().at(1)->get_data()) + 7), // NOLINT(build/unsigned)
    12);                                                                              // NOLINT(build/unsigned)
}

BOOST_AUTO_TEST_CASE(SerDes_TriggerRecord_to_Ptr)
{
  // Setup
  std::vector<ComponentRequest> components;
  components.emplace_back();
  components.back().component.subsystem = SourceID::Subsystem::kDetectorReadout;
  components.back().component.id = 2;
  components.back().window_begin = 3;
  components.back().window_end = 4;
  components.emplace_back();
  components.back().component.subsystem = SourceID::Subsystem::kDetectorReadout;
  components.back().component.id = 6;
  components.back().window_begin = 7;
  components.back().window_end = 8;

  TriggerRecordHeader record_header(components);
  record_header.set_trigger_number(1);
  record_header.set_trigger_timestamp(2);
  record_header.set_run_number(3);
  record_header.set_trigger_type(4);
  record_header.set_sequence_number(5);
  record_header.set_max_sequence_number(6);

  TriggerRecord record(record_header);

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

  auto another_frag = malloc(sizeof(FragmentHeader) + 8);
  header.size = sizeof(FragmentHeader) + 8;
  memcpy(another_frag, &header, sizeof(FragmentHeader));

  uint8_t five = 5, six = 6, seven = 7, eight = 8;                                      // NOLINT(build/unsigned)
  uint8_t nine = 9, ten = 10, eleven = 11, twelve = 12;                                 // NOLINT(build/unsigned)
  memcpy(static_cast<uint8_t*>(another_frag) + sizeof(FragmentHeader), &five, 1);       // NOLINT(build/unsigned)
  memcpy(static_cast<uint8_t*>(another_frag) + sizeof(FragmentHeader) + 1, &six, 1);    // NOLINT(build/unsigned)
  memcpy(static_cast<uint8_t*>(another_frag) + sizeof(FragmentHeader) + 2, &seven, 1);  // NOLINT(build/unsigned)
  memcpy(static_cast<uint8_t*>(another_frag) + sizeof(FragmentHeader) + 3, &eight, 1);  // NOLINT(build/unsigned)
  memcpy(static_cast<uint8_t*>(another_frag) + sizeof(FragmentHeader) + 4, &nine, 1);   // NOLINT(build/unsigned)
  memcpy(static_cast<uint8_t*>(another_frag) + sizeof(FragmentHeader) + 5, &ten, 1);    // NOLINT(build/unsigned)
  memcpy(static_cast<uint8_t*>(another_frag) + sizeof(FragmentHeader) + 6, &eleven, 1); // NOLINT(build/unsigned)
  memcpy(static_cast<uint8_t*>(another_frag) + sizeof(FragmentHeader) + 7, &twelve, 1); // NOLINT(build/unsigned)

  auto test_frag = std::make_unique<Fragment>(frag, Fragment::BufferAdoptionMode::kTakeOverBuffer);
  auto another_test_frag = std::make_unique<Fragment>(another_frag, Fragment::BufferAdoptionMode::kTakeOverBuffer);

  record.add_fragment(std::move(test_frag));
  record.add_fragment(std::move(another_test_frag));

  // SERIALIZE
  auto bytes = dunedaq::serialization::serialize(record, dunedaq::serialization::kMsgPack);

  // DESERIALIZE
  auto deserialized = dunedaq::serialization::deserialize<std::unique_ptr<TriggerRecord>>(bytes);

  // TEST
  BOOST_REQUIRE_EQUAL(deserialized->get_header_data().num_requested_components, 2);
  BOOST_REQUIRE_EQUAL(deserialized->get_header_data().trigger_number, 1);
  BOOST_REQUIRE_EQUAL(deserialized->get_header_data().trigger_timestamp, 2);
  BOOST_REQUIRE_EQUAL(deserialized->get_header_data().run_number, 3);
  BOOST_REQUIRE_EQUAL(deserialized->get_header_data().trigger_type, 4);
  BOOST_REQUIRE_EQUAL(deserialized->get_header_data().sequence_number, 5);
  BOOST_REQUIRE_EQUAL(deserialized->get_header_data().max_sequence_number, 6);

  BOOST_REQUIRE_EQUAL(deserialized->get_fragments_ref().size(), 2);

  BOOST_REQUIRE_EQUAL(deserialized->get_fragments_ref().at(0)->get_trigger_number(), 1);
  BOOST_REQUIRE_EQUAL(deserialized->get_fragments_ref().at(0)->get_trigger_timestamp(), 2);
  BOOST_REQUIRE_EQUAL(deserialized->get_fragments_ref().at(0)->get_run_number(), 3);
  BOOST_REQUIRE_EQUAL(deserialized->get_fragments_ref().at(1)->get_trigger_number(), 1);
  BOOST_REQUIRE_EQUAL(deserialized->get_fragments_ref().at(1)->get_trigger_timestamp(), 2);
  BOOST_REQUIRE_EQUAL(deserialized->get_fragments_ref().at(1)->get_run_number(), 3);

  BOOST_REQUIRE_EQUAL(
    *(static_cast<uint8_t*>(deserialized->get_fragments_ref().at(0)->get_data()) + 0), // NOLINT(build/unsigned)
    1);                                                                                // NOLINT(build/unsigned)
  BOOST_REQUIRE_EQUAL(
    *(static_cast<uint8_t*>(deserialized->get_fragments_ref().at(0)->get_data()) + 1), // NOLINT(build/unsigned)
    2);                                                                                // NOLINT(build/unsigned)
  BOOST_REQUIRE_EQUAL(
    *(static_cast<uint8_t*>(deserialized->get_fragments_ref().at(0)->get_data()) + 2), // NOLINT(build/unsigned)
    3);                                                                                // NOLINT(build/unsigned)
  BOOST_REQUIRE_EQUAL(
    *(static_cast<uint8_t*>(deserialized->get_fragments_ref().at(0)->get_data()) + 3), // NOLINT(build/unsigned)
    4);                                                                                // NOLINT(build/unsigned)

  BOOST_REQUIRE_EQUAL(
    *(static_cast<uint8_t*>(deserialized->get_fragments_ref().at(1)->get_data()) + 0), // NOLINT(build/unsigned)
    5);                                                                                // NOLINT(build/unsigned)
  BOOST_REQUIRE_EQUAL(
    *(static_cast<uint8_t*>(deserialized->get_fragments_ref().at(1)->get_data()) + 1), // NOLINT(build/unsigned)
    6);                                                                                // NOLINT(build/unsigned)
  BOOST_REQUIRE_EQUAL(
    *(static_cast<uint8_t*>(deserialized->get_fragments_ref().at(1)->get_data()) + 2), // NOLINT(build/unsigned)
    7);                                                                                // NOLINT(build/unsigned)
  BOOST_REQUIRE_EQUAL(
    *(static_cast<uint8_t*>(deserialized->get_fragments_ref().at(1)->get_data()) + 3), // NOLINT(build/unsigned)
    8);                                                                                // NOLINT(build/unsigned)
  BOOST_REQUIRE_EQUAL(
    *(static_cast<uint8_t*>(deserialized->get_fragments_ref().at(1)->get_data()) + 4), // NOLINT(build/unsigned)
    9);                                                                                // NOLINT(build/unsigned)
  BOOST_REQUIRE_EQUAL(
    *(static_cast<uint8_t*>(deserialized->get_fragments_ref().at(1)->get_data()) + 5), // NOLINT(build/unsigned)
    10);                                                                               // NOLINT(build/unsigned
  BOOST_REQUIRE_EQUAL(
    *(static_cast<uint8_t*>(deserialized->get_fragments_ref().at(1)->get_data()) + 6), // NOLINT(build/unsigned)
    11);                                                                               // NOLINT(build/unsigned)
  BOOST_REQUIRE_EQUAL(
    *(static_cast<uint8_t*>(deserialized->get_fragments_ref().at(1)->get_data()) + 7), // NOLINT(build/unsigned)
    12);                                                                               // NOLINT(build/unsigned)
}

BOOST_AUTO_TEST_CASE(Bad_JSON)
{
  std::string test_string = "J{ \"test_value\": \"test string\" }";
  std::vector<unsigned char> bytes(test_string.begin(), test_string.end());
  BOOST_REQUIRE_EXCEPTION(dunedaq::serialization::deserialize<TriggerRecord>(bytes),
                          dunedaq::dfmessages::CannotDeserializeTriggerRecord,
                          [&](dunedaq::dfmessages::CannotDeserializeTriggerRecord) { return true; });
  BOOST_REQUIRE_EXCEPTION(dunedaq::serialization::deserialize<std::unique_ptr<TriggerRecord>>(bytes),
                          dunedaq::dfmessages::CannotDeserializeTriggerRecord,
                          [&](dunedaq::dfmessages::CannotDeserializeTriggerRecord) { return true; });

  std::string another_test_string = "J{\"header\": { \"test_value\": \"test string\" }}";
  std::vector<unsigned char> more_bytes(another_test_string.begin(), another_test_string.end());
  BOOST_REQUIRE_EXCEPTION(dunedaq::serialization::deserialize<TriggerRecord>(more_bytes),
                          dunedaq::dfmessages::CannotDeserializeTriggerRecordHeader,
                          [&](dunedaq::dfmessages::CannotDeserializeTriggerRecordHeader) { return true; });

  BOOST_REQUIRE_EXCEPTION(dunedaq::serialization::deserialize<std::unique_ptr<TriggerRecord>>(more_bytes),
                          dunedaq::dfmessages::CannotDeserializeTriggerRecordHeader,
                          [&](dunedaq::dfmessages::CannotDeserializeTriggerRecordHeader) { return true; });
}

BOOST_AUTO_TEST_SUITE_END()
