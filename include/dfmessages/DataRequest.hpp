
#include "Common.hpp"

#include <vector>

namespace dunedaq {
namespace dfmessages {
struct DataRequest
{
  enum class mode_t : int
  {
	  LocalizedReadout,
	  ExtendedReadout
  };

  request_number_t RequestNumber;
  trigger_number_t TriggerNumber;
  run_number_t RunNumber;

  timestamp_t TriggerTimestamp;
  timestamp_diff_t WindowOffset;
  timestamp_t WindowWidth;

  mode_t RequestMode;
};

} // namespace dfmessages
} // namespace dunedaq