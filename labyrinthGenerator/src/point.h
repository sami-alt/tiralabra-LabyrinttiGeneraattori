#ifndef POINT_H
#define POINT_H

typedef struct Point {
    double x;
    double y;
} Point;

Point create_point(double x, double y);
int point_equals(Point p1, Point p2);
#endif // POINT_H   
