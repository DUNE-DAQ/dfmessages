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
#include <tuple>

namespace dunedaq {
namespace dfmessages {
struct GeoID
{
  uint32_t APANumber;  // NOLINT(build/unsigned)
  uint32_t LinkNumber; // NOLINT(build/unsigned)

  bool operator<(const GeoID& other) const
  {
    return std::tuple(APANumber, LinkNumber) < std::tuple(other.APANumber, other.LinkNumber);
  }
};
} // namespace dfmessages
} // namespace dunedaq

#endif // DFMESSAGES_INCLUDE_DFMESSAGES_GEOID_HPP_
