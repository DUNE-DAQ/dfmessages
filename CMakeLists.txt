cmake_minimum_required(VERSION 3.12)
project(dfmessages VERSION 1.0.0)

find_package(daq-cmake REQUIRED)

daq_setup_environment()

find_package(Boost 1.70.0 COMPONENTS unit_test_framework REQUIRED)
find_package(dataformats REQUIRED)
find_package(serialization REQUIRED)
find_package(nwqueueadapters REQUIRED)

# No sources, so we'll create an INTERFACE library
daq_add_library(LINK_LIBRARIES dataformats::dataformats)

daq_add_unit_test(DataRequest_test LINK_LIBRARIES dataformats::dataformats serialization::serialization)
daq_add_unit_test(TimeSync_test LINK_LIBRARIES dataformats::dataformats serialization::serialization)
daq_add_unit_test(TriggerDecision_test LINK_LIBRARIES dataformats::dataformats serialization::serialization)
daq_add_unit_test(TriggerDecisionToken_test LINK_LIBRARIES dataformats::dataformats serialization::serialization)
daq_add_unit_test(TriggerInhibit_test LINK_LIBRARIES dataformats::dataformats serialization::serialization)

# Plugins to make types nwqueueadapters-able
daq_add_plugin(TimeSyncNQ             duneNetworkQueue LINK_LIBRARIES dfmessages nwqueueadapters::nwqueueadapters)
daq_add_plugin(TriggerDecisionNQ      duneNetworkQueue LINK_LIBRARIES dfmessages nwqueueadapters::nwqueueadapters)
daq_add_plugin(TriggerDecisionTokenNQ duneNetworkQueue LINK_LIBRARIES dfmessages nwqueueadapters::nwqueueadapters)
daq_add_plugin(TriggerInhibitNQ       duneNetworkQueue LINK_LIBRARIES dfmessages nwqueueadapters::nwqueueadapters)
daq_add_plugin(DataRequestNQ          duneNetworkQueue LINK_LIBRARIES dfmessages nwqueueadapters::nwqueueadapters)

daq_install()
