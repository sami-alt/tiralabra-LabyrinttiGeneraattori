#ifndef ROOMS_H
#define ROOMS_H

#include "point.h"

int place_rooms(int num_rooms,
                    int width,
                    int height,
                    int minimum_distance_between_rooms,
                    unsigned int seed,
                    Point** rooms
);


#endif // ROOMS_H