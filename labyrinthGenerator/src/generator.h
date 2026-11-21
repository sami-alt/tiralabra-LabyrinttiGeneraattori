#ifndef GENERATOR_H
#define GENERATOR_H

typedef struct GeneratorOptions{
    int num_rooms;
    int width;
    int height;
    int min_room_distance;
    unsigned int seed;
} GeneratorOptions;

int generate_labyrinth(const GeneratorOptions *options, char ***output_grid);

#endif //GENERATOR_H