#include <stdlib.h>
#include "edge_list.h"

void init_edge_list(EdgeList *list) {
    list->edges = NULL;
    list->size = 0;
    list->capacity = 0;
}

void add_edge_list(EdgeList *list, Edge edge){
    if (list->size == list->capacity){
        int new_capacity = list->capacity == 0 
        ? 4 : list->capacity * 2;

        Edge *new_edges = realloc(list->edges, new_capacity * sizeof(Edge));
        if (new_edges == NULL){
            return; // Handle memory allocation failure
        }
        list->edges = new_edges;
        list->capacity = new_capacity;
    }
    list->edges[list->size] = edge;
    list->size++;
}

/*
    Funktion lisää poistaa kolmion reunan reunojen listasta sen mukaan todetaanko kolmiot hyviksi vai huonoiksi delaunay triangulaatioon.
*/
void edge_list_toggle(EdgeList *list,  Edge edge){
    for (int i = 0; i < list->size; i++){
        if (edge_equals(list->edges[i], edge)){
            list->edges[i] = list->edges[list->size - 1];
            list->size--;
            return;
        }
    }
    add_edge_list(list, edge);
}

void free_edge_list(EdgeList *list) {
    free(list->edges);
    list->edges = NULL;
    list->size = 0;
    list->capacity = 0;
}