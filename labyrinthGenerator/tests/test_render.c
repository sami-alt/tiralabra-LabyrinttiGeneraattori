#include "unity.h"
#include "../src/render.h"

#include <stdlib.h>
#include <string.h>

void test_render_null_arguments(void){
    Point fake_room[] = {create_point(5.0, 5.0)};
    Graph fake_graph;
    graph_init(&fake_graph);
    char **grid = NULL;

    TEST_ASSERT_EQUAL_INT(-1, render_maze_ascii(NULL, 1, &fake_graph, 5, 5, &grid));
    TEST_ASSERT_EQUAL_INT(-1, render_maze_ascii(fake_room, 1, NULL, 5, 5, &grid));
    TEST_ASSERT_EQUAL_INT(-1, render_maze_ascii(fake_room, 1, &fake_graph, 5, 5, NULL));
    TEST_ASSERT_EQUAL_INT(-1, render_maze_ascii(fake_room, 1, &fake_graph, 0, 5, &grid));
    TEST_ASSERT_EQUAL_INT(-1, render_maze_ascii(fake_room, 1, &fake_graph, 5, 0, &grid));
    TEST_ASSERT_NULL(grid);

    graph_free(&fake_graph);

}

void test_render_single_room_no_edges(void){
    Point rooms[] = { create_point(3.0, 3.0) };
    Graph graph;
    graph_init(&graph);
    char **grid = NULL;

    TEST_ASSERT_EQUAL_INT(1, render_maze_ascii(rooms, 1, &graph, 10, 10, &grid));
    TEST_ASSERT_NOT_NULL(grid);


    for (int y = 0; y < 10; y++){
        for (int x = 0; x < 10; x++){
            char expected_char = (x == 3 && y == 3) ? MAZE_ROOM : MAZE_WALL;
            TEST_ASSERT_EQUAL_CHAR(expected_char, grid[y][x]);
        }
    }
    free_render_grid(grid, 10);
    graph_free(&graph);
}

void test_render_room_out_of_bouds(void){

    Point rooms[] = {create_point(50.0, 3.0)};
    Graph graph;
    graph_init(&graph);
    char **grid = NULL;
    TEST_ASSERT_EQUAL_INT(-1, render_maze_ascii(rooms, 1, &graph, 10, 10, &grid));
    TEST_ASSERT_NULL(grid);
    graph_free(&graph);
}

void test_render_two_rooms_horizontal_corridor(void){
    Point rooms[] = {create_point(2.0, 5.0), create_point(7.0, 5.0)};
    Graph graph;
    graph_init(&graph);
    graph_add_edge(&graph,create_edge(0, 1), 5.0);

    char **grid = NULL;

    TEST_ASSERT_EQUAL_INT(1, render_maze_ascii(rooms, 2, &graph, 10, 10, &grid));

    for (int x = 3;  x <= 6; x++){
        TEST_ASSERT_EQUAL_CHAR(MAZE_FLOOR, grid[5][x]);
    }

    TEST_ASSERT_EQUAL_CHAR(MAZE_ROOM, grid[5][2]);
    TEST_ASSERT_EQUAL_CHAR(MAZE_ROOM, grid[5][7]);

    for (int x = 0; x < 10; x++){
        TEST_ASSERT_EQUAL_CHAR(MAZE_WALL, grid[4][x]);
        TEST_ASSERT_EQUAL_CHAR(MAZE_WALL, grid[6][x]);
    }

    free_render_grid(grid, 10);
    graph_free(&graph);

}

void test_render_two_rooms_vertical_corridor(void){
    Point rooms[] = {create_point(5.0, 2.0), create_point(5.0, 7.0)};
    Graph graph;
    graph_init(&graph);
    graph_add_edge(&graph,create_edge(0, 1), 5.0);

    char **grid = NULL;

    TEST_ASSERT_EQUAL_INT(1, render_maze_ascii(rooms, 2, &graph, 10, 10, &grid));

    for (int y = 3;  y <= 6; y++){
        TEST_ASSERT_EQUAL_CHAR(MAZE_FLOOR, grid[y][5]);
    }

    TEST_ASSERT_EQUAL_CHAR(MAZE_ROOM, grid[2][5]);
    TEST_ASSERT_EQUAL_CHAR(MAZE_ROOM, grid[7][5]);

    for (int x = 0; x < 10; x++){
        TEST_ASSERT_EQUAL_CHAR(MAZE_WALL, grid[1][x]);
        TEST_ASSERT_EQUAL_CHAR(MAZE_WALL, grid[8][x]);
    }

    free_render_grid(grid, 10);
    graph_free(&graph);

}

void test_render_two_rooms_diagonal_l_corridor(void){

    Point rooms[] = {create_point(2.0, 2.0),  create_point(7.0, 7.0)};

    Graph graph;
    graph_init(&graph);
    graph_add_edge(&graph,create_edge(0, 1), 7.0);

    char **grid = NULL;

    TEST_ASSERT_EQUAL_INT(1, render_maze_ascii(rooms, 2, &graph, 10, 10, &grid));

    for (int x = 3; x <= 6; x++){
        TEST_ASSERT_EQUAL_CHAR(MAZE_FLOOR, grid[2][x]);
    }

    for (int y = 3; y <= 6; y++){
        TEST_ASSERT_EQUAL_CHAR(MAZE_FLOOR, grid[y][7]);
    }

    TEST_ASSERT_EQUAL_CHAR(MAZE_FLOOR, grid[2][7]);

    TEST_ASSERT_EQUAL_CHAR(MAZE_ROOM, grid[2][2]);
    TEST_ASSERT_EQUAL_CHAR(MAZE_ROOM, grid[7][7]);

    free_render_grid(grid, 10);
    graph_free(&graph);

}

void test_render_three_rooms_connected(void){
    Point rooms[] = {
        create_point(1,1),
        create_point(5,5),
        create_point(8,2)
    };

    Graph graph;
    graph_init(&graph);
    graph_add_edge(&graph, create_edge(0, 1), 0);
    graph_add_edge(&graph, create_edge(1, 2), 0);


    char **grid = NULL;
    TEST_ASSERT_EQUAL_INT(1, render_maze_ascii(rooms, 3, &graph, 10, 10, &grid));

    TEST_ASSERT_EQUAL_CHAR(MAZE_ROOM, grid[1][1]);
    TEST_ASSERT_EQUAL_CHAR(MAZE_ROOM, grid[5][5]);
    TEST_ASSERT_EQUAL_CHAR(MAZE_ROOM, grid[2][8]);

    free_render_grid(grid, 10);
    graph_free(&graph);
}

void test_render_rejects_edge_with_out_of_range_room_index(void){

    Point rooms[] = {
        create_point(1,1),
        create_point(5,5)
    };

    Graph graph;
    graph_init(&graph);
    graph_add_edge(&graph, create_edge(0, 2), 0); // Invalid edge

    char **grid = NULL;
    TEST_ASSERT_EQUAL_INT(-1, render_maze_ascii(rooms, 2, &graph, 10, 10, &grid));
    TEST_ASSERT_NULL(grid);

    graph_free(&graph);
}

//Testi epäonnistuneelle vapautukselle, ei pitäisi kaatua vaikka grid olisi NULL
void test_free_render_grid_null_safe(void){
    free_render_grid(NULL, 10);
}