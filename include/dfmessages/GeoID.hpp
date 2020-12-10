/**
 * @file GeoID.hpp Geometric Identification for a link
 *
 * This is part of the DUNE DAQ Application Framework, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#ifndef DFMESSAGES_INCLUDE_DFMESSAGES_GEOID_HPP_
#define DFMESSAGES_INCLUDE_DFMESSAGES_GEOID_HPP_

#include <cstdint>

namespace dunedaq {
namespace dfmessages {
struct GeoID
{
  uint32_t APANumber;  // NOLINT(build/unsigned)
  uint32_t LinkNumber; // NOLINT(build/unsigned)
};
} // namespace dfmessages
} // namespace dunedaq

#endif // DFMESSAGES_INCLUDE_DFMESSAGES_GEOID_HPP_