#include "graph.h"
#include "input.h"
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>

void print_path(searcher_info_t *info)
{
    for (int i = 0; i < info->path_cur_size; ++i) {
        printf("%d", info->path[i] + 1);
        if (i != info->path_cur_size - 1)
            printf(" -> ");
    }

    printf("\n");
}

void matrix_graph_DFS(matrix_graph_t *graph, searcher_info_t *cur_path_info, searcher_info_t *max_path_info, int vertex) {
    cur_path_info->visited[vertex] = true;
    cur_path_info->path[cur_path_info->path_cur_size++] = vertex;

    if (cur_path_info->path_cur_size > max_path_info->path_cur_size)
        *max_path_info = *cur_path_info;

    for (int cur_vertex = 0; cur_vertex < graph->n_vertexes; ++cur_vertex)
        if (graph->matrix[vertex][cur_vertex] == 1 && !cur_path_info->visited[cur_vertex])
            matrix_graph_DFS(graph, cur_path_info, max_path_info, cur_vertex);

    cur_path_info->visited[vertex] = false;
    cur_path_info->path_cur_size--;
}

void find_max_simple_path_in_matrix_graph(matrix_graph_t *graph, searcher_info_t *max_path_info) {
    for (int cur_vertex = 0; cur_vertex < graph->n_vertexes; ++cur_vertex) {
        searcher_info_t cur_path_info = {};
        matrix_graph_DFS(graph, &cur_path_info, max_path_info, cur_vertex);
    }
}

void matrix_graph_to_dot(FILE *f, char *graph_name, matrix_graph_t *graph)
{
    fprintf(f, "digraph %s {\n\
    node [shape=oval, fontname=\"Arial\", fontsize=12];\
    edge [fontsize=10];",
    graph_name);

    for (int i = 0; i < graph->n_vertexes; ++i)
        for (int j = 0; j < graph->n_vertexes; ++j)
            if (graph->matrix[i][j])
                fprintf(f, "%d -> %d;\n", i + 1, j + 1);

    fprintf(f, "}\n");
}

int open_matrix_graph_img(char *file_name, matrix_graph_t *graph)
{
    char path[MAX_STR_LEN];
    sprintf(path, "./img/%s.dot", file_name);

    FILE *out_img = fopen(path, "w");
    if (!out_img)
        return BAD_IMAGE;

    matrix_graph_to_dot(out_img, "_graph_", graph);
    fclose(out_img);

    char command[MAX_STR_LEN * 2];
    sprintf(command, "dot -Tpng %s -o ./img/%s.png && sxiv ./img/%s.png &", path, file_name, file_name);
    system(command);
    return 0;
}

int is_matrix_graph_empty(matrix_graph_t *graph)
{
    if (graph->n_vertexes == 0)
        return 1;

    for (int i = 0; i < graph->n_vertexes; ++i)
        for (int j = 0; j < graph->n_vertexes; ++j)
            if (graph->matrix[i][j] == 1)
                return 0;

    return 1;
}

int fscanf_matrix_graph(FILE *f, matrix_graph_t *graph)
{
    fseek(f, 0, SEEK_SET);
    if (fscanf(f, "%d", &graph->n_vertexes) != 1 || graph->n_vertexes <= 1)
        return READ_ERR;

    graph->matrix = calloc(graph->n_vertexes, sizeof(int *));
    for (int i = 0; i < graph->n_vertexes; ++i)
        graph->matrix[i] = calloc(graph->n_vertexes, sizeof(int));

    for (int i = 0; i < graph->n_vertexes; ++i)
        for (int j = 0; j < graph->n_vertexes; ++j)
            if (fscanf(f, "%d", &graph->matrix[i][j]) != 1 || 
                (graph->matrix[i][j] != 0 && graph->matrix[i][j] != 1))
                return READ_ERR;

    return 0;
}

void free_matrix_graph(matrix_graph_t *graph)
{
    for (int i = 0; i < graph->n_vertexes; ++i)
        free(graph->matrix[i]);

    free(graph->matrix);
    graph->matrix = NULL;
    graph->n_vertexes = 0;
}

// node_t *create_node(int vertex)
// {
//     node_t *new_node = calloc(1, sizeof(node_t));
//     if (new_node != NULL)
//         new_node->vertex = vertex;
    
//     return new_node;
// }


// void free_list_arr_graph(list_arr_graph_t *graph)
// {
//     node_t *tmp;
//     for (int i = 0; i < graph->n_vertexes; ++i)
//         for (node_t *cur_node = graph->list_arr[i]; cur_node; cur_node = tmp) {
//             tmp = cur_node->next;
//             free(cur_node);
//         }

//     free(graph->list_arr);
//     graph->list_arr = NULL;
//     graph->n_vertexes = 0;
// }


// int fscanf_list_arr_graph(FILE *f, list_arr_graph_t *graph)
// {
//     fseek(f, 0, SEEK_SET);
//     if (fscanf(f, "%d", &graph->n_vertexes) != 1 || graph->n_vertexes <= 1)
//         return READ_ERR;

//     graph->list_arr = calloc(graph->n_vertexes, sizeof(node_t *));
//     if (graph->list_arr == NULL)
//         return ALLOC_ERR;

//     for (int i = 0; i < graph->n_vertexes; ++i) {
//         node_t *cur_node = NULL;
//         for (int j = 0; j < graph->n_vertexes; ++j) {
//             int vertex;
//             if (fscanf(f, "%d", &vertex) != 1 || (vertex != 0 && vertex != 1)) {
//                 free_list_arr_graph(graph);
//                 return READ_ERR;
//             }

//             if (vertex) {
//                 if (cur_node != NULL) {
//                     cur_node->next = create_node(vertex);
//                     if (cur_node->next == NULL) {
//                         free_list_arr_graph(graph);
//                         return ALLOC_ERR;
//                     }
//                     cur_node = cur_node->next;
//                 } else {
//                     graph->list_arr[i] = create_node(vertex);
//                     if (graph->list_arr[i] == NULL)
//                         return ALLOC_ERR;
//                     cur_node = graph->list_arr[i];
//                 }
//             }
//         }
//     }

//     return 0;
// }

// void list_arr_graph_to_dot(FILE *f, char *graph_name, list_arr_graph_t *graph)
// {
//     fprintf(f, "digraph %s {\n\
//     node [shape=oval, fontname=\"Arial\", fontsize=12];\
//     edge [fontsize=10];",
//     graph_name);

//     for (int i = 0; i < graph->n_vertexes; ++i)
//         for (node_t *cur_node = graph->list_arr[i]->next; cur_node; cur_node = cur_node->next)
//             fprintf(f, "%d -> %d;\n", graph->list_arr[0]->vertex + 1, cur_node->vertex + 1);

//     fprintf(f, "}\n");
// }

// int open_list_arr_graph_img(char *file_name, list_arr_graph_t *graph)
// {
//     char path[MAX_STR_LEN];
//     sprintf(path, "./img/%s.dot", file_name);

//     FILE *out_img = fopen(path, "w");
//     if (!out_img)
//         return BAD_IMAGE;

//     list_arr_graph_to_dot(out_img, "_graph_", graph);
//     fclose(out_img);

//     char command[MAX_STR_LEN * 2];
//     sprintf(command, "dot -Tpng %s -o ./img/%s.png && sxiv ./img/%s.png &", path, file_name, file_name);
//     system(command);
//     return 0;
// }

// int is_list_arr_graph_empty(list_arr_graph_t *graph)
// {
//     if (graph->n_vertexes == 0)
//         return 1;

    
//     for (int i = 0; i < graph->n_vertexes; ++i)
//         for (node_t *cur_node = graph->list_arr[i]->next; cur_node; cur_node = cur_node->next)
//             if (cur_node->vertex == 1)
//                 return 0;

//     return 1;
// }


