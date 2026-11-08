#include "edge.h"

Edge create_edge(int p1, int p2) {
    Edge e;
    e.p1 = p1;
    e.p2 = p2;
    return e;
}


/*
    Tarkstetaan ovatko kolmioiden reunat päällekkäisiä eli jakavatko kaksi kolmiota saman reunan, näin voidaan välttää dublikaatteja reuna rakenteiden listassa.
*/
int edge_equals(Edge e1, Edge e2) {
    return (e1.p1 == e2.p1 && e1.p2 == e2.p2) ||
           (e1.p1 == e2.p2 && e1.p2 == e2.p1);
}