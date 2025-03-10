#ifdef VRR_INCLUDE_GUARD
#undef VRR_INCLUDE_GUARD
#include <stdint.h>  // uint8_t
#endif

#define VRR_UNSTABLE_STRINGIFY_INNER(b) #b
#define VRR_UNSTABLE_STRINGIFY(b) VRR_UNSTABLE_STRINGIFY_INNER(b)
#define VRR_UNSTABLE_LOG __FILE__ ":" VRR_UNSTABLE_STRINGIFY(__LINE__) ": "

#define vrr_expected(format) (VRR_UNSTABLE_LOG "expected: " format "\n")
#define vrr_observed(format) (VRR_UNSTABLE_LOG "observed: " format "\n")

uint64_t vrr_checksum(uint64_t count, uint8_t const* bytes);
