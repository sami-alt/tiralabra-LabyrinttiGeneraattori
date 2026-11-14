#ifndef TRIANGLE_H
#define TRIANGLE_H  

#include "point.h"

typedef struct Triangle {
    int p1;
    int p2;
    int p3;
} Triangle;

typedef enum {
    COLLINEAR = 0,
    COUNTERCLOCKWISE = 1,
    CLOCKWISE = -1
} Orientation;


int point_in_circumcicle(Triangle t, const Point *points, Point p);
Orientation get_triangle_orientation(Triangle t, const Point *points);
Triangle create_triangle(int p1, int p2, int p3);
double get_triangle_area(Triangle t, const Point *points);
int point_in_triangle(Point p, Triangle t, const Point *points);

#endif // TRIANGLE_H