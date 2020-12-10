
#include <cstdint>
#include <map>
#include <sys/time.h>
#include <utility>

namespace dunedaq {
namespace dfmessages {
using trigger_number_t = uint64_t;
using request_number_t = uint64_t;
using timestamp_t = uint64_t;
using timestamp_diff_t = int64_t;
using type_t = unsigned;
using run_number_t = uint32_t;
using roi_t = std::pair<timestamp_t, timestamp_t>;
using trigger_type_t = uint32_t;
using error_flags_t = uint32_t;
using geoID_t = std::pair<size_t, size_t>;
using component_request_t = std::tuple<timestamp_t, timestamp_t, timestamp_diff_t>;
using component_request_map_t = std::map<geoID_t, component_request_t>;
using system_time_t = uint64_t;

system_time_t
gettimeofday_us()
{
  struct timeval tv;
  gettimeofday(&tv, nullptr);
  return static_cast<system_time_t>(tv.tv_sec) * 1000000 + tv.tv_usec;
}
} // namespace dfmessages
} // namespace dunedaq