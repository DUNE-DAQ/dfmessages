/**
 * @file plugins/TRMonRequestNQ.cpp TRMonRequest Network Queue Definition
 *
 * This is part of the DUNE DAQ Application Framework, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#include "dfmessages/TRMonRequest.hpp"
#include "nwqueueadapters/AdapterMacros.hpp"

DEFINE_DUNE_NWQUEUEADAPTERS(dunedaq::dfmessages::TRMonRequest)
