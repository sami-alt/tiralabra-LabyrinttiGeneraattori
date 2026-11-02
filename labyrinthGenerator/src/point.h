#ifndef POINT_H
#define POINT_H

typedef struct Point {
    double x;
    double y;
} Point;

Point createPoint(double x, double y);
int pointEquals(Point p1, Point p2);
#endif // POINT_H   
