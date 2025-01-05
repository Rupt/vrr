#define VRR_UNSAFE_STRINGIFY_INNER(b) #b
#define VRR_UNSAFE_STRINGIFY(b) VRR_UNSAFE_STRINGIFY_INNER(b)
#define VRR_UNSAFE_LOG __FILE__ ":" VRR_UNSAFE_STRINGIFY(__LINE__) ": "

#define vrr_expected(format) (VRR_UNSAFE_LOG "expected: " format "\n")
#define vrr_observed(format) (VRR_UNSAFE_LOG "observed: " format "\n")
