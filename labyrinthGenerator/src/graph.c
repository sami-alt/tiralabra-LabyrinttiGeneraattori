#include "graph.h"

#include <stdlib.h>
#include <math.h>

void graph_init(Graph* graph) {
    graph->edges = NULL;
    graph->num_edges = 0;
    graph->capacity = 0;
}


double calculate_edge_weight(const Triangulation *triangulation, Edge edge) {
    Point p1 = triangulation->points[edge.p1];
    Point p2 = triangulation->points[edge.p2];
    double dx = p1.x - p2.x;
    double dy = p1.y - p2.y;
    return sqrt(dx * dx + dy * dy);
}

int graph_has_edge(const Graph *graph, Edge edge) {
    for (int i = 0; i < graph->num_edges; i++) {
        if (edge_equals(graph->edges[i].edge, edge)) {
            return 1;
        }
    }
    return 0;
}

int graph_add_edge(Graph* graph, Edge edge, double weight){
    if (graph == NULL) {
        return -1; 
    }

    if (!isfinite(weight)) {
        return -1; 
    }

    if(graph->num_edges >= graph->capacity) {
        int new_capacity = (graph->capacity == 0) ? 1 : graph->capacity * 2;
        GraphEdge* new_edges = realloc(graph->edges, new_capacity * sizeof(GraphEdge));
        if (new_edges == NULL) {
            return -1; 
        }
        graph->edges = new_edges;
        graph->capacity = new_capacity;
    }

    graph->edges[graph->num_edges].edge = edge;
    graph->edges[graph->num_edges].weight = weight;
    graph->num_edges++;

    return 1;
}

int graph_from_triangulation(Graph *graph, const Triangulation *triangulation){
    if (graph  == NULL || triangulation == NULL) {
        return -1;
    }
    for(int i = 0; i < triangulation->num_triangles; i++) {
        Triangle t = triangulation->triangles[i];

        Edge edges[3] = {
            {t.p1, t.p2},
            {t.p2, t.p3},
            {t.p3, t.p1}
        };

        for(int j = 0; j < 3; j++) {

            if (!graph_has_edge(graph, edges[j])) {
                double weight = calculate_edge_weight(triangulation, edges[j]);
                if(graph_add_edge(graph, edges[j], weight) == -1) {
                    graph_free(graph);
                    return -1;
                }
            }
        }
    }

    return 1;
};

void graph_free(Graph* graph) {
    if (graph->edges != NULL) {
        free(graph->edges);
        graph->edges = NULL;
    }
    graph->num_edges = 0;
    graph->capacity = 0;
}