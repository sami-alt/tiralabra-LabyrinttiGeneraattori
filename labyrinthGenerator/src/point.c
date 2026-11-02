#include "point.h"

Point createPoint(double x, double y) {
    Point p;
    p.x = x;
    p.y = y;
    return p;
}

int pointEquals(Point p1, Point p2) {
    return p1.x == p2.x && p1.y == p2.y;
}