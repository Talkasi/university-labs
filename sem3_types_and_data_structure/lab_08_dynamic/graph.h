#ifndef GRAPH_H
#define GRAPH_H
#include <stdio.h>
#include <stdbool.h>

#define MAX_SIZE 100

enum errs {
    BAD_IMAGE = -10,
    ALLOC_ERR = -11,
    READ_ERR
};

typedef struct matrix_graph matrix_graph_t;
typedef struct list_arr_graph list_arr_graph_t;
typedef struct searcher_info searcher_info_t;
typedef struct node node_t;

struct matrix_graph {
    int **matrix;
    int n_vertexes;
};

// struct node {
//     int vertex;
//     node_t *next;
// };

// struct list_arr_graph {
//     node_t **list_arr;
//     int n_vertexes;
// };

struct searcher_info {
    bool visited[MAX_SIZE];
    int path[MAX_SIZE];
    int path_cur_size;
};

void print_path(searcher_info_t *info);

void matrix_graph_DFS(matrix_graph_t *graph, searcher_info_t *cur_path_info, searcher_info_t *max_path_info, int vertex);
void find_max_simple_path_in_matrix_graph(matrix_graph_t *graph, searcher_info_t *max_path_info);
void matrix_graph_to_dot(FILE *f, char *graph_name, matrix_graph_t *graph);
int open_matrix_graph_img(char *file_name, matrix_graph_t *graph);
int is_matrix_graph_empty(matrix_graph_t *graph);
void free_matrix_graph(matrix_graph_t *graph);
int fscanf_matrix_graph(FILE *f, matrix_graph_t *graph);


// node_t *create_node(int vertex);
// void free_list_arr_graph(list_arr_graph_t *graph);
// int fscanf_list_arr_graph(FILE *f, list_arr_graph_t *graph);
// void list_arr_graph_to_dot(FILE *f, char *graph_name, list_arr_graph_t *graph);
// int open_list_arr_graph_img(char *file_name, list_arr_graph_t *graph);
// int is_list_arr_graph_empty(list_arr_graph_t *graph);

#endif
