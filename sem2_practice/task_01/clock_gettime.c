#include <inttypes.h>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>

#define MS_IN_SEC 1000     /* milliseconds in second */
#define NSEC_IN_MS 1000000 /* nanoseconds in millisecond */
#define USEC_IN_MS 1000    /* microseconds in millisecond */
#define USEC_IN_NSEC 1000

#ifndef TIME
#error TIME parameter not found
#endif

unsigned long long calc_elapsed_time_ts(const struct timespec *start, const struct timespec *end);

int main(void) {
    unsigned long long time;
    unsigned long long average = 0;
    struct timespec req = {TIME / MS_IN_SEC, TIME % MS_IN_SEC * NSEC_IN_MS};
    struct timespec rem = {0, 0};
    struct timespec start = {0, 0}, end = {0, 0};

    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    int rc = nanosleep(&req, &rem);
    clock_gettime(CLOCK_MONOTONIC_RAW, &end);

    if (rc || rem.tv_sec || rem.tv_nsec)
        fprintf(stderr, "Warning: `nanosleep()` have not work properly."
                        "\nTime required: %lds %ldms;\nTime remaining: %lds %ldms\n",
                req.tv_sec, req.tv_nsec, rem.tv_sec, rem.tv_nsec);
    else {
        time = calc_elapsed_time_ts(&start, &end);
        average += time;
        printf("%llu\n", time);
    }
}

unsigned long long calc_elapsed_time_ts(const struct timespec *start, const struct timespec *end) {
    return ((unsigned long long) (end->tv_sec - start->tv_sec) * MS_IN_SEC * USEC_IN_MS +
            (end->tv_nsec - start->tv_nsec) / USEC_IN_NSEC);
}