#include "queue.h"
#include <stdio.h>
#include <string.h>

int	main(void)
{
	machine_t a1;
	machine_t a2;

	memset(&a1, 0, sizeof(a1));
	memset(&a2, 0, sizeof(a2));

	a1.q.n_requests = MAX_QUEUE_SIZE;

	a1.time_min = 0;
	a1.time_max = 6;

	a2.time_min = 1;
	a2.time_max = 8;

	process(&a1, &a2);

	return 0;
}


