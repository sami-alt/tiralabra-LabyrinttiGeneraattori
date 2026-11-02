#include "../headers/labyrinthGenerator.h"



Triangulation bowyerWatsonAlgorithm(int rooms, int width, int height, int room_distance, int seed)
{
    //Pseudo-code for Bowyer-Watson algorithm implementation
    /*
    triangulation = create_super_triangle(width, height)
    
    for each point in points:
        bad_triangles = []
        for each triangle in triangulation:
            if point is inside circumcircle of triangle:
                bad_triangles.append(triangle)
        
        polygon = []
        for each triangle in bad_triangles:
            for each edge in triangle:
                if edge is not shared by any other triangle in bad_triangles:
                    polygon.append(edge)
        
        remove bad_triangles from triangulation
        
        for each edge in polygon:
            new_triangle = create_triangle(edge, point)
            triangulation.append(new_triangle)
    
    
    return triangulation;
    */
}