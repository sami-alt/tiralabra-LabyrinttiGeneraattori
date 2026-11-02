#include "edge.h"

Edge createEdge(int p1, int p2) {
    Edge e;
    e.p1 = p1;
    e.p2 = p2;
    return e;
}

int EdgeEquals(Edge e1, Edge e2) {
    return (e1.p1 == e2.p1 && e1.p2 == e2.p2) ||
           (e1.p1 == e2.p2 && e1.p2 == e2.p1);
}