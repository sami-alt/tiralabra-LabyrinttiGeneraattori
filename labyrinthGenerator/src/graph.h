#ifndef GRAPH_H
#define GRAPH_H

#include "edge.h"
#include "triangulation.h"
#include <stdlib.h>
#include <math.h>

typedef struct GraphEdge{
    Edge edge;
    double weight;
} GraphEdge;

typedef struct Graph{
    GraphEdge* edges;

    int num_edges;
    int capacity;
} Graph;

void graph_init(Graph* graph);
double calculate_edge_weight(const Triangulation *triangulation, Edge edge);
int graph_has_edge(const Graph *graph, Edge edge);
int graph_add_edge(Graph *graph, Edge edge, double weight);
int graph_from_triangulation(Graph *graph, const Triangulation *triangulation);
void graph_free(Graph *graph);


#endif // GRAPH_H