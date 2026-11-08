#include "triangulation.h"
#include <float.h>
#include <math.h>
#include <stdio.h> //debugging purposes, can be removed later

void triangulation_init(Triangulation *triangulation) {
    triangulation->points = NULL;
    triangulation->num_points = 0;
    triangulation->points_capacity = 0;

    triangulation->triangles = NULL;
    triangulation->num_triangles = 0;
    triangulation->triangles_capacity = 0;
}

/*
    selitä triangulaatio
*/

int triangulation_add_point(Triangulation *triangulation, Point point){
    if(triangulation->num_points == triangulation->points_capacity){
        int new_capacity = triangulation->points_capacity == 0
        ? 4 
        : triangulation->points_capacity * 2;

        Point *new_points = realloc(triangulation->points, new_capacity * sizeof(Point));
        if (new_points == NULL){
            return -1; // Handle memory allocation failure
        }
        triangulation->points = new_points;
        triangulation->points_capacity = new_capacity;
    }

    int index = triangulation->num_points;
    triangulation->points[index] = point;
    triangulation->num_points++;

    return index;
}

/*
    lisätään kolmio triangulaation, tämää voidaan myöhemmin poistaa jos se todetaan huonoksi.
*/

void triangulation_add_triangle(Triangulation * triangulation, Triangle triangle){
    if(triangulation->num_triangles == triangulation->triangles_capacity){
        int new_capacity = triangulation->triangles_capacity == 0
        ? 4 
        : triangulation->triangles_capacity * 2;

        Triangle *new_triangles = realloc(triangulation->triangles, new_capacity * sizeof(Triangle));
        if (new_triangles == NULL){
            return; // Handle memory allocation failure
        }
        triangulation->triangles = new_triangles;
        triangulation->triangles_capacity = new_capacity;
    }

    triangulation->triangles[triangulation->num_triangles] = triangle;
    triangulation->num_triangles++;
}

/*
    Luon kaikkien pisteiden ympärille ison kolmion joka varmistaa että kaikki pisteet ovat sen sisällä, delaynay trinagulaatiota rakentuun tämän kolmion pisteiden sisään. 
    kolmion pisteet poistetaan trinagulaation valmistutta
*/

int triangulation_create_super_triangle(Triangulation *triangulation) {
    if (triangulation->num_points < 3) {
        return 0; // Not enough points to create a super triangle
    }

    double min_x = DBL_MAX, min_y = DBL_MAX;
    double max_x = -DBL_MAX, max_y = -DBL_MAX;

    for (int i = 0; i < triangulation->num_points; i++){
        Point p = triangulation->points[i];
        if (p.x < min_x) min_x = p.x;
        if (p.y < min_y) min_y = p.y;
        if (p.x > max_x) max_x = p.x;
        if (p.y > max_y) max_y = p.y;
    }

    double width = max_x - min_x;
    double height = max_y - min_y;

    double size = fmax(width, height) * 10; 

    if (size == 0.0)
        return 0; // Avoid creating a super triangle if all points are the same

    double mid_x = (min_x + max_x) / 2.0;
    double mid_y = (min_y + max_y) / 2.0;


    //Factor of 20 is used to ensure that the super triangle is large enough to encompass all points, even if they are very close together. This factor can be adjusted based on the specific requirements of the triangulation algorithm being used.
    int a = triangulation_add_point(triangulation, create_point(mid_x - 20 * size, mid_y - size));
    int b = triangulation_add_point(triangulation, create_point(mid_x, mid_y + 20 * size));
    int c = triangulation_add_point(triangulation, create_point(mid_x + 20 * size, mid_y - size));

    if (a < 0 || b < 0 || c < 0) {
        return 0; // Failed to add points
    }

    triangulation_add_triangle(triangulation, create_triangle(a, b, c));

    return 1;
}

/*
    POistaa kolmion jos se todetaan huonoksi.
*/

void triangulation_remove_triangle(Triangulation *triangulation, int index) {
    if (index < 0 || index >= triangulation->num_triangles) {
        return; // Invalid index
    }

    triangulation->triangles[index] = triangulation->triangles[triangulation->num_triangles - 1];
    triangulation->num_triangles--;
}

void triangulation_remove_bad_triangles(Triangulation * triangulation, Point point, EdgeList *boundary) {
    int i = 0;
    while (i < triangulation->num_triangles) {
        Triangle triangle = triangulation->triangles[i];
        if (point_in_circumcicle(triangle, triangulation->points, point)) {
            edge_list_toggle(boundary, create_edge(triangle.p1, triangle.p2));
            edge_list_toggle(boundary, create_edge(triangle.p2, triangle.p3));
            edge_list_toggle(boundary, create_edge(triangle.p3, triangle.p1));

            triangulation_remove_triangle(triangulation, i);
            
        } else {
            i++;
        }
    }
}

void triangulation_create_new_triangles(Triangulation *triangulation, EdgeList *boundary, int point_index) {
    for (int i = 0; i < boundary->size; i++){
        Edge edge = boundary->edges[i];
        Triangle new_triangle = create_triangle(edge.p1, edge.p2, point_index);

        if (get_triangle_orientation(new_triangle, triangulation->points) != COLLINEAR){
            triangulation_add_triangle(triangulation, new_triangle);
        } 
    }
}

int bowyer_watson(Triangulation *triangulation){

    //debug
    //printf("Point count %d\n", triangulation->num_points);
    //printf("triangle count %d\n", triangulation->num_triangles);


    if (triangulation->num_points < 3 || triangulation->num_triangles != 0) {
        return 0; // Not enough points or no triangles to process
    }
    
    int original_point_count = triangulation->num_points;
    
    //printf("Create super triangle\n");
    if (!triangulation_create_super_triangle(triangulation)) {
    
        return 0; // Failed to create super triangle
    }
    //printf("Super triangle created\n");

    for (int i = 0; i < original_point_count; i++){
        Point point = triangulation->points[i];
        EdgeList boundary;
        init_edge_list(&boundary);

        triangulation_remove_bad_triangles(triangulation, point, &boundary);
        triangulation_create_new_triangles(triangulation, &boundary, i);

        free_edge_list(&boundary);
    }

    int i = 0;
    while(i < triangulation->num_triangles){
        Triangle triangle = triangulation->triangles[i];

        if ( triangle.p1 >= original_point_count ||
             triangle.p2 >= original_point_count || 
             triangle.p3 >= original_point_count){
            triangulation_remove_triangle(triangulation, i);
        } else {
            i++;
        }
    }
    triangulation->num_points = original_point_count; // Reset the number of points to the original count
    return 1;
}

void triangulation_free(Triangulation *triangulation) {
    free(triangulation->points);
    free(triangulation->triangles);

    triangulation->points = NULL;
    triangulation->num_points = 0;
    triangulation->points_capacity = 0;

    triangulation->triangles = NULL;
    triangulation->num_triangles = 0;
    triangulation->triangles_capacity = 0;

}