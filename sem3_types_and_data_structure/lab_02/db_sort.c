#include <stdio.h>
#include "db.h"

void print_special(flat_t flats[], int n_records, long min, long max)
{
	int	n_found = 0;
	for (int i = 0; i < n_records; ++i)
		if (flats[i].n_rooms == 2 &&
		    flats[i].cost_per_square >= min && flats[i].cost_per_square <= max &&
		    flats[i].housing_type == 2 && flats[i].housing.secondary.animals == 0) {
			if (n_found == 0)
				print_db_header();
			print_db_record(&flats[i], i + 1);
			++n_found;
		}

	if (n_found == 0)
		printf("No flats were found\n");
	else
		print_db_footer();
}


long	sort_condition_f(flat_t *f1, flat_t *f2)
{
	return (f1->cost_per_square - f2->cost_per_square);
}


void buble_sort_f(flat_t flats[], int n_flats)
{
	flat_t tmp;
	for (int i = 0; i < n_flats; ++i)
		for (int j = 0; j < i; ++j)
			if (flats[i].cost_per_square < flats[j].cost_per_square) {
				tmp = flats[i];
				flats[i] = flats[j];
				flats[j] = tmp;
			}
}


void insertion_sort_f(flat_t flats[], int n_flats)
{
	int	i, j;
	flat_t key;
	for (i = 1; i < n_flats; i++) {
		key = flats[i];
		j = i - 1;

		while (j >= 0 && sort_condition_f(&flats[j], &key) > 0) {
			flats[j + 1] = flats[j];
			j = j - 1;
		}
		flats[j + 1] = key;
	}
}


long	sort_condition_k(fkey_t *k1, fkey_t *k2)
{
	return (k1->cost - k2->cost);
}


void buble_sort_k(fkey_t keys[], int n_keys)
{
	fkey_t tmp;
	for (int i = 0; i < n_keys; ++i)
		for (int j = 0; j < i; ++j)
			if (keys[i].cost < keys[j].cost) {
				tmp = keys[i];
				keys[i] = keys[j];
				keys[j] = tmp;
			}
}


void insertion_sort_k(fkey_t keys[], int n_keys)
{
	int	i, j;
	fkey_t key;
	for (i = 1; i < n_keys; i++) {
		key = keys[i];
		j = i - 1;

		while (j >= 0 && sort_condition_k(&keys[j], &key) > 0) {
			keys[j + 1] = keys[j];
			j = j - 1;
		}
		keys[j + 1] = key;
	}
}


unsigned long long	current_time()
{
	struct timespec ts;
	clockid_t clkid;
	clkid = CLOCK_REALTIME;
	clock_gettime(clkid, &ts);

	return ts.tv_sec * 1000000000 + ts.tv_nsec;
}


