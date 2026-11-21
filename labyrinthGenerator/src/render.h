#ifndef RENDER_H
#define RENDER_H

#include "graph.h"
#include "point.h"


int render_maze_ascii(const Point *rooms, int num_rooms, const Graph *mst, int width, int height, char ***output_grid);

void free_render_grid(char **grid, int height);


#define MAZE_WALL '#'
#define MAZE_FLOOR ' '
#define MAZE_ROOM 'O'


#endif // RENDER_H