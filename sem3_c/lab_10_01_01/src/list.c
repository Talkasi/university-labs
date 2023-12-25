#define _GNU_SOURCE
#include "list.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

void clear_cars(cars_arr_t *cars)
{
    memset(cars, 0, sizeof(cars_arr_t));
}

void clear_car(car_t *car)
{
    memset(car, 0, sizeof(car_t));
}

void free_car(car_t *car)
{
    free(car->model);
    free(car->owners_name);
    clear_car(car);
}

void free_cars(cars_arr_t *cars)
{
    if (cars->data)
        for (size_t i = 0; i < cars->n; ++i)
            free_car(&cars->data[i]);

    free(cars->data);
    clear_cars(cars);
}

void free_str(char *s, size_t *s_len)
{
    free(s);
    s = NULL;
    *s_len = 0;
}

void del_new_line(char *s, size_t *s_len)
{
    if (s[*s_len - 1] == '\n')
        s[--*s_len] = '\0';
}

int all_space(char *s, size_t s_len)
{
    for (size_t i = 0; i < s_len; ++i)
        if (!isspace(s[i]))
            return 0;

    return 1;
}

int read_line(FILE *f, char **s, size_t *s_len)
{
    *s = NULL;
    ssize_t tmp_s_len;
    if ((tmp_s_len = getline(s, s_len, f)) == -1)
    {
        free_str(*s, s_len);
        return READ_ERR;
    }

    *s_len = tmp_s_len;

    del_new_line(*s, s_len);
    if (all_space(*s, *s_len) || *s_len == 0)
    {
        free_str(*s, s_len);
        return READ_ERR;
    }

    return 0;
}

int fread_car(FILE *f, car_t *car)
{
    size_t tmp;

    if (read_line(f, &car->model, &tmp))
        return NO_CAR_ERR;

    if (fscanf(f, "%ld\n", &car->licence_number) != 1 || car->licence_number < 0 ||
        fscanf(f, "%d\n", &car->year) != 1 || car->year < 0 || read_line(f, &car->owners_name, &tmp))
    {
        free_str(car->model, &tmp);
        return WRONG_CAR_ERR;
    }

    return 0;
}

int fread_cars(FILE *f, cars_arr_t *cars)
{
    int rc;
    cars->n = 0;
    if ((rc = realloc_cars(cars, CAR_ARR_CAPACITY)) != 0)
        return rc;

    while ((rc = fread_car(f, &cars->data[cars->n])) == 0)
        if (++cars->n >= cars->max_n && (rc = realloc_cars(cars, cars->max_n * 2)) != 0)
        {
            free_cars(cars);
            return rc;
        }

    if (rc != NO_CAR_ERR || (rc = realloc_cars(cars, cars->n)) != 0)
    {
        free_cars(cars);
        return rc;
    }

    if (cars->n == 0)
    {
        free_cars(cars);
        return READ_ERR;
    }

    return 0;
}

int fwrite_car_list(FILE *f, node_t *cars_list)
{
    for (node_t *cur_node = cars_list; cur_node; cur_node = cur_node->next)
    {
        car_t *car = (car_t *)cur_node->data;
        if (fprintf(f, "%s\n%ld\n%d\n%s\n", car->model, car->licence_number, car->year, car->owners_name) < 0)
            return WRITE_ERR;
    }

    return 0;
}

void print_car(car_t car)
{
    printf("%s\n%ld\n%d\n%s\n", car.model, car.licence_number, car.year, car.owners_name);
}

void print_cars(cars_arr_t cars)
{
    for (size_t i = 0; i < cars.n; ++i)
        print_car(cars.data[i]);
}

int realloc_cars(cars_arr_t *cars, size_t new_n_max)
{
    void *tmp = realloc(cars->data, new_n_max * sizeof(car_t));
    if (new_n_max == 0)
    {
        clear_cars(cars);
        return 0;
    }

    if (!tmp)
    {
        free_cars(cars);
        return REALLOC_ERR;
    }

    cars->data = tmp;
    cars->max_n = new_n_max;
    return 0;
}

int alloc_node(node_t **node)
{
    *node = calloc(1, sizeof(node_t));
    if (!*node)
    {
        *node = NULL;
        return ALLOC_ERR;
    }

    return 0;
}

void free_car_list(node_t *list)
{
    node_t *cur_node = list->next;
    while (cur_node)
    {
        node_t *tmp = cur_node->next;
        free(cur_node);
        cur_node = tmp;
    }
}

void *find_elem_by_index(void *arr, size_t i, size_t size)
{
    char *data = (char *)arr;
    return data + i * size;
}

int init_list_from_array(node_t **head, void *arr, size_t n, size_t size)
{
    int rc;
    if ((rc = alloc_node(head)) != 0)
    {
        free_list(*head);
        return rc;
    }

    node_t *cur_node = *head;
    cur_node->data = find_elem_by_index(arr, 0, size);

    for (size_t i = 1; i < n; ++i)
    {
        if ((rc = alloc_node(&cur_node->next)) != 0)
        {
            free_list(*head);
            return rc;
        }

        cur_node = cur_node->next;
        cur_node->data = find_elem_by_index(arr, i, size);
    }

    return 0;
}

void free_list(node_t *head)
{
    node_t *cur_node = head;
    while (cur_node)
    {
        node_t *tmp = cur_node->next;
        free(cur_node);
        cur_node = tmp;
    }
}

int car_model_comparator(const void *e1, const void *e2)
{
    car_t car1 = *(car_t *)e1;
    car_t car2 = *(car_t *)e2;

    return strcmp(car1.model, car2.model);
}

void *pop_front(node_t **head)
{
    if (head == NULL || *head == NULL)
        return NULL;

    node_t *to_delete = *head;
    void *ans = to_delete->data;
    *head = to_delete->next;

    free(to_delete);
    return ans;
}

void *pop_back(node_t **head)
{
    if (head == NULL || *head == NULL)
        return NULL;

    void *ans;
    node_t *cur_node = *head;
    if (cur_node->next == NULL)
    {
        ans = cur_node->data;
        free(cur_node);
        *head = NULL;
        return ans;
    }

    while (cur_node->next->next != NULL)
        cur_node = cur_node->next;

    ans = cur_node->next->data;
    free(cur_node->next);
    cur_node->next = NULL;

    return ans;
}

node_t *find(node_t *list, const void *data, comparator_t comparator)
{
    for (node_t *cur_node = list; cur_node; cur_node = cur_node->next)
        if (comparator(cur_node->data, data) == 0)
            return cur_node;

    return NULL;
}

void insert(node_t **head, node_t *elem, node_t *before)
{
    if (*head == before)
    {
        elem->next = *head;
        *head = elem;
        return;
    }

    for (node_t *cur_node = *head; cur_node; cur_node = cur_node->next)
        if (cur_node->next == before)
        {
            cur_node->next = elem;
            elem->next = before;
            return;
        }
}

void remove_duplicates(node_t **head, comparator_t comparator)
{
    if (head == NULL || *head == NULL)
        return;

    node_t *cur_node = *head;
    while (cur_node->next != NULL)
    {
        if (comparator(cur_node->data, cur_node->next->data) == 0)
        {
            node_t *tmp = cur_node->next;
            cur_node->next = tmp->next;
            free(tmp);
        }
        else
            cur_node = cur_node->next;
    }
}

size_t count_nodes(node_t *head)
{
    size_t i = 0;
    for (node_t *cur_node = head; cur_node; cur_node = cur_node->next)
        ++i;

    return i;
}

void front_back_split(node_t *head, node_t **back)
{
    if (head == NULL)
    {
        *back = NULL;
        return;
    }

    node_t *fast = head->next;
    node_t *slow = head;

    while (fast != NULL)
    {
        fast = fast->next;
        if (fast != NULL)
        {
            slow = slow->next;
            fast = fast->next;
        }
    }

    *back = slow->next;
    slow->next = NULL;
}

node_t *sorted_merge(node_t **head_a, node_t **head_b, comparator_t comparator)
{
    node_t *result;
    if (*head_a == NULL)
    {
        result = *head_b;
        *head_b = NULL;
        return result;
    }

    if (*head_b == NULL)
    {
        result = *head_a;
        *head_a = NULL;
        return result;
    }

    node_t *el_a = *head_a;
    node_t *el_b = *head_b;

    if (comparator(el_a->data, el_b->data) < 0)
    {
        result = el_a;
        el_a = el_a->next;
    }
    else
    {
        result = el_b;
        el_b = el_b->next;
    }

    node_t *result_head = result;

    while (el_a && el_b)
    {
        if (comparator(el_a->data, el_b->data) < 0)
        {
            result->next = el_a;
            el_a = el_a->next;
        }
        else
        {
            result->next = el_b;
            el_b = el_b->next;
        }

        result = result->next;
    }

    result->next = el_a == NULL ? el_b : el_a;
    *head_a = NULL;
    *head_b = NULL;
    return result_head;
}

node_t *sort(node_t *head, comparator_t comparator)
{
    if (head == NULL || head->next == NULL)
        return head;

    node_t *back = NULL;
    front_back_split(head, &back);
    head = sort(head, comparator);
    back = sort(back, comparator);
    return sorted_merge(&head, &back, comparator);
}
