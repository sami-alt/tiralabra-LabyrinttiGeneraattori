#include "render.h"

#include <stdlib.h>

static void horizontal_corridor(char ** grid, int from_x, int to_x, int y) {
    int start = (from_x < to_x) ? from_x : to_x;
    int end = (from_x < to_x) ? to_x : from_x;

    for (int x = start; x <= end; x++) {
        grid[y][x] = MAZE_FLOOR;
    }
}

static void vertical_corridor(char ** grid, int x, int from_y, int to_y) {
    int start = (from_y < to_y) ? from_y : to_y;
    int end = (from_y < to_y) ? to_y : from_y;

    for (int y = start; y <= end; y++) {
        grid[y][x] = MAZE_FLOOR;
    }
}

static void l_shaped_corridor(char **grid, Point from, Point to){
    int corridor_one_start_x = (int)from.x;
    int corridor_one_end_x = (int)to.x;
    int corridor_two_start_y = (int)from.y;
    int corridor_two_end_y = (int)to.y; 

    // Piirretään L-muotoinen käytävä, ensin vaakasuora ja sitten pystysuora
    horizontal_corridor(grid, corridor_one_start_x, corridor_one_end_x, corridor_two_start_y);
    vertical_corridor(grid, corridor_one_end_x, corridor_two_start_y, corridor_two_end_y);

}


int render_maze_ascii(const Point *rooms, int num_rooms, const Graph *mst, int width, int height, char ***output_grid){

    if (output_grid == NULL)
        return -1;

    *output_grid = NULL;

    if(rooms == NULL || mst == NULL)
        return -1;

    if (num_rooms <= 0 || width <= 0 || height <= 0)
        return -1;

    char **grid = malloc(height * sizeof(char*));
    if (grid == NULL)
        return -1;

    for (int y = 0; y < height; y++){
        grid[y] = malloc(width * sizeof(char));
        if (grid[y] == NULL){
            for (int j = 0; j < y; j++){
                free(grid[j]);
            }
            free(grid);
            return -1;
        }
        for (int x = 0; x < width; x++){
            grid[y][x] = MAZE_WALL;
        }

    }

    /*
    Viimeinnen tarkistus enne labyrintin piirtoa, tarkistaa että huoneed eivät ole ulkopuolella labyrintin rajoja. Jos huoneet ovat ulkopuolella, funktio palauttaa -1 ja vapauttaa varatun muistin.
    */
    for (int i = 0; i < num_rooms; i++){
        int room_x = (int)rooms[i].x;
        int room_y = (int)rooms[i].y;
        if (room_x < 0 || room_x >= width || room_y < 0 || room_y >= height){
            free_render_grid(grid, height);
            return -1;
        }
    }


    //Käytävät mst kaarien mukaan
    for (int i = 0; i < mst->num_edges; i++){
        int room_a_index = mst->edges[i].edge.p1;
        int room_b_index = mst->edges[i].edge.p2;
        
        if(room_a_index < 0 || room_a_index >= num_rooms || 
           room_b_index < 0 || room_b_index >= num_rooms){
            free_render_grid(grid, height);
            return -1;
        }

        l_shaped_corridor(grid, rooms[room_a_index], rooms[room_b_index]);

    }

    //Piirretään huoneet
    for (int i = 0; i < num_rooms; i++){
        int room_x = (int)rooms[i].x;
        int room_y = (int)rooms[i].y;
        grid[room_y][room_x] = MAZE_ROOM;
    }

    *output_grid = grid;
    return 1;
}


void free_render_grid(char **grid, int height){
    if (grid == NULL)
        return;

    for (int y = 0; y < height; y++){
        free(grid[y]);
    }
    free(grid);
}