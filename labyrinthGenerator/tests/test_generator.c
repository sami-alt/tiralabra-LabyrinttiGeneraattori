#include "unity.h"
#include "../src/generator.h"
#include "../src/render.h"

#include <stdlib.h>
#include <string.h>

/*
    Floodf fill aputaja testi funktioita varten.
*/

static int every_room_reachable(char **grid, int width, int height){
    int total_cells = width * height;
    int *visited = calloc((size_t)total_cells, sizeof(int));
    int *queue = malloc((size_t)total_cells * sizeof(int));
    if (visited == NULL || queue == NULL){
        free(visited);
        free(queue);
        return -1;
    }

    int start_cell = -1;
    for (int i = 0; i < total_cells; i++){
        int x = i % width;
        int y = i / width;
        if (grid[y][x] == MAZE_ROOM){
            start_cell = i;
            break;
        }
    }

    if (start_cell < 0){
        free(visited);
        free(queue);
        return 1;
    }
    
    int head = 0;
    int tail = 0;
    queue[tail++] = start_cell;
    visited[start_cell] = 1;

    while(head < tail){
        int cell = queue[head++];
        int x = cell % width;
        int y = cell / width;


        int neighbour_x[4] = {x -1, x + 1, x, x};
        int neighbour_y[4] = {y, y, y - 1, y + 1};
       
        for (int i = 0; i < 4; i++){
            int nx = neighbour_x[i];
            int ny = neighbour_y[i];
            if (nx < 0 || nx >= width || ny < 0 || ny >= height)
                continue;


            int neighbour_cell = ny * width + nx;
            if (visited[neighbour_cell])
                continue;
            if (grid [ny][nx] == MAZE_WALL)
                continue;

            visited[neighbour_cell] = 1;
            queue[tail++] = neighbour_cell;

        }
    }

    int all_rooms_reached = 1;
    for (int i = 0; i < total_cells; i++){
        if (grid[i / width][i % width] == MAZE_ROOM && !visited[i]){
            all_rooms_reached = 0;
            break;
        }
    }

    free(visited);
    free(queue);
    return all_rooms_reached;
}


void test_pipeline_produces_grid_of_requested_size(void){
    GeneratorOptions options = {
        .num_rooms = 10,
        .width = 60,
        .height = 35,
        .min_room_distance = 5,
        .seed = 42
    };

    char **grid = NULL;
    int result = generate_labyrinth(&options, &grid);
    TEST_ASSERT_EQUAL_INT(1, result);
    TEST_ASSERT_NOT_NULL(grid);

    int room_count = 0;
    for (int i = 0; i < options.height; i++){
        for (int j = 0; j < options.width; j++){
            char c = grid[i][j];
            TEST_ASSERT_TRUE(c == MAZE_WALL || c == MAZE_ROOM || c == MAZE_FLOOR);
            if (c == MAZE_ROOM)
                room_count++;
        }
    }

    TEST_ASSERT_EQUAL_INT(options.num_rooms, room_count);
    free_render_grid(grid, options.height);
}

void test_pipeline_all_rooms_reachable(void){
    GeneratorOptions options = {
        .num_rooms = 15,
        .width = 50,
        .height = 30,
        .min_room_distance = 4,
        .seed = 1234
    };

    char **grid = NULL;
    int result = generate_labyrinth(&options, &grid);
    TEST_ASSERT_EQUAL_INT(1, result);
    TEST_ASSERT_NOT_NULL(grid);

    int reachable = every_room_reachable(grid, options.width, options.height);
    TEST_ASSERT_EQUAL_INT(1, reachable);

    free_render_grid(grid, options.height);
}

void test_pipeline_deterministic_for_same_seed(void){
    GeneratorOptions options = {
        .num_rooms = 12,
        .width = 40,
        .height = 25,
        .min_room_distance = 4,
        .seed = 5678
    };

    char **grid1 = NULL;
    char **grid2 = NULL;

    int result1 = generate_labyrinth(&options, &grid1);
    int result2 = generate_labyrinth(&options, &grid2);

    TEST_ASSERT_EQUAL_INT(1, result1);
    TEST_ASSERT_EQUAL_INT(1, result2);
    TEST_ASSERT_NOT_NULL(grid1);
    TEST_ASSERT_NOT_NULL(grid2);

    for (int i = 0; i < options.height; i++){
        TEST_ASSERT_EQUAL_INT(0, memcmp(grid1[i], grid2[i], (size_t)options.width));
    }

    free_render_grid(grid1, options.height);
    free_render_grid(grid2, options.height);
}

void test_pipeline_different_seeds_produce_different_grids(void){
    GeneratorOptions options1 = {
        .num_rooms = 12,
        .width = 40,
        .height = 25,
        .min_room_distance = 4,
        .seed = 1
    };

    GeneratorOptions options2 = {
        .num_rooms = 12,
        .width = 40,
        .height = 25,
        .min_room_distance = 4,
        .seed = 2
    };

    char **grid1 = NULL;
    char **grid2 = NULL;

    int result1 = generate_labyrinth(&options1, &grid1);
    int result2 = generate_labyrinth(&options2, &grid2);

    TEST_ASSERT_EQUAL_INT(1, result1);
    TEST_ASSERT_EQUAL_INT(1, result2);
    TEST_ASSERT_NOT_NULL(grid1);
    TEST_ASSERT_NOT_NULL(grid2);

    int grids_are_different = 0;
    for (int i = 0; i < options1.height; i++){
        if (memcmp(grid1[i], grid2[i], (size_t)options1.width) != 0){
            grids_are_different = 1;
            break;
        }
    }

    TEST_ASSERT_EQUAL_INT(1, grids_are_different);

    free_render_grid(grid1, options1.height);
    free_render_grid(grid2, options2.height);
}


void test_pipeline_rejects_null_options(void){
    char **grid = NULL;
    int result = generate_labyrinth(NULL, &grid);
    TEST_ASSERT_EQUAL_INT(-1, result);
    TEST_ASSERT_NULL(grid);
}


void test_pipeline_rejects_too_few_rooms(void){
    GeneratorOptions one_room = {
        .num_rooms = 1,
        .width = 20,
        .height = 22,
        .min_room_distance = 0,
        .seed = 1
    };

    GeneratorOptions two_rooms = {
        .num_rooms = 2,
        .width = 20,
        .height = 22,
        .min_room_distance = 0,
        .seed = 1
    };

    char **grid = NULL;

    int result1 = generate_labyrinth(&one_room, NULL);
    TEST_ASSERT_EQUAL_INT(-1, result1);
    int result2 = generate_labyrinth(&two_rooms, NULL);
    TEST_ASSERT_EQUAL_INT(-1, result2);

    TEST_ASSERT_NULL(grid);
}


void test_pipeline_rejects_impossible_minimum_distance(void){
    GeneratorOptions options = {
        .num_rooms = 5,
        .width = 20,
        .height = 20,
        .min_room_distance = 20,
        .seed = 1
    };

    char **grid = NULL;
    int result = generate_labyrinth(&options, &grid);
    TEST_ASSERT_EQUAL_INT(-1, result);
    TEST_ASSERT_NULL(grid);
}

void test_pipeline_rejects_negative_dimesions(void){
    GeneratorOptions negative_width = {
        .num_rooms = 5,
        .width = -10,
        .height = 20,
        .min_room_distance = 20,
        .seed = 1
    };

    GeneratorOptions negative_height = {
        .num_rooms = 5,
        .width = 10,
        .height = -20,
        .min_room_distance = 20,
        .seed = 1
    };

    char **grid = NULL;
    int result1 = generate_labyrinth(&negative_width, &grid);
    TEST_ASSERT_EQUAL_INT(-1, result1);
    TEST_ASSERT_NULL(grid);

    int result2 = generate_labyrinth(&negative_height, &grid);
    TEST_ASSERT_EQUAL_INT(-1, result2);
    TEST_ASSERT_NULL(grid);

}

void test_pipeline_minimal_viable_input(void){

    GeneratorOptions options = {
        .num_rooms = 3,
        .width = 20,
        .height = 15,
        .min_room_distance = 2,
        .seed = 99
    };

    char **grid = NULL;
    int result = generate_labyrinth(&options, &grid);
    TEST_ASSERT_EQUAL_INT(1, result);
    int room_count = 0;
    for (int i = 0; i < options.height; i++){
        for (int j = 0; j < options.width; j++){
            char c = grid[i][j];
            TEST_ASSERT_TRUE(c == MAZE_WALL || c == MAZE_ROOM || c == MAZE_FLOOR);
            if (c == MAZE_ROOM)
                room_count++;
        }
    }
    TEST_ASSERT_EQUAL_INT(options.num_rooms, room_count);
    int reachable = every_room_reachable(grid, options.width, options.height);
    TEST_ASSERT_EQUAL_INT(1, reachable);    

    free_render_grid(grid, options.height);
}




/*
    for posible tests for memory leaks 
    void test_pipeline_repeated_runs_do_not_leak(void) {

    for (unsigned int seed = 1; seed <= 10; seed++) {
        GeneratorOptions options = { 15, 40, 30, 3, seed };
        char **grid = NULL;
        TEST_ASSERT_EQUAL_INT(1, generate_labyrinth(&options, &grid));
        TEST_ASSERT_NOT_NULL(grid);
        free_render_grid(grid, options.height);
    }
}

*/