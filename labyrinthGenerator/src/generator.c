#include "generator.h"

#include "graph.h"
#include "kruskal.h"
#include "render.h" 
#include "rooms.h"
#include "triangulation.h"

#include <stdlib.h>



static int load_rooms_into_triangulation(Triangulation *triangulation, const Point *rooms, int num_rooms){
    for (int i = 0; i < num_rooms; i++){
        int index = triangulation_add_point(triangulation, rooms[i]);
        if (index == -1){
            return -1;
        }
    } 
    return 1;
}


int generate_labyrinth(const GeneratorOptions *options, char ***output_grid){

    if (output_grid == NULL)
        return -1;
    if (options == NULL)
        return -1; 
    if (options->num_rooms <= 0)
        return -1;
    if (options->width <= 0 || options->height <= 0)
        return -1;
    if (options->min_room_distance < 0)
        return -1;  

    Point *rooms = NULL;
    if (place_rooms(options->num_rooms, 
                    options->width, 
                    options->height, 
                    options->min_room_distance, 
                    options->seed, 
                    &rooms) != 1){
        return -1;
    }
    Triangulation triangulation;
    triangulation_init(&triangulation);
    if (load_rooms_into_triangulation(&triangulation, rooms, options->num_rooms) != 1){
        free(rooms);
        triangulation_free(&triangulation);
        return -1;
    }
    if(bowyer_watson(&triangulation) != 1){
        free(rooms);
        triangulation_free(&triangulation);
        return -1;
    }

    free(rooms);
    rooms = NULL;

    Graph graph;
    graph_init(&graph);
    if (graph_from_triangulation(&graph, &triangulation) != 1){
        triangulation_free(&triangulation);
        return -1;  
    }


    Graph minumum_spanning_tree;
    if (kruskal_minimum_spanning_tree(&graph, options->num_rooms, &minumum_spanning_tree) != 1){
        graph_free(&graph);
        triangulation_free(&triangulation);
        return -1;
    }

    if (minumum_spanning_tree.num_edges != options->num_rooms - 1){
        graph_free(&graph);
        graph_free(&minumum_spanning_tree);
        triangulation_free(&triangulation);
        return -1;
    }

    char **grid = NULL;
    if (render_maze_ascii(triangulation.points, options->num_rooms, &minumum_spanning_tree, options->width, options->height, &grid) != 1){
        graph_free(&graph);
        graph_free(&minumum_spanning_tree);
        triangulation_free(&triangulation);
        return -1;
    }

    *output_grid = grid;
    graph_free(&graph);
    graph_free(&minumum_spanning_tree);
    triangulation_free(&triangulation);
    return 1;
}