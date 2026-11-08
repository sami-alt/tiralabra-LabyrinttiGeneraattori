#ifndef EDGE_LIST_H
#define EDGE_LIST_H

#include "edge.h"

typedef struct EdgeList {
    Edge *edges;
    int size;
    int capacity;
} EdgeList;

void init_edge_list(EdgeList *list);
void add_edge_list(EdgeList *list, Edge e);
void free_edge_list(EdgeList *list);

void edge_list_toggle(EdgeList *list, Edge edge);

#endif // EDGE_LIST_H