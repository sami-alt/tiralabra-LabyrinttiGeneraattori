#ifndef TRIANGULATION_H
#define TRIANGULATION_H

#include <stddef.h>
#include <stdlib.h>
#include "point.h"
#include "triangle.h"
#include "edge_list.h"

typedef struct Triangulation {
    Point *points;
    int num_points;
    int points_capacity;

    Triangle *triangles;
    int num_triangles;
    int triangles_capacity;
} Triangulation;

void triangulation_init(Triangulation *triangulation);
int triangulation_add_point(Triangulation *triangulation, Point point);
void triangulation_add_triangle(Triangulation *triangulation, Triangle triangle);
void triangulation_free(Triangulation *triangulation);
int triangulation_create_super_triangle(Triangulation *triangulation);
void triangulation_remove_triangle(Triangulation *triangulation, int index);
void triangulation_remove_bad_triangles(Triangulation *triangulation, Point point, EdgeList *boundary);
void triangulation_create_new_triangles(Triangulation *triangulation, EdgeList *boundary, int point_idex);
int bowyer_watson(Triangulation *triangulation);

#endif // TRIANGULATION_H