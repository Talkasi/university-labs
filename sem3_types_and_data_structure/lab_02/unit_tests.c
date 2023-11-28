#include <stdio.h>
#include "db.h"
#define NTESTS 13
int main() {
	/* flat_parsing testing */
	// TODO(Talkasi): add more tests
	char in[NTESTS][30] = {"addr,12,12,12,1,1,", "q,1,20,1231,2,2010,1,1,", ",1,20,1231,2,2010,1,1,",
			   "q,,20,1231,2,2010,1,1,", "q,1,,1231,2,2010,1,1,",  "q,1,20,,2,2010,1,1,",
			   "q,1,20,1231,,2010,1,1,", "q,1,20,1231,2,,1,1,",  "q,1,20,1231,2,2010,,1,",
			   "q,1,20,1231,2,2010,1,,", "add, -1,1,1,1,1,", "add, 1, -1, 1, 1, 1,", "add, 1, 1, -1, 1, 1,"};
	int out[] = {0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

	for (int i = 0; i < NTESTS; ++i) {
		flat_t flat;
		int rc = flat_parsing(in[i], &flat);
		printf("TEST_%c%c: ", i + 1 < 9 ? '0' : (i + 1)/10 + '0', (i + 1)%10 + '0');
		if (rc == 0 && out[i] == 0)
			printf("PASSED\n");
		else if (rc != 0 && out[i] != 0)
			printf("PASSED\n");
		else
			printf("FAILED\t\tIn: %s;\n", in[i]);
	}

	/* add_record testing */
	flat_t flats[NTESTS] = {{"addr", 64, 2, 150000, 1, {1}}, {"asd", 23, 1, 89898, 2, {2018, 3, 0}}};
	flat_t new = {"Bauman street, house 1", 30, 1, 300000, 2, {2008, 2, 1}};
	int n = 2;
	add_record(flats, &n, &new);
	add_record(flats, &n, &new);
	add_record(flats, &n, &new);
	add_record(flats, &n, &new);
	if (n == 6)
		printf("PASSED\n");
	else
		printf("FAILED\n");


	/* del_record testing */
}