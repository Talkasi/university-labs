#include <inttypes.h>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>

#define MS_IN_SEC 1000     /* milliseconds in second */
#define NSEC_IN_MS 1000000 /* nanoseconds in millisecond */

#ifndef TIME
#error TIME parameter not found
#endif

int main(void) {
    double time;
    double average = 0;
    struct timespec req = {TIME / MS_IN_SEC, TIME % MS_IN_SEC * NSEC_IN_MS};
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
        time = (double) (end - start) / CLOCKS_PER_SEC;
        average += time;
        printf("%f\n", time);
    }
}
