#include "kruskal.h"

int compare_graph_edges(const void *edge1, const void *edge2) {
    const GraphEdge *e1 = (const GraphEdge *)edge1;
    const GraphEdge *e2 = (const GraphEdge *)edge2;

    if (e1->weight < e2->weight) {
        return -1;
    } else if (e1->weight > e2->weight) {
        return 1;
    } else {
        return 0;
    }
}

int kruskal_minimum_spanning_tree(const Graph *graph, int num_vertices, Graph *mst){

    if (mst == NULL) {
        return -1; 
    }


    graph_init(mst);


    if (graph == NULL || num_vertices <= 0) {
        return -1; 
    }

    if ( num_vertices == 1) {
        return 1; 
    }

    if (graph->num_edges == 0) {
        return -1; 
    }

    if (graph->num_edges < 0)
    return -1;

    if (graph->edges == NULL)
    return -1;
    
    int num_edges_copy = graph->num_edges;

    GraphEdge *sorted_edges = malloc(num_edges_copy * sizeof(GraphEdge));
    if (sorted_edges == NULL) {
        graph_free(mst);
        return -1; 
    }


    for (int i = 0; i < num_edges_copy; i++) {
        sorted_edges[i] = graph->edges[i];
    }


    qsort(sorted_edges, num_edges_copy, sizeof(GraphEdge), compare_graph_edges);

    UnionFind uf;
    if (union_find_init(&uf, num_vertices) != 1) {
        free(sorted_edges);
        graph_free(mst);
        return -1; 
    }



    int edges_in_tree = 0;
    for (int i = 0; i < num_edges_copy && edges_in_tree < num_vertices - 1; i++) {
        Edge curr_edge = sorted_edges[i].edge;
        int vertex1 = curr_edge.p1;
        int vertex2 = curr_edge.p2;
        
        if (vertex1 < 0 || vertex1 >= num_vertices ||
            vertex2 < 0 || vertex2 >= num_vertices) {
            continue;
        }


        int res = union_find_union(&uf, vertex1, vertex2);
        if (res == 1) { 
            if (graph_add_edge(mst, curr_edge, sorted_edges[i].weight) != 1) {
                free(sorted_edges);
                union_find_free(&uf);
                graph_free(mst);
                return -1; 
            }
            edges_in_tree++;    
        }
        if (res == -1) {
            free(sorted_edges);
            union_find_free(&uf);
            graph_free(mst);
            return -1; 
        }

    }
    
        free(sorted_edges);
        union_find_free(&uf);
    
    if (edges_in_tree != num_vertices - 1) {
        graph_free(mst);
        return -1;
    }




    return 1;
}