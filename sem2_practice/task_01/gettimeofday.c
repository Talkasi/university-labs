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

unsigned long long calc_elapsed_time_tv(const struct timeval *start, const struct timeval *end);

int main(void) {
    unsigned long long time;
    unsigned long long average = 0;
    struct timespec req = {TIME / MS_IN_SEC, TIME % MS_IN_SEC * NSEC_IN_MS};
    struct timespec rem = {0, 0};
    struct timeval start = {0, 0}, end = {0, 0};

    gettimeofday(&start, 0);
    int rc = nanosleep(&req, &rem);
    gettimeofday(&end, 0);

    if (rc || rem.tv_sec || rem.tv_nsec)
        fprintf(stderr, "Warning: `nanosleep()` have not work properly."
                        "\nTime required: %lds %ldms;\nTime remaining: %lds %ldms\n",
                req.tv_sec, req.tv_nsec, rem.tv_sec, rem.tv_nsec);
    else {
        time = calc_elapsed_time_tv(&start, &end);
        average += time;
        printf("%llu\n", time);
    }
}

unsigned long long calc_elapsed_time_tv(const struct timeval *start, const struct timeval *end) {
    return ((unsigned long long) (end->tv_sec - start->tv_sec) * MS_IN_SEC * USEC_IN_MS +
            (end->tv_usec - start->tv_usec));
}
