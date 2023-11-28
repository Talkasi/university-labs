#include "db.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

long	checks_uint_type(char *s, long bound);
char	checks_bool(char *s, char v1, char v2);
char	*my_strtok(char *s, char sep, int *my_errno);
void print_db_record(flat_t *flat, int n_record);

int	flat_parsing(char *record, flat_t *flat)
{
	char	*token;
	int	token_n = 0;
	int	my_errno = 0;
	token = my_strtok(record, ',', &my_errno);
	while (token != NULL) {
		if (token_n > DECORATION && flat->housing_type == 1)
			return WRONG_RECORD;

		switch (token_n) {
		case (ADDRESS)
:
				if (strlen(token) <= MAX_ADDRESS_LEN)
					strcpy(flat->address, token);
				else
					return WRONG_RECORD;
			break;
		case (AREA)
:
				flat->area = (int) checks_uint_type(token, MAX_AREA);
			if (flat->area == -1)
				return WRONG_RECORD;
			break;
		case (N_ROOMS)
:
				flat->n_rooms = (char) checks_uint_type(token, MAX_NROOMS);
			if (flat->n_rooms == -1)
				return WRONG_RECORD;
			break;
		case (COST_PER_SQUARE)
:
				flat->cost_per_square = checks_uint_type(token, MAX_COST);
			if (flat->cost_per_square == -1)
				return WRONG_RECORD;
			break;
		case (HOUSING_TYPE)
:
				flat->housing_type = checks_bool(token, '1', '2');
			if (flat->housing_type == -1)
				return WRONG_RECORD;
			if (flat->housing_type == 2)
				++token_n;
			break;
		case (DECORATION)
:
				flat->housing.decoration = checks_bool(token, '0', '1');
			if (flat->housing.decoration == -1)
				return WRONG_RECORD;
			break;
		case (YEAR)
:
				flat->housing.secondary.year = checks_uint_type(token, MAX_YEAR);
			if (flat->housing.secondary.year == -1)
				return WRONG_RECORD;
			break;
		case (N_PREV_OWNERS)
:
				flat->housing.secondary.n_prev_owners = checks_uint_type(token, MAX_N_PREV_OWNERS);
			if (flat->housing.secondary.n_prev_owners == -1)
				return WRONG_RECORD;
			break;
		case (ANIMALS)
:
				flat->housing.secondary.animals = checks_bool(token, '0', '1');
			if (flat->housing.secondary.animals == -1)
				return WRONG_RECORD;
			break;
		default:
			return WRONG_RECORD;
			break;
		}

		token = my_strtok(NULL, ',', &my_errno);
		++token_n;
	}

	if (my_errno)
		return WRONG_RECORD;

	return 0;
}


int	read_db_line(FILE *db, flat_t *flat)
{
	char	record[MAX_STR_LEN + 1];
	char	*tmp  = fgets(record, MAX_STR_LEN + 1, db);
	if (tmp == NULL)
		return FGETS_ZERO;

	size_t record_len = strlen(record);
	if (record[record_len - 1] == '\n')
		record[--record_len] = '\0';

	if (flat_parsing(record, flat) != 0)
		return WRONG_RECORD;

	return 0;
}


char	*my_strtok(char *s, char sep, int *my_errno)
{
	*my_errno = 0;
	static char	*cur;
	if (s == NULL)
		s = cur;
	if (*s == '\0')
		return NULL;
	if (s == NULL || *s == sep) {
		*my_errno = 1;
		return NULL;
	}

	char	*ret = s;
	while (*s != sep) {
		++s;
		if (*s == '\0') {
			*my_errno = 1;
			return NULL;
		}
	}
	*s = '\0';
	cur = ++s;
	return ret;
}


long	checks_uint_type(char *s, long bound)
{
	char	*endptr;
	long	tmp = strtol(s, &endptr, 10);
	if (*endptr != '\0' || tmp <= 0 || tmp > bound)
		return - 1;
	return tmp;
}


char	checks_bool(char *s, char v1, char v2)
{
	if (strlen(s) == 1) {
		if (s[0] == v1)
			return v1 - '0';
		else if (s[0] == v2)
			return v2 - '0';
		else
			return - 1;
	}
	return - 1;
}


int	add_record(flat_t flats[], int *n_flats, flat_t *flat)
{
	if (*n_flats + 1 > MAX_NRECORDS)
		return ERR_OVERFLOW;

	flats[*n_flats] = *flat;
	++ * n_flats;
	return 0;
}


void del_record(flat_t flats[], int *n_flats, int del_n)
{
	for (int i = del_n; i < *n_flats - 1; ++i)
		flats[i] = flats[i + 1];
	-- * n_flats;
}


int	read_db(FILE *db, flat_t flats[], fkey_t keys[], int *n_records)
{
	rewind(db);

	int	rc;
	*n_records = 0;

	while ((rc = read_db_line(db, &flats[*n_records])) == 0) {
		keys[*n_records].n = *n_records + 1;
		keys[*n_records].cost = flats[*n_records].cost_per_square;
		++ * n_records;
		if (*n_records + 1 > MAX_NRECORDS)
			return ERR_OVERFLOW;
	}

	if (rc != FGETS_ZERO) {
		print_db_record(&flats[*n_records], *n_records);
		return WRONG_RECORD;
	}
	return 0;
}


void save_db(FILE *db, flat_t flats[], int n_flats)
{
	rewind(db);
	for (int i = 0; i < n_flats; ++i) {
		if (flats[i].housing_type == 1)
			fprintf(db, "%s,%d,%d,%ld,%d,%d,\n", flats[i].address, flats[i].area, flats[i].n_rooms,
			    flats[i].cost_per_square, flats[i].housing_type,
			    flats[i].housing.decoration);
		else
			fprintf(db, "%s,%d,%d,%ld,%d,%d,%d,%d,\n", flats[i].address, flats[i].area, flats[i].n_rooms,
			    flats[i].cost_per_square, flats[i].housing_type,
			    flats[i].housing.secondary.year,
			    flats[i].housing.secondary.n_prev_owners,
			    flats[i].housing.secondary.animals);
	}
}


void print_db_header()
{
	printf("┌──────┬────────────────────────────────────────────────────┬────────┬──────────┬─────────────────┬──────────────┬────────────┬──────┬─────────┬─────────┐\n"
	    "│ Numb │                     Address                        │  Area  │ Rooms n. │ Cost per square │ Housing type │ Decoration │ Year │ N. owns │ Animals │\n"
	    "├──────┼────────────────────────────────────────────────────┼────────┼──────────┼─────────────────┼──────────────┼────────────┼──────┼─────────┼─────────┤\n");

}


void print_db_record(flat_t *flat, int n_record)
{
	printf("│ %4d ", n_record);
	printf("│ %-50s │ %6d │ %8d │ %12ld p. │ %-12s │", flat->address, flat->area, flat->n_rooms, flat->cost_per_square, flat->housing_type == 1 ? "Primary" : "Secondary");
	if (flat->housing_type == 1)
		printf(" %-10s │ %6s │ %9s │ %-9s │\n", flat->housing.decoration == 0 ? "No" : "Yes", "—", "—", "—");
	else
		printf(" %-12s │ %4d │ %7d │ %-7s │\n", "—", flat->housing.secondary.year, flat->housing.secondary.n_prev_owners, flat->housing.secondary.animals == 0 ? "No" : "Yes");
}


void print_db_footer()
{
	printf("└──────┴────────────────────────────────────────────────────┴────────┴──────────┴─────────────────┴──────────────┴────────────┴──────┴─────────┴─────────┘\n");
}


void print_db(flat_t flats[], int n_flats)
{
	print_db_header();

	for (int i = 0; i < n_flats; ++i)
		print_db_record(&flats[i], i + 1);

	print_db_footer();
}


void print_keys(fkey_t keys[], int n_keys)
{
	printf("┌────────────┬───────────────────┬─────────────────┐\n"
	    "│ Key Number │ Number in main db │ Cost per square │\n"
	    "├────────────┼───────────────────┼─────────────────┤\n");
	for (int i = 0; i < n_keys; ++i)
		printf("│ %10d │ %17d │ %12ld p. │\n", i + 1, keys[i].n, keys[i].cost);

	printf("└────────────┴───────────────────┴─────────────────┘\n");
}


void print_t_efficiency(unsigned long long kb, unsigned long long ki, unsigned long long fb, unsigned long long fi)
{
	printf("┌───────────────┬────────────────────┬────────────────────┐\n"
	    "│ Table type    │ Average time       │ Average time       │\n"
	    "│               │ Bubble sort        │ Insertion sort     │\n"
	    "├───────────────┼────────────────────┼────────────────────┤\n");
	printf("│ Key table     │ %13llu nsec │ %13llu nsec │\n", kb, ki);
	printf("│ Main database │ %13llu nsec │ %13llu nsec │\n", fb, fi);
	printf("└───────────────┴────────────────────┴────────────────────┘\n");
}


void print_m_efficiency(unsigned long long kb, unsigned long long ki, unsigned long long fb, unsigned long long fi)
{
	printf("┌───────────────┬────────────────────┬────────────────────┐\n"
	    "│ Table type    │ Memory used        │ Memory used        │\n"
	    "│               │ Bubble sort        │ Insertion sort     │\n"
	    "├───────────────┼────────────────────┼────────────────────┤\n");
	printf("│ Key table     │ %12lld bytes │ %12lld bytes │\n", kb, ki);
	printf("│ Main database │ %12lld bytes │ %12lld bytes │\n", fb, fi);
	printf("└───────────────┴────────────────────┴────────────────────┘\n");
}


void print_p_efficiency(unsigned long long best, unsigned long long worst)
{
	printf("┌───────────────┬───────────────────┐\n"
	    "│ Table type    │ Time efficiency   │\n"
	    "├───────────────┼───────────────────┤\n");
	printf("│ Key table     │ %15lld \% │\n", best * 100 / worst);
	printf("│ Main database │ %15lld \% │\n", 100);
	printf("└───────────────┴───────────────────┘\n");
}


void print_flats_by_key(flat_t flats[], fkey_t keys[], int n_flats)
{
	print_db_header();

	for (int i = 0; i < n_flats; ++i)
		print_db_record(&flats[keys[i].n - 1], i + 1);

	print_db_footer();
}


int	read_line(FILE *f, char *s, int bound)
{
	char	tmp[MAX_STR_LEN];
	if (fgets(tmp, MAX_STR_LEN, f) == NULL)
		return - 1;

	int	len_tmp = strlen(tmp);
	if (tmp[len_tmp - 1] == '\n')
		tmp[--len_tmp] = '\0';

	if (len_tmp  + 1 > bound)
		return - 1;

	strcpy(s, tmp);
	return len_tmp;
}


#define MAX_LONG_LEN 21
int	read_long(long *number, long border)
{
	char	tmp[MAX_LONG_LEN];
	if (fgets(tmp, MAX_LONG_LEN, stdin) == NULL)
		return - 1;

	int	len_tmp = strlen(tmp);
	if (tmp[len_tmp - 1] == '\n')
		tmp[--len_tmp] = '\0';
	else {
		while (getchar() != '\n')
			;
		return - 1;
	}

	if (len_tmp == 0 || !isdigit(tmp[0]))
		return - 1;

	char	*endptr;
	long	tmp_l;
	tmp_l = strtol(tmp, &endptr, 10);
	if (*endptr != '\0')
		return - 1;

	if (tmp_l > border)
		return - 1;

	*number = tmp_l;
	return 0;
}


int	read_char(char *c)
{
	char	tmp[3];
	if (fgets(tmp, 3, stdin) == NULL)
		return - 1;

	int	len_tmp = strlen(tmp);
	if (tmp[0] == '\n') {
		*c = '\n';
		return 0;
	}

	if (tmp[len_tmp  - 1] == '\n')
		tmp[--len_tmp] = '\0';
	else {
		while (getchar() != '\n')
			;
		return - 1;
	}

	if (len_tmp != 1)
		return - 1;

	*c = tmp[0];
	return 0;
}


void read_flat_long(char *name, char *prepos, long *number, long bound)
{
	while (1) {
		printf("Enter %s %s a new flat in boundaries [1, %ld]: ", name, prepos, bound);
		if (read_long(number, bound) < 0 || *number <= 0)
			printf("Wrong %s. It must be an integer bigger than 0 and less than %ld. Try again.\n",  name, bound + 1);
		else
			break;
	}
}


void read_flat(flat_t *flat)
{
	int	rc;
	while (1) {
		printf("Enter address of a new flat with length boundaries [1; %d], without `,`: ", MAX_ADDRESS_LEN);
		if ((rc = read_line(stdin, flat->address, MAX_ADDRESS_LEN)) <= 0)
			printf("Wrong address. It must be a non-empty string with less than %d characters. Try again.\n", MAX_ADDRESS_LEN + 1);
		else {
			rc = 1;
			for (int i = 0; i < strlen(flat->address); ++i)
				if (flat->address[i] == ',') {
					rc = 0;
					printf("Wrong address. ',' character is forbidden. Try again.\n");
				}

			if (rc)
				break;
		}
	}
	long	tmp_l;

	read_flat_long("area", "of", &tmp_l, MAX_AREA);
	flat->area = (int) tmp_l;
	read_flat_long("number of rooms",  "in", &tmp_l, MAX_NROOMS);
	flat->n_rooms = (char) tmp_l;
	read_flat_long("cost per square", "for", &flat->cost_per_square, MAX_COST);

	while (1) {
		printf("Enter housing type of the new flat, %c for primary or %c for secondary: ", '1', '2');
		if (read_char(&flat->housing_type) < 0 || (flat->housing_type != '1' && flat->housing_type != '2'))
			printf("Wrong housing type. It must be %c for primary, %c for secondary, nothing else. Try again.\n", '1', '2');
		else {
			flat->housing_type -= '0';
			break;
		}
	}

	char	prompt;
	if (flat->housing_type == 1) {
		while (1) {
			printf("Is flat finished? [y/n]: ");
			if (read_char(&prompt) < 0  || (prompt != 'n' && prompt != 'N' && prompt != 'y' && prompt != 'Y'))
				printf("Wrong answer. Enter `y` for yes or `n` for no. Try again.\n");
			else {
				flat->housing.decoration = (prompt == 'n' || prompt == 'N') ? 0 : 1;
				break;
			}
		}
	} else {
		read_flat_long("year", "of", &tmp_l, MAX_YEAR);
		flat->housing.secondary.year = (int) tmp_l;
		read_flat_long("number of previous owners", "of", &tmp_l, MAX_N_PREV_OWNERS);
		flat->housing.secondary.n_prev_owners = tmp_l;

		while (1) {
			printf("Were there animals in this flat? [y/n]: ");
			if (read_char(&prompt) < 0 || (prompt != 'n' && prompt != 'N' && prompt != 'y' && prompt != 'Y'))
				printf("Wrong answer. Enter `y` for yes or `n` for no. Try again.\n");
			else {
				flat->housing.secondary.animals = (prompt == 'n' || prompt == 'N') ? 0 : 1;
				break;
			}
		}
	}
}


void del_key(fkey_t keys[], int n_keys, int del_n)
{
	for (int i = 0; i < n_keys; ++i)
		if (keys[i].n == del_n) {
			for (int j = i; j < n_keys - 1; ++j)
				keys[j] = keys[j + 1];
			break;
		}
}


