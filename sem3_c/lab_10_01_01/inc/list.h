#ifndef LIST_H
#define LIST_H
#include <stdio.h>

enum err
{
    CAR_ERR = -10,
    NO_CAR_ERR = -11,
    WRONG_CAR_ERR,
    ALLOC_ERR,
    READ_ERR,
    WRITE_ERR,
    REALLOC_ERR
};

#define CAR_ARR_CAPACITY 3

typedef struct node node_t;
typedef struct car car_t;
typedef struct cars_arr cars_arr_t;
typedef struct arr arr_t;
typedef int (*comparator_t)(const void *, const void *);

struct car
{
    char *model;
    long licence_number;
    int year;
    char *owners_name;
};

struct node
{
    void *data;
    node_t *next;
};

struct cars_arr
{
    car_t *data;
    size_t n;
    size_t max_n;
};

struct arr
{
    void *data;
    size_t n;
    size_t max_n;
};

int alloc_node(node_t **node);
size_t count_nodes(node_t *head);

void clear_car(car_t *car);
void clear_cars(cars_arr_t *cars);

void free_car(car_t *car);
void free_cars(cars_arr_t *cars);

int fread_car(FILE *f, car_t *car);
int fread_cars(FILE *f, cars_arr_t *cars);
int fwrite_car_list(FILE *f, node_t *cars_list);

void free_list(node_t *list);

void print_car(car_t car);
void print_cars(cars_arr_t cars);

int realloc_cars(cars_arr_t *cars, size_t new_n_max);

int init_car_list(node_t *dst_list, cars_arr_t *src_arr);
void free_car_list(node_t *list);

void *pop_back(node_t **head);
void *pop_front(node_t **head);

void insert(node_t **head, node_t *elem, node_t *before);
void remove_duplicates(node_t **head, comparator_t comparator);
void front_back_split(node_t *head, node_t **back);
node_t *sort(node_t *head, comparator_t comparator);
node_t *find(node_t *list, const void *data, comparator_t comparator);
node_t *sorted_merge(node_t **head_a, node_t **head_b, comparator_t comparator);

int car_model_comparator(const void *e1, const void *e2);
int init_list_from_array(node_t **head, void *arr, size_t n, size_t size);

#endif