#include "generator.h"
#include "render.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


static void print_usage(const char *program_name){
    fprintf(stderr, 
        "Usage: %s [num_rooms] [width] [height] [minumum_room_distance] [seed]\n"
        "Defaults: 20 rooms, 60x30 grid, minimum room distance of 5, and  seed 42.\n"
        , program_name);

}

static int parse_positive_int(const char *str, int *out){
    char *end = NULL;
    long value = strtol(str, &end, 10);
    if (end == str || *end != '\0' || value <= 0 || value > 100000){
        return -1;
    }
    *out = (int)value;
    return 1;
}

int main(int argc, char **argv){
    GeneratorOptions options = {
        .num_rooms = 20,
        .width = 60,
        .height = 30,
        .min_room_distance = 5,
        .seed = 42
    }; 

    if (argc == 2 && strcmp(argv[1], "--help") == 0){
        print_usage(argv[0]);
        return 0;
    }

    if (argc > 6){
        print_usage(argv[0]);
        return 1;
    }


    if (argc >= 2 && parse_positive_int(argv[1], &options.num_rooms) != 1){
        print_usage(argv[0]);
        return 1;
    }

    if (argc >= 3 && parse_positive_int(argv[2], &options.width) != 1){
        print_usage(argv[0]);
        return 1;
    }

    if (argc >= 4 && parse_positive_int(argv[3], &options.height) != 1){
        print_usage(argv[0]);
        return 1;
    }

    if (argc >= 5 && parse_positive_int(argv[4], &options.min_room_distance) != 1){
        print_usage(argv[0]);
        return 1;
    }

    if (argc >= 6){
        char *end = NULL;
        unsigned long seed = strtoul(argv[5], &end, 10);
        if (end == argv[5] || *end != '\0'){
            print_usage(argv[0]);
            return 1;
        }
        options.seed = (unsigned int)seed;
    }

    char **grid = NULL;
    if (generate_labyrinth(&options, &grid) != 1){
        fprintf(stderr, "Error: Failed to generate labyrinth.\n");
        return 1;
    }

    for (int i = 0; i < options.height; i++){
        fwrite(grid[i], 1, (size_t)options.width, stdout);
        putchar('\n');
    }

    free_render_grid(grid, options.height);

    return 0;
}