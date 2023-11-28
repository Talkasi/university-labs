#ifndef DB_H
#define DB_H
#include <stdio.h>
#include <sys/time.h>
#include <time.h>

#define MAX_STR_LEN 1024
#define MAX_NRECORDS 1024

#define ADDRESS 0
#define AREA 1
#define N_ROOMS 2
#define COST_PER_SQUARE 3
#define HOUSING_TYPE 4
#define DECORATION 5
#define YEAR 6
#define N_PREV_OWNERS 7
#define ANIMALS 8

#define MAX_ADDRESS_LEN 50
#define MAX_AREA 999999
#define MAX_NROOMS 20
#define MAX_COST 10000000
#define MAX_YEAR 2023
#define MAX_N_PREV_OWNERS 99

#define WRONG_FLAT_LEN 100
#define WRONG_RECORD 101
#define ERR_OVERFLOW 102
#define FGETS_ZERO 103

struct flat {
	char address[MAX_ADDRESS_LEN];
	int area;
	char n_rooms;
	long cost_per_square;
	char housing_type;
	union housing_t {
		struct secondary_t {
			int year;
			char n_prev_owners;
			char animals;
		} secondary;
		char decoration;
	} housing;
};

struct key_helper {
	int n;
	long cost;
};

typedef struct flat flat_t;
typedef struct key_helper fkey_t;

void buble_sort_f(flat_t flats[], int n_flats);
void insertion_sort_f(flat_t flats[], int n_flats);
void buble_sort_k(fkey_t keys[], int n_keys);
void insertion_sort_k(fkey_t keys[], int n_keys);

int read_db_line(FILE *db, flat_t *flat);
int flat_parsing(char *record, flat_t *flat);
int add_record(flat_t flats[], int *n_flats, flat_t *flat);
void del_key(fkey_t keys[], int n_keys, int del_n);
void del_record(flat_t flats[], int *n_flats, int del_n);
int read_db(FILE *db, flat_t flats[], fkey_t keys[], int *n_records);
void save_db(FILE *db, flat_t flats[], int n_flats);

void print_keys(fkey_t keys[], int n_keys);
void print_db(flat_t flats[], int n_records);
void print_db_header();
void print_db_footer();
void print_db_record(flat_t *flat, int record_n);
void print_special(flat_t flats[], int n_records, long min, long max);
void print_flats_by_key(flat_t flats[], fkey_t keys[], int n_flats);
void print_t_efficiency(unsigned long long kb, unsigned long long ki, unsigned long long fb, unsigned long long fi);
void print_m_efficiency(unsigned long long kb, unsigned long long ki, unsigned long long fb, unsigned long long fi);
void print_p_efficiency(unsigned long long best, unsigned long long worst);
void read_flat(flat_t *flat);
int read_line(FILE *f, char *s, int max);
int read_long(long *number, long border);
int read_char(char *c);

unsigned long long current_time();

#endif