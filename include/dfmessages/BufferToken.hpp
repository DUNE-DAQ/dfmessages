/**
 * @file dfmessages/BufferToken.hpp BufferToken Message Declaration
 *
 * This is part of the DUNE DAQ Application Framework, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#ifndef DFMESSAGES_INCLUDE_DFMESSAGES_BUFFERTOKEN_HPP_
#define DFMESSAGES_INCLUDE_DFMESSAGES_BUFFERTOKEN_HPP_

#include "dfmessages/Types.hpp"

#include "serialization/Serialization.hpp"

namespace dunedaq {
namespace dfmessages {
/**
 * @brief Represents a message indicating that the DataFlow has one additional buffer available
 */
struct BufferToken
{
  /**
   * @brief Magic bytes to identify a BufferToken entry in a raw data stream
   */
  static constexpr uint32_t s_buffer_token_magic = 0xBBBB7777; // NOLINT(build/unsigned)

  /**
   * @brief Magic Bytes used to identify BufferToken in a raw data stream
   */
  uint32_t buffer_token_marker = s_buffer_token_magic; // NOLINT(build/unsigned)

  run_number_t run_number; ///< The run number that this token corresponds to

  DUNE_DAQ_SERIALIZE(BufferToken, buffer_token_marker, run_number);
};
} // namespace dfmessages
} // namespace dunedaq

#endif // DFMESSAGES_INCLUDE_DFMESSAGES_BUFFERTOKEN_HPP_
