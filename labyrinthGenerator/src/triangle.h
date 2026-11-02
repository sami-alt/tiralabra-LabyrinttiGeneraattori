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


int pointInCircumcircle(Triangle t, const Point *points, Point p);
Orientation getTriangleOrientation(Triangle t, const Point *points);
Triangle createTriangle(int p1, int p2, int p3);
double triangleArea(Triangle t, Point *points);

#endif // TRIANGLE_H