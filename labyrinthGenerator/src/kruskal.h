#ifndef KRUSKAL_H
#define KRUSKAL_H

#include "graph.h"
#include "union_find.h"

int compare_graph_edges(const void *edge1, const void *edge2);
int kruskal_minimum_spanning_tree(const Graph *graph, int num_vertices, Graph *mst);



#endif // KRUSKAL_H