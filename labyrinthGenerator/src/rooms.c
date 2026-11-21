#include "rooms.h"

#include <math.h>
#include <stdlib.h>
#include <stdint.h>


//hylkää siemenluvu jolla xorshift generaattori ei toimi kunnolla
#define FALLBACK_SEED 2463534242u

//kuinka monta kertaa yritetään sijoittaa huonetta ennen kuin luovutetaan
#define MAX_PLACEMENT_ATTEMPTS 1000


// Xorshift32 satunnaislukugeneraattori joka takaa deterministisen satunnaisuuden annetulla siemenluvulla.
static uint32_t xorshift32(uint32_t* state) {
    uint32_t value = *state;
    value ^= value << 13;
    value ^= value >> 17;
    value ^= value << 5;
    *state = value;
    return value;
}

// Palauttaa satunnaisen kokonaisluvun välillä [0, upper_bound) käyttäen xorshift32 generaattoria.
static int random_int_below(uint32_t* state, int upper_bound) {
    uint32_t bound = (uint32_t)upper_bound;
    uint32_t threshold = (uint32_t)(-bound) % bound;  
    uint32_t raw;
    do {
        raw = xorshift32(state);
    } while (raw < threshold);
    return (int)(raw % bound);
}

static int is_far_enough_from_others(Point posible_room, const Point *existing_rooms, int esisting_room_count, double minimum_distance) {
    double minimum_distance_squared = minimum_distance * minimum_distance;
    for (int i = 0; i < esisting_room_count; i++) {
        double delta_x = posible_room.x - existing_rooms[i].x;
        double delta_y = posible_room.y - existing_rooms[i].y;
        if (delta_x * delta_x + delta_y * delta_y < minimum_distance_squared) {
            return 0; 
        }
    }
    return 1;
}

int place_rooms(int num_rooms, int width, int height, int minimum_distance_between_rooms, unsigned int seed, Point** rooms_out){
    if (rooms_out == NULL)
        return -1;

    *rooms_out = NULL;

    if (num_rooms <= 0 || width <= 0 || height <= 0 || 
        minimum_distance_between_rooms < 0){

            return -1;
        }

        if (minimum_distance_between_rooms >= width ||
            minimum_distance_between_rooms >= height){

                return -1;
            }

    Point *rooms = malloc(num_rooms * sizeof(Point));
    if (rooms == NULL)
        return -1;  

    uint32_t rng_state = (seed == 0u) ? FALLBACK_SEED : (uint32_t)seed;
    int placed_rooms = 0;

    while (placed_rooms < num_rooms){
        int placement_in_this_round = 0;

        for (int place_attempts = 0; place_attempts < MAX_PLACEMENT_ATTEMPTS; place_attempts++){
            Point posible_room = create_point((double)random_int_below(&rng_state, width), (double)random_int_below(&rng_state, height));

            if (is_far_enough_from_others(posible_room, rooms, placed_rooms, (double)minimum_distance_between_rooms)){
                rooms[placed_rooms] = posible_room;
                placed_rooms++;
                placement_in_this_round = 1;
                break; 
            }
        }
        if (!placement_in_this_round) {
            free(rooms);
            return -1;
        }
    }

    *rooms_out = rooms;
    return 1;
}
