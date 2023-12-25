#define _GNU_SOURCE
#include "list.h"
#include <stdio.h>

enum args
{
    PROGRAM_NAME,
    IN_FILE,
    OUT_FILE,
    N_ARGS
};

enum errs
{
    ARG_ERR = -1,
    FILE_ERR = -2
};

int main(int argc, char *argv[])
{
    int rc;
    if (argc != N_ARGS)
        return ARG_ERR;

    FILE *f_in = fopen(argv[IN_FILE], "r");
    if (!f_in)
        return FILE_ERR;

    cars_arr_t cars;
    clear_cars(&cars);

    if ((rc = fread_cars(f_in, &cars)) != 0)
    {
        fclose(f_in);
        return rc;
    }

    fclose(f_in);

    node_t *car_info_list;
    if ((rc = init_list_from_array(&car_info_list, cars.data, cars.n, sizeof(car_t))) != 0)
    {
        free_cars(&cars);
        return rc;
    }

    if (count_nodes(car_info_list) > 1)
    {
        car_t *first_data = pop_front(&car_info_list);
        car_t *last_data = pop_back(&car_info_list);

        node_t *first_dup = find(car_info_list, first_data, car_model_comparator);
        if (first_dup && last_data)
        {
            node_t *last_dup;
            if ((rc = alloc_node(&last_dup)))
                return rc;
            last_dup->data = last_data;

            insert(&car_info_list, last_dup, first_dup);
        }
        else
            remove_duplicates(&car_info_list, car_model_comparator);

        car_info_list = sort(car_info_list, car_model_comparator);
    }

    print_cars(cars);

    FILE *f_out = fopen(argv[OUT_FILE], "w");
    if (f_out == NULL)
    {
        free_cars(&cars);
        free_list(car_info_list);
        return FILE_ERR;
    }

    if ((rc = fwrite_car_list(f_out, car_info_list)))
    {
        fclose(f_out);
        free_cars(&cars);
        free_list(car_info_list);
    }

    fclose(f_out);
    free_cars(&cars);
    free_list(car_info_list);

    return 0;
}
