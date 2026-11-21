#include "unity.h"
#include "../src/rooms.h"

#include <stdlib.h>
#include <math.h>

void test_place_rooms_null_output_pointer(void) {
    int result = place_rooms(5, 10, 10, 2, 12345, NULL);
    TEST_ASSERT_EQUAL_INT(-1, result);
}

void test_place_rooms_invalid_arguments(void){
    Point *rooms = NULL;

    TEST_ASSERT_EQUAL_INT(-1, place_rooms(0,  100, 100, 10, 1, &rooms));
    TEST_ASSERT_EQUAL_INT(-1, place_rooms(-1, 100, 100, 10, 1, &rooms));
    TEST_ASSERT_EQUAL_INT(-1, place_rooms(5,  0,   100, 10, 1, &rooms));
    TEST_ASSERT_EQUAL_INT(-1, place_rooms(5,  100, 0,   10, 1, &rooms));
    TEST_ASSERT_EQUAL_INT(-1, place_rooms(5,  100, 100, -1, 1, &rooms));
    
    TEST_ASSERT_NULL(rooms);

}

void test_plance_rooms_impossible_minimum_distance(void){
    Point *rooms = NULL;

    TEST_ASSERT_EQUAL_INT(-1, place_rooms(5,  100, 100, 100, 1, &rooms));
    TEST_ASSERT_EQUAL_INT(-1, place_rooms(5,  100, 100, 200, 1, &rooms));
    
    TEST_ASSERT_NULL(rooms);
}

void test_place_too_many_rooms(void){
    Point *rooms = NULL;

    TEST_ASSERT_EQUAL_INT(-1, place_rooms(1000,  10, 10, 1, 1, &rooms));
    
    TEST_ASSERT_NULL(rooms);
}

void test_place_single_room(void){
    Point *rooms = NULL;

    TEST_ASSERT_EQUAL_INT(1, place_rooms(1, 100, 100, 0, 7, &rooms));
    TEST_ASSERT_NOT_NULL(rooms);
    TEST_ASSERT_TRUE(rooms[0].x >= 0 && rooms[0].x < 100);
    TEST_ASSERT_TRUE(rooms[0].y >= 0 && rooms[0].y < 100);

    free(rooms);
}

void test_place_rooms_all_in_bounds(void){
    int const num_rooms = 15;
    int const min_distance = 20;
    Point *rooms = NULL;

    TEST_ASSERT_EQUAL_INT(1 , place_rooms(num_rooms, 100, 300, min_distance, 999, &rooms));

    double min_distance_squared = (double)(min_distance * min_distance);

    for (int i = 0; i < num_rooms; i++){
        for (int j = i + 1; j < num_rooms; j++){
            double delta_x = rooms[i].x - rooms[j].x;
            double delta_y = rooms[i].y - rooms[j].y;
            double distance_squared = delta_x * delta_x + delta_y * delta_y;

            TEST_ASSERT_TRUE(distance_squared >= min_distance_squared);
        }

    }
    free(rooms);
}

void test_place_rooms_with_deterministic_for_same_seed(void){
    Point *rooms1 = NULL;
    Point *rooms2 = NULL;

    TEST_ASSERT_EQUAL_INT(1, place_rooms(10, 200, 200, 5, 12345, &rooms1));
    TEST_ASSERT_EQUAL_INT(1, place_rooms(10, 200, 200, 5, 12345, &rooms2));

    for (int i = 0; i < 5; i++){
        TEST_ASSERT_EQUAL_INT(rooms1[i].x, rooms2[i].x);
        TEST_ASSERT_EQUAL_INT(rooms1[i].y, rooms2[i].y);
    }

    free(rooms1);
    free(rooms2);
}


void test_place_rooms_with_different_seeds(void){
    Point *rooms1 = NULL;
    Point *rooms2 = NULL;

    TEST_ASSERT_EQUAL_INT(1, place_rooms(10, 200, 200, 5, 1, &rooms1));
    TEST_ASSERT_EQUAL_INT(1, place_rooms(10, 200, 200, 5, 2, &rooms2));

    int identical_count = 0;
    for (int i = 0; i < 10; i++){
        if (rooms1[i].x == rooms2[i].x && rooms1[i].y == rooms2[i].y){
            identical_count++;
        }
    }

    TEST_ASSERT_TRUE(identical_count < 10);

    free(rooms1);
    free(rooms2);
}

void test_place_rooms_with_minimum_distance_allows_any_position(void){

    Point *rooms = NULL;

    TEST_ASSERT_EQUAL_INT(1, place_rooms(50, 500, 500, 0, 3, &rooms));
    TEST_ASSERT_NOT_NULL(rooms);
    free(rooms);
}