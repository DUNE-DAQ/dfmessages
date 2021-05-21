/**
 * @file plugins/FragmentNQ.cpp Fragment Network Queue Definition
 *
 * This is part of the DUNE DAQ Application Framework, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#include "dfmessages/Fragment_serialization.hpp"
#include "nwqueueadapters/AdapterMacros.hpp"

#include <memory>

DEFINE_DUNE_NWQUEUEADAPTERS(std::unique_ptr<dunedaq::dataformats::Fragment>)
