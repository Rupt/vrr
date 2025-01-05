// <stdio.h>: printf

#define vrr_log_open() \
    printf("{\"file\": \"%s\", \"line\": \"%d\"", __FILE__, __LINE__)
#define vrr_log_expected(format, ...) \
    printf((", \"expected\": " format "\""), __VA_ARGS__)
#define vrr_log_observed(format, ...) \
    printf((", \"observed\": " format "\""), __VA_ARGS__)
#define vrr_log_close() printf("}\n")
