#include <inttypes.h>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include <x86intrin.h>
#include <stdio.h>

#pragma intrinsic(__rdtsc)

#define MS_IN_SEC 1000 /* milliseconds in second */
#define NSEC_IN_MS 1000000 /* nanoseconds in millisecond */
#define USEC_IN_MS 1000 /* microseconds in millisecond */
#define USEC_IN_NSEC 1000

#define N_TESTS 15
#define MY_PROCESSOR_FREQUENCY 2.1

unsigned long long calc_elapsed_time_ts(const struct timespec *start, const struct timespec *end);
unsigned long long calc_elapsed_time_tv(const struct timeval *start, const struct timeval *end);

int main(void) {
    suseconds_t time_ms[] = {1000, 100, 50, 10};

    printf("`gettimeofday()` testing\n");
    for (size_t i = 0; i < sizeof (time_ms) / sizeof (suseconds_t); ++i)
    {
        unsigned long long time[N_TESTS];
        unsigned long long average = 0;
        for (size_t j = 0; j < N_TESTS; ++j)
        {
            struct timespec req = {time_ms[i] /  MS_IN_SEC, time_ms[i] % MS_IN_SEC * NSEC_IN_MS};
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
                time[j] = calc_elapsed_time_tv(&start, &end);
                average += time[j];
                printf("%ldms: %lluus\n", time_ms[i], time[j]);
            }
        }

        printf("Average time: %lluus\n", average / N_TESTS);
    }


    printf("`clock_gettime()` testing\n");
    for (size_t i = 0; i < sizeof (time_ms) / sizeof (suseconds_t); ++i)
    {
        unsigned long long time[N_TESTS];
        unsigned long long average = 0;
        for (size_t j = 0; j < N_TESTS; ++j)
        {
            struct timespec req = {time_ms[i] /  MS_IN_SEC, time_ms[i] % MS_IN_SEC * NSEC_IN_MS};
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
                time[j] = calc_elapsed_time_ts(&start, &end);
                average += time[j];
                printf("%ldms: %lluus\n", time_ms[i], time[j]);
            }
        }

        printf("Average time: %lluus\n", average / N_TESTS);
    }

    printf("`clock()` testing\n");
    for (size_t i = 0; i < sizeof (time_ms) / sizeof (suseconds_t); ++i)
    {
        double time[N_TESTS];
        double average = 0;
        for (size_t j = 0; j < N_TESTS; ++j)
        {
            struct timespec req = {time_ms[i] /  MS_IN_SEC, time_ms[i] % MS_IN_SEC * NSEC_IN_MS};
            struct timespec rem = {0, 0};
            clock_t start, end;

            start = clock();
            int rc = nanosleep(&req, &rem);
            end = clock();

            if (rc || rem.tv_sec || rem.tv_nsec)
                fprintf(stderr, "Warning: `nanosleep()` have not work properly."
                                "\nTime required: %lds %ldms;\nTime remaining: %lds %ldms\n",
                        req.tv_sec, req.tv_nsec, rem.tv_sec, rem.tv_nsec);
            else {
                time[j] = (double) (end - start) / CLOCKS_PER_SEC;
                average += time[j];
                printf("%ldms: %f\n", time_ms[i], time[j]);
            }
        }

        printf("Average: %f\n", average / N_TESTS);
    }

    printf("`__rdtsc()` testing\n");
    for (size_t i = 0; i < sizeof (time_ms) / sizeof (suseconds_t); ++i)
    {
        unsigned long long time[N_TESTS];
        unsigned long long average = 0;
        for (size_t j = 0; j < N_TESTS; ++j)
        {
            struct timespec req = {time_ms[i] /  MS_IN_SEC, time_ms[i] % MS_IN_SEC * NSEC_IN_MS};
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
                time[j] = (unsigned long long) ((end - start) / CLOCKS_PER_SEC / MY_PROCESSOR_FREQUENCY);
                average += time[j];
                printf("%" PRId64"ms: %llus\n", time_ms[i], time[j]);
            }
        }

        printf("Average: %llus\n", average / N_TESTS);
    }
}

unsigned long long calc_elapsed_time_tv(const struct timeval *start, const struct timeval *end)
{
    return ((unsigned long long) (end->tv_sec - start->tv_sec) * MS_IN_SEC * USEC_IN_MS +
            (end->tv_usec - start->tv_usec));
}

unsigned long long calc_elapsed_time_ts(const struct timespec *start, const struct timespec *end)
{
    return ((unsigned long long) (end->tv_sec - start->tv_sec) * MS_IN_SEC * USEC_IN_MS +
            (end->tv_nsec - start->tv_nsec) / USEC_IN_NSEC);
}