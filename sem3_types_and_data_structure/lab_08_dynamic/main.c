#include "graph.h"
#include "input.h"
#include <stdio.h>
#include <time.h>
#include <sys/time.h>

typedef enum {
    EXIT,
    LOAD_FROM_FILE,
    FIND_MAX_SIMPLE_PATH,
    PRINT,
    MESURE_EFF,
    N_COMMANDS
} menu;

#define IMG_PATH "test"
#define N_TESTS 50

unsigned long long current_time()
{
    struct timespec ts = {};
    clockid_t clkid;
    clkid = CLOCK_REALTIME;
    clock_gettime(clkid, &ts);

    return ts.tv_sec * 1000000000 + ts.tv_nsec;
}

int main() {
    matrix_graph_t matrix_graph = {};
    // list_arr_graph_t list_arr_graph = {};
    searcher_info_t max_path_info_matrix_graph = {};
    // searcher_info_t max_path_info_list_arr_graph = {};

    int command = -1;
    FILE *f = NULL;
    while (command != EXIT) {
        printf("Command menu:\n"
               "0 - Exit\n"
               "1 - Load graph from file\n"
               "2 - Find max simple path in graph\n"
               "3 - Print graph image\n"
               "4 - Mesure efficiency\n");

        printf(">> Enter number of the command to execute: ");
        if (read_int(&command) < 0 || command < 0)
            printf("Wrong command. Command is a number between %d and %d.\n", 0, N_COMMANDS);

        switch (command) {
            case LOAD_FROM_FILE:
                free_matrix_graph(&matrix_graph);
                if (f != NULL)
                    fclose(f);

                f = NULL;
                printf(">> To start working with graph enter name of the file to load data from: ");
                while (f == NULL) {
                    char file_name[MAX_STR_LEN];
                    while (read_str(stdin, file_name, MAX_STR_LEN) <= 0)
                        printf("Wrong file name. Try again: ");

                    f = fopen(file_name, "r");
                    if (f == NULL) {
                        printf("Error while opening a file. Try again with another one: ");
                        continue;
                    }

                    if (fscanf_matrix_graph(f, &matrix_graph)) {
                        printf("Error while loading the data. File is corrupt. Try again with another one: ");
                        fclose(f);
                        f = NULL;
                        continue;
                    }

                    // if (fscanf_list_arr_graph(f, &list_arr_graph)) {
                    //     printf("Error while loading the data. File is corrupt. Try again with another one: ");
                    //     fclose(f);
                    //     f = NULL;
                    //     continue;
                    // }
                    break;
                }
                break;
            case FIND_MAX_SIMPLE_PATH:
                if (is_matrix_graph_empty(&matrix_graph)) {
                    printf("Error. Nothing to work with: matrix graph is empty.\n");
                    break;
                }

                find_max_simple_path_in_matrix_graph(&matrix_graph, &max_path_info_matrix_graph);
                printf("Max simple path was found in the matrix graph:\n");
                print_path(&max_path_info_matrix_graph);

                // if (is_list_arr_graph_empty(&list_arr_graph)) {
                //     printf("Error. Nothing to work with: list arr graph is empty.\n");
                //     break;
                // }

                // find_max_simple_path_in_lsit_arr_graph(&list_arr_graph, &max_path_info_list_arr_graph);
                // printf("Max simple path was found in the list array graph:\n");
                // print_path(&max_path_info_list_arr_graph);
                break;
            case PRINT:
                if (is_matrix_graph_empty(&matrix_graph)) {
                    printf("Error. Nothing to work with: matrix graph is empty.\n");
                    break;
                }

                open_matrix_graph_img("matrix_graph", &matrix_graph);

                // if (is_list_arr_graph_empty(&list_arr_graph)) {
                //     printf("Error. Nothing to work with: list arr graph is empty.\n");
                //     break;
                // }

                // open_list_arr_graph_img("list_arr_graph", &list_arr_graph);
                break;
            case MESURE_EFF:
                if (is_matrix_graph_empty(&matrix_graph)) {
                    printf("Error. Nothing to work with: matrix graph is empty.\n");
                    break;
                }

                printf(">> EFFICIENCY\n");
                unsigned long long time;
                unsigned long long all_time = 0;
                for (int i = 0; i < N_TESTS; ++i) {
                    time = current_time();
                    find_max_simple_path_in_matrix_graph(&matrix_graph, &max_path_info_matrix_graph);
                    all_time += current_time() - time;
                }
                printf("Average search time: %lld nsec\n", all_time / N_TESTS);
                printf("Size: %zu bytes\n\n", sizeof(int) * matrix_graph.n_vertexes * matrix_graph.n_vertexes);
                break;
            case EXIT:
                break;
            default:
                printf("Wrong command. Command is a number between %d and %d.\n", 0, N_COMMANDS);
                break;
        }
    }

    free_matrix_graph(&matrix_graph);
    return 0;
}
