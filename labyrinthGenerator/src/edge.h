#ifndef EDGE_H
#define EDGE_H

#include "point.h"

typedef struct Edge {
    int p1;
    int p2;
} Edge;

Edge create_edge(int p1, int p2);
int edge_equals(Edge e1, Edge e2);

#endif // EDGE_H