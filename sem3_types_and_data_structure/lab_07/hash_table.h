#ifndef HASH_TABLE_H
#define HASH_TABLE_H
#include <stdio.h>

#define TABLE_SIZE 1000
#define MAX_WORD_LEN 40

typedef struct node_entry node_entry_t;

struct node_entry {
    char key[MAX_WORD_LEN];
    node_entry_t *next;
};

typedef struct list_hash_table {
    node_entry_t **table;
    long long n_compare;
    int n_searches;
    int cur_size;
} list_hash_table_t;

typedef struct arr_hash_table {
    char table[TABLE_SIZE][MAX_WORD_LEN];
    long long n_compare;
    int n_searches;
    int cur_size;
} arr_hash_table_t;

int hash_good(char *key);
int hash(char *key, size_t n);

list_hash_table_t *create_list_hash_table();
void insert_list_hash_table(list_hash_table_t *ht, char *key);
void create_list_hash_table_from_file(FILE *f, list_hash_table_t *ht);
void print_list_hash_table(list_hash_table_t *ht);
void delete_list_hash_table(list_hash_table_t *ht, char *key);
void destroy_list_hash_table(list_hash_table_t **ht);
void restruct_list_hash_table(list_hash_table_t *ht);
char *search_list_hash_table(list_hash_table_t *ht, char *key);

arr_hash_table_t *create_arr_hash_table();
void insert_arr_hash_table(arr_hash_table_t *ht, char *key);
void create_arr_hash_table_from_file(FILE *f, arr_hash_table_t *ht);
void print_arr_hash_table(arr_hash_table_t *ht);
void delete_arr_hash_table(arr_hash_table_t *ht, char *key);
void destroy_arr_hash_table(arr_hash_table_t **ht);
void restruct_arr_hash_table(arr_hash_table_t *ht);
char *search_arr_hash_table(arr_hash_table_t *ht, char *key);

#endif