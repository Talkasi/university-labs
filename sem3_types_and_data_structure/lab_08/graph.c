#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>

#define MAX_SIZE 100
#define IMG_PATH "test"
#define MAX_STR_LEN 100
#define BAD_IMAGE 1

typedef struct graph graph_t;
typedef struct searcher_info searcher_info_t;

struct graph {
    int matrix[MAX_SIZE][MAX_SIZE];
    int n_vertexes;
};

struct searcher_info {
    bool visited[MAX_SIZE];
    int path[MAX_SIZE];
    int path_cur_size;
};

void DFS(graph_t *graph, searcher_info_t *cur_path_info, searcher_info_t *max_path_info, int vertex) {
    cur_path_info->visited[vertex] = true;
    cur_path_info->path[cur_path_info->path_cur_size++] = vertex;

    if (cur_path_info->path_cur_size > max_path_info->path_cur_size)
        *max_path_info = *cur_path_info;

    for (int cur_vertex = 0; cur_vertex < graph->n_vertexes; ++cur_vertex)
        if (graph->matrix[vertex][cur_vertex] == 1 && !cur_path_info->visited[cur_vertex])
            DFS(graph, cur_path_info, max_path_info, cur_vertex);

    cur_path_info->visited[vertex] = false;
    cur_path_info->path_cur_size--;
}

void find_max_path(graph_t *graph, searcher_info_t *max_path_info) {
    for (int cur_vertex = 0; cur_vertex < graph->n_vertexes; ++cur_vertex) {
        searcher_info_t cur_path_info = {};
        DFS(graph, &cur_path_info, max_path_info, cur_vertex);
    }
}

void graph_to_dot(FILE *f, char *graph_name, graph_t *graph)
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

int open_graph_img(char *file_name, graph_t *graph)
{
    char path[MAX_STR_LEN];
    sprintf(path, "./img/%s.dot", file_name);

    FILE *out_img = fopen(path, "w");
    if (!out_img)
        return BAD_IMAGE;

    graph_to_dot(out_img, "_graph_", graph);
    fclose(out_img);

    char command[MAX_STR_LEN * 2];
    sprintf(command, "dot -Tpng %s -o ./img/%s.png && sxiv ./img/%s.png &", path, file_name, file_name);
    system(command);
    return 0;
}

int main() {
    graph_t graph = {};
    searcher_info_t max_path_info = {};

    printf("Введите количество вершин в графе: ");
    scanf("%d", &graph.n_vertexes);

    printf("Введите матрицу смежности графа:\n");
    for (int i = 0; i < graph.n_vertexes; i++) {
        for (int j = 0; j < graph.n_vertexes; j++) {
            scanf("%d", &graph.matrix[i][j]);
        }
    }

    open_graph_img(IMG_PATH, &graph);
    find_max_path(&graph, &max_path_info);

    printf("Максимальный путь:\n");
    for (int i = 0; i < max_path_info.path_cur_size; i++) {
        printf("%d ", max_path_info.path[i] + 1);
    }
    printf("\n");

    return 0;
}
