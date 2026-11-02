#include "labyrinthGenerator.h"


void generateLabyrinth(int rooms, int width, int height, int room_distance, int seed)
{
    // Placeholder for labyrinth generation logic
    printf("Generating labyrinth with %d rooms, width %d, height %d, room distance %d, seed %d\n",
           rooms, width, height, room_distance, seed);
}

int main(int ac, char **av)
{
    if (ac != 6)
    {
        printf("Usage: %s <rooms> <width> <height> <room_distance> <seed>\n", av[0]);
        return 1;
    }
    int rooms = atoi(av[1]);
    int width = atoi(av[2]);
    int height = atoi(av[3]);
    int room_distance = atoi(av[4]);
    int seed = atoi(av[5]);

    if (rooms <= 0 || width <= 0 || height <= 0 || room_distance <= 0 || seed < 0)
    {
        printf("All parameters must be positive integers.\n");
        return 1;
    }
    generateLabyrinth(rooms, width, height, room_distance, seed);
    return 0;
}