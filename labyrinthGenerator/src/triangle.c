#include <math.h>
#include "triangle.h"
#include "point.h"

Triangle create_triangle( int p1, int p2, int p3) {
    Triangle t;
    t.p1 = p1;
    t.p2 = p2;
    t.p3 = p3;
    return t;
}

double get_triangle_area(Triangle t, const Point *points) {
    Point p1 = points[t.p1];
    Point p2 = points[t.p2];
    Point p3 = points[t.p3];

    double area = p1 .x * (p2.y - p3.y) +
                  p2.x * (p3.y - p1.y) +
                  p3.x * (p1.y - p2.y);
    return fabs(area) / 2.0;
}

/*
    Tarkistaa mihin suuntaan kolmion on luotu pisteiden kiertosuuntaan nähden.
*/

Orientation get_triangle_orientation(Triangle t, const Point *points) {
    Point p1 = points[t.p1];
    Point p2 = points[t.p2];
    Point p3 = points[t.p3];

    double determinant = (p2.y - p1.y) * (p3.x - p2.x) -
                 (p2.x - p1.x) * (p3.y - p2.y);

    if (determinant == 0) return COLLINEAR;
    return (determinant > 0) ? CLOCKWISE : COUNTERCLOCKWISE;
}

int point_in_circumcicle(Triangle t, const Point *points, Point p) {
    Point p1 = points[t.p1];
    Point p2 = points[t.p2];
    Point p3 = points[t.p3];

    double ax = p1.x - p.x;
    double ay = p1.y - p.y;
    double bx = p2.x - p.x;
    double by = p2.y - p.y;
    double cx = p3.x - p.x;
    double cy = p3.y - p.y;

    double determinant = (ax * ax + ay * ay) * (bx * cy - cx * by) -
                         (bx * bx + by * by) * (ax * cy - cx * ay) +
                         (cx * cx + cy * cy) * (ax * by - bx * ay);

    Orientation orientation = get_triangle_orientation(t, points);

    if(orientation == COLLINEAR) {
        return 0;
    }
    if(orientation == COUNTERCLOCKWISE) {
        return determinant > 0;
    }

    return determinant < 0;
}

int point_in_triangle(Point p, Triangle t, const Point *points) {
    Point p1 = points[t.p1];
    Point p2 = points[t.p2];
    Point p3 = points[t.p3];

    double d1 = (p.x - p2.x)  * (p1.y - p2.y) 
              - (p1.x - p2.x) * (p.y - p2.y);
    double d2 = (p.x - p3.x)  * (p2.y - p3.y) 
              - (p2.x - p3.x) * (p.y - p3.y);
    double d3 = (p.x - p1.x)  * (p3.y - p1.y) 
              - (p3.x - p1.x) * (p.y - p1.y);

    int has_neg = (d1 < 0) || (d2 < 0) || (d3 < 0);
    int has_pos = (d1 > 0) || (d2 > 0) || (d3 > 0);

    return !(has_neg && has_pos);
}