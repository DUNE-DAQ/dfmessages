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
  run_number_t run_number; ///< The run number that this token corresponds to
  request_number_t sequence_number; ///< A sequence number for tokens sent by this process

  DUNE_DAQ_SERIALIZE(BufferToken, run_number, sequence_number);
};
} // namespace dfmessages
} // namespace dunedaq

#endif // DFMESSAGES_INCLUDE_DFMESSAGES_BUFFERTOKEN_HPP_
