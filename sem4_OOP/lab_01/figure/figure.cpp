#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "figure.h"


err_t fload_point(FILE *f, point_3D_t &point)
{
    if (f == NULL)
        return WRONG_FILE_PTR_ERR;

    err_t rc = SUCCESS;
    if (fscanf(f, "%lf %lf %lf", &point.x, &point.y, &point.z) != 3)
        rc = WRONG_FILE_ERR;

    return rc;
}


err_t fload_points(FILE *f, point_3D_t *points, const size_t npoints)
{
    if (f == NULL)
        return WRONG_FILE_PTR_ERR;

    if (points == NULL)
        return WRONG_POINTS_PTR_ERR;

    if (npoints == 0)
        return WRONG_NPOINTS_ERR;

    err_t rc = SUCCESS;
    for (size_t i = 0; (i < npoints) && (rc == SUCCESS); ++i)
        rc = fload_point(f, points[i]);

    return rc;
}


err_t fload_npoints(FILE *f, size_t &n)
{
    if (f == NULL)
        return WRONG_FILE_PTR_ERR;

    err_t rc = SUCCESS;
    if (fscanf(f, "%zu", &n) != 1)
        rc = WRONG_FILE_ERR;

    return rc;
}

err_t alloc_points(point_3D_t *&points, const size_t n)
{
    if (points != NULL)
        return WRONG_POINTS_PTR_ERR;

    if (n == 0)
        return WRONG_NPOINTS_ERR;

    err_t rc = SUCCESS;
    points = (point_3D_t *)calloc(n, sizeof(point_3D_t));
    if (points == NULL)
        rc = POINTS_ALLOC_ERR;

    return rc;
}

err_t free_points(points_3D_t &points)
{
    free(points.data);
    points.data = NULL;
    points.n = 0;
    return SUCCESS;
}

err_t fload_points_section(FILE *f, points_3D_t &points)
{
    if (f == NULL)
        return WRONG_FILE_PTR_ERR;

    if (points.data != NULL)
        return WRONG_POINTS_PTR_ERR;

    if (points.n != 0)
        return WRONG_NPOINTS_ERR;

    err_t rc = SUCCESS;
    rc = fload_npoints(f, points.n);

    if (rc == SUCCESS) {
        rc = alloc_points(points.data, points.n);

        if (rc == SUCCESS) {
            rc = fload_points(f, points.data, points.n);

            if (rc != SUCCESS)
                rc = free_points(points);
        }
    }

    return rc;
}

err_t fload_edge(FILE *f, edge_t &edge)
{
    if (f == NULL)
        return WRONG_FILE_PTR_ERR;

    err_t rc = SUCCESS;
    if (fscanf(f, "%zu %zu", &edge.first, &edge.second) != 2)
        rc = WRONG_FILE_ERR;

    if (rc == SUCCESS) {
        --edge.first;
        --edge.second;
    }

    return rc;
}


err_t fload_edges(FILE *f, edge_t *edges, const size_t nedges)
{
    if (f == NULL)
        return WRONG_FILE_PTR_ERR;

    if (edges == NULL)
        return WRONG_EDGES_PTR_ERR;

    if (nedges == 0)
        return WRONG_NEDGES_ERR;

    err_t rc = SUCCESS;
    for (size_t i = 0; (i < nedges) && (rc == SUCCESS); ++i)
        rc = fload_edge(f, edges[i]);

    return rc;
}


err_t fload_nedges(FILE *f, size_t &n)
{
    if (f == NULL)
        return WRONG_FILE_PTR_ERR;

    err_t rc = SUCCESS;
    if (fscanf(f, "%zu", &n) != 1)
        rc = WRONG_FILE_ERR;

    return rc;
}

err_t alloc_edges(edge_t *&edges, const size_t n)
{
    if (edges != NULL)
        return WRONG_EDGES_PTR_ERR;

    if (n == 0)
        return WRONG_NEDGES_ERR;

    err_t rc = SUCCESS;
    edges = (edge_t *)calloc(n, sizeof(edge_t));
    if (edges == NULL)
        rc = EDGES_ALLOC_ERR;

    return rc;
}

err_t free_edges(edges_t &edges)
{
    free(edges.data);
    edges.data = NULL;
    edges.n = 0;
    return SUCCESS;
}


err_t fload_edges_section(FILE *f, edges_t &edges)
{
    if (f == NULL)
        return WRONG_FILE_PTR_ERR;

    if (edges.data != NULL)
        return WRONG_EDGES_PTR_ERR;

    if (edges.n != 0)
        return WRONG_NEDGES_ERR;

    err_t rc = SUCCESS;
    rc = fload_nedges(f, edges.n);

    if (rc == SUCCESS) {
        rc = alloc_edges(edges.data, edges.n);

        if (rc == SUCCESS) {
            rc = fload_edges(f, edges.data, edges.n);

            if (rc != SUCCESS)
                rc = free_edges(edges);
        }
    }

    return rc;
}

err_t fload_figure(figure_t &figure, const char *file_name)
{
    if (!file_name)
        return EMPTY_FILE_NAME;

    err_t rc = SUCCESS;
    FILE *f = fopen(file_name, "r");
    if (f == NULL)
        rc = OPEN_FILE_ERR;

    if (rc == SUCCESS) {
        figure_t tmp_figure = {};
        rc = fload_points_section(f, tmp_figure.points);

        if (rc == SUCCESS) {
            rc = fload_edges_section(f, tmp_figure.edges);

            if (rc == SUCCESS)
                figure = tmp_figure;
            else
                rc = free_points(tmp_figure.points);
        }
        
        fclose(f);
    }

    return rc;
}

err_t fsave_npoints(FILE *f, size_t npoints)
{
    if (f == NULL)
        return WRONG_FILE_PTR_ERR;

    err_t rc = SUCCESS;
    if (fprintf(f, "%zu\n", npoints) < 0)
        rc = FSAVE_NPOINTS_ERR;

    return rc;
}

err_t clear_file(FILE *f)
{
    if (f == NULL)
        return WRONG_FILE_PTR_ERR;

    err_t rc = SUCCESS;
    int fd = fileno(f);
    if (fd == -1)
        rc = FILE_DESC_OBTAIN_ERR;

    if (ftruncate(fd, 0) != 0)
        rc = FTRUNCATE_ERR;

    return rc;
}

err_t fsave_point(FILE *f, const point_3D_t &point)
{
    if (f == NULL)
        return WRONG_FILE_PTR_ERR;

    err_t rc = SUCCESS;
    if (fprintf(f, "%lf %lf %lf\n", point.x, point.y, point.z) < 0)
        rc = FSAVE_NPOINTS_ERR;

    return rc;
}

err_t fsave_points(FILE *f, const point_3D_t *points, size_t npoints)
{
    if (f == NULL)
        return WRONG_FILE_PTR_ERR;

    err_t rc = SUCCESS;
    for (size_t i = 0; (i < npoints) && (rc == SUCCESS); ++i)
        rc = fsave_point(f, points[i]);

    return rc;
}

err_t fsave_points_segment(FILE *f, const points_3D_t &points)
{
    if (f == NULL)
        return WRONG_FILE_PTR_ERR;

    err_t rc = SUCCESS;

    rc = fsave_npoints(f, points.n);
    if (rc == SUCCESS) {
        rc = fsave_points(f, points.data, points.n);

        if (rc != SUCCESS)
            rc = clear_file(f);
    }

    return rc;
}

err_t fsave_nedges(FILE *f, size_t nedges)
{
    if (f == NULL)
        return WRONG_FILE_PTR_ERR;

    err_t rc = SUCCESS;
    if (fprintf(f, "%zu\n", nedges) < 0)
        rc = FSAVE_NEDGES_ERR;

    return rc;
}

err_t fsave_edge(FILE *f, const edge_t &edge)
{
    if (f == NULL)
        return WRONG_FILE_PTR_ERR;

    err_t rc = SUCCESS;
    if (fprintf(f, "%zu %zu\n", edge.first, edge.second) < 0)
        rc = FSAVE_NEDGES_ERR;

    return rc;
}

err_t fsave_edges(FILE *f, const edge_t *edges, size_t nedges)
{
    if (f == NULL)
        return WRONG_FILE_PTR_ERR;

    err_t rc = SUCCESS;
    for (size_t i = 0; (i < nedges) && (rc == SUCCESS); ++i)
        rc = fsave_edge(f, edges[i]);

    return rc;
}

err_t fsave_edges_segment(FILE *f, const edges_t &edges)
{
    if (f == NULL)
        return WRONG_FILE_PTR_ERR;

    err_t rc = SUCCESS;

    rc = fsave_nedges(f, edges.n);
    if (rc == SUCCESS) {
        rc = fsave_edges(f, edges.data, edges.n);

        if (rc != SUCCESS)
            rc = clear_file(f);
    }

    return rc;
}

err_t fsave_figure(figure_t &figure, const char *file_name)
{
    if (file_name == NULL)
        return EMPTY_FILE_NAME;

    err_t rc = SUCCESS;
    FILE *f = fopen(file_name, "w");
    if (f == NULL)
        rc = OPEN_FILE_ERR;

    if (rc == SUCCESS) {
        rc = fsave_points_segment(f, figure.points);

        if (rc == SUCCESS) {
            rc = fsave_edges_segment(f, figure.edges);

            if (rc != SUCCESS)
                rc = clear_file(f);
        }

        fclose(f);
    }

    return rc;
}

err_t move_point(point_3D_t &point, const move_t move)
{
    err_t rc = SUCCESS;
    point.x += move.dx;
    point.y += move.dy;
    point.z += move.dz;
    return rc;
}

err_t move_points(points_3D_t &points, const move_t move)
{
    err_t rc = SUCCESS;
    for (size_t i = 0; (i < points.n) && (rc == SUCCESS); ++i)
        rc = move_point(points.data[i], move);
    return rc;
}

err_t move_figure(figure_t &figure, const move_t &move)
{
    err_t rc = move_points(figure.points, move);
    return rc;
}

err_t scale_point(point_3D_t &point, point_3D_t &scale_center, const scale_t &scale)
{
    err_t rc = SUCCESS;
    point.x = (point.x - scale_center.x) * scale.kx + scale_center.x;
    point.y = (point.y - scale_center.y) * scale.ky + scale_center.y;
    point.z = (point.z - scale_center.z) * scale.kz + scale_center.z;
    return rc;
}

err_t scale_points(points_3D_t &points, const scale_t &scale)
{
    err_t rc = SUCCESS;
    // for (size_t i = 0; (i < points.n) && (rc == SUCCESS); ++i)
    //     rc = scale_point(points.data[i], scale);
    return rc;
}

err_t scale_figure(figure_t &figure, const scale_t &scale)
{
    err_t rc = scale_points(figure.points, scale);
    return rc;
}

err_t rotate_point(point_3D_t &point, const scale_t &scale)
{
    err_t rc = SUCCESS;
    // point.x = ;
    // point.y = ;
    // point.z = ;
    return rc;
}

err_t rotate_points(points_3D_t &points, const rotate_t &rotate)
{
    err_t rc = SUCCESS;

    return rc;
}

err_t rotate_figure(figure_t &figure, const rotate_t &rotate)
{
    err_t rc = rotate_points(figure.points, rotate);
    return rc;
}

