cmake_minimum_required(VERSION 3.12)
project(dfmessages VERSION 1.0.0)

find_package(daq-cmake REQUIRED)

daq_setup_environment()

find_package(Boost 1.70.0 COMPONENTS unit_test_framework REQUIRED)
find_package(dataformats REQUIRED)

# No sources, so we'll create an INTERFACE library
daq_add_library(LINK_LIBRARIES dataformats::dataformats)

daq_add_unit_test(DataRequest_test LINK_LIBRARIES dataformats::dataformats)
daq_add_unit_test(TimeSync_test LINK_LIBRARIES dataformats::dataformats)
daq_add_unit_test(TriggerDecision_test LINK_LIBRARIES dataformats::dataformats)
daq_add_unit_test(TriggerInhibit_test LINK_LIBRARIES dataformats::dataformats)

daq_install()
