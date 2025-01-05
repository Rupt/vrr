#define VRR_UNSAFE_STRING_INNER(b) #b
#define VRR_UNSAFE_STRING(b) VRR_UNSAFE_STRING_INNER(b)
#define vrr_unsafe_log(text) __FILE__ ":" VRR_UNSAFE_STRING(__LINE__) ": " text

#define vrr_expected(format) (vrr_unsafe_log("expected: ") format "\n")
#define vrr_observed(format) (vrr_unsafe_log("observed: ") format "\n")
