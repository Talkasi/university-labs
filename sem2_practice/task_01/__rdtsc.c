#include <inttypes.h>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include <x86intrin.h>

#define MS_IN_SEC 1000     /* milliseconds in second */
#define NSEC_IN_MS 1000000 /* nanoseconds in millisecond */

#define MY_PROCESSOR_FREQUENCY 2.1

#ifndef TIME
#error TIME parameter not found
#endif

int main(void) {
    unsigned long long time;
    unsigned long long average = 0;
    struct timespec req = {TIME / MS_IN_SEC, TIME % MS_IN_SEC * NSEC_IN_MS};
    struct timespec rem = {0, 0};
    uint64_t start, end;

    start = __rdtsc();
    int rc = nanosleep(&req, &rem);
    end = __rdtsc();

    if (rc || rem.tv_sec || rem.tv_nsec)
        fprintf(stderr, "Warning: `nanosleep()` have not work properly."
                        "\nTime required: %lds %ldms;\nTime remaining: %lds %ldms\n",
                req.tv_sec, req.tv_nsec, rem.tv_sec, rem.tv_nsec);
    else {
        time = (unsigned long long) ((end - start) / CLOCKS_PER_SEC / MY_PROCESSOR_FREQUENCY);
        average += time;
        printf("%llu\n", time);
    }
}