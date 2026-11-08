#include "unity.h"
#include "../src/triangulation.h"

void test_triangulation_init(void){
    Triangulation triangulation;
    triangulation_init(&triangulation);

    TEST_ASSERT_NULL(triangulation.points);
    TEST_ASSERT_EQUAL_INT(0, triangulation.num_points);
    TEST_ASSERT_EQUAL_INT(0, triangulation.points_capacity);

    TEST_ASSERT_NULL(triangulation.triangles);
    TEST_ASSERT_EQUAL_INT(0, triangulation.num_triangles);
    TEST_ASSERT_EQUAL_INT(0, triangulation.triangles_capacity);
}

void test_triangulation_add_point(void){
    Triangulation triangulation;
    triangulation_init(&triangulation);

    int index = triangulation_add_point(&triangulation, create_point(2.0, 3.0));

    TEST_ASSERT_EQUAL_INT(0, index);
    TEST_ASSERT_EQUAL_INT(1, triangulation.num_points);
    TEST_ASSERT_EQUAL_INT(4, triangulation.points_capacity);
    TEST_ASSERT_EQUAL_DOUBLE(2.0, triangulation.points[0].x);
    TEST_ASSERT_EQUAL_DOUBLE(3.0, triangulation.points[0].y);

    triangulation_free(&triangulation);
}

void test_triangulation_add_multiple_point(void){
    Triangulation triangulation;
    triangulation_init(&triangulation);

    for(int i = 0; i < 5; i++){
        int index = triangulation_add_point(&triangulation, create_point(i , i));
        TEST_ASSERT_EQUAL_INT(i, index);
    }

    TEST_ASSERT_EQUAL_INT(5, triangulation.num_points);
    TEST_ASSERT_EQUAL_INT(8, triangulation.points_capacity);

    for(int i = 0; i < 5; i++){
        TEST_ASSERT_EQUAL_DOUBLE(i, triangulation.points[i].x);
        TEST_ASSERT_EQUAL_DOUBLE(i, triangulation.points[i].y);
    }

    triangulation_free(&triangulation);

}

void test_triangulation_add_triangle(void){
    Triangulation triangulation;
    triangulation_init(&triangulation);

    Triangle triangle = create_triangle(0, 1, 2);
    triangulation_add_triangle(&triangulation, triangle);

    TEST_ASSERT_EQUAL_INT(1, triangulation.num_triangles);
    TEST_ASSERT_EQUAL_INT(4, triangulation.triangles_capacity);

    TEST_ASSERT_EQUAL_INT(0, triangulation.triangles[0].p1);
    TEST_ASSERT_EQUAL_INT(1, triangulation.triangles[0].p2);
    TEST_ASSERT_EQUAL_INT(2, triangulation.triangles[0].p3);

    triangulation_free(&triangulation);
}

void test_triangulation_remove_triangle(void){

    Triangulation triangulation;
    triangulation_init(&triangulation);

    Triangle triangle1 = create_triangle(0, 1, 2);
    Triangle triangle2 = create_triangle(3, 4, 5);
    triangulation_add_triangle(&triangulation, triangle1);
    triangulation_add_triangle(&triangulation, triangle2);

    TEST_ASSERT_EQUAL_INT(2, triangulation.num_triangles);

    triangulation_remove_triangle(&triangulation, 0);

    TEST_ASSERT_EQUAL_INT(1, triangulation.num_triangles);
    TEST_ASSERT_EQUAL_INT(3, triangulation.triangles[0].p1);
    TEST_ASSERT_EQUAL_INT(4, triangulation.triangles[0].p2);
    TEST_ASSERT_EQUAL_INT(5, triangulation.triangles[0].p3);

    triangulation_free(&triangulation);
}

void test_triangulation_remove_invalid_triangle(void){

    Triangulation triangulation;
    triangulation_init(&triangulation);

    triangulation_add_triangle(&triangulation, create_triangle(0, 1, 2));

    triangulation_remove_triangle(&triangulation, -1); // Invalid index
    triangulation_remove_triangle(&triangulation, 1);  // Invalid index
    TEST_ASSERT_EQUAL_INT(1, triangulation.num_triangles);

    triangulation_free(&triangulation);
}

void test_triangulation_create_super_triangle(void){
    Triangulation triangulation;
    triangulation_init(&triangulation);

    triangulation_add_point(&triangulation, create_point(0.0, 0.0));
    triangulation_add_point(&triangulation, create_point(4.0, 0.0));
    triangulation_add_point(&triangulation, create_point(0.0, 4.0));

    int result = triangulation_create_super_triangle(&triangulation);

    TEST_ASSERT_EQUAL_INT(1, result);
    TEST_ASSERT_EQUAL_INT(6, triangulation.num_points);
    TEST_ASSERT_EQUAL_INT(1, triangulation.num_triangles);

    Triangle super_triangle = triangulation.triangles[0];

    for (int i = 0; i < 3;i++){
        TEST_ASSERT_TRUE(point_in_triangle(triangulation.points[i], super_triangle, triangulation.points));
    }

    triangulation_free(&triangulation);
}

void test_triangulation_create_super_triangle_not_enough_points(void){
    Triangulation triangulation;
    triangulation_init(&triangulation);

    triangulation_add_point(&triangulation, create_point(0.0, 0.0));
    triangulation_add_point(&triangulation, create_point(4.0, 0.0));

    int result = triangulation_create_super_triangle(&triangulation);

    TEST_ASSERT_EQUAL_INT(0, result);
    TEST_ASSERT_EQUAL_INT(2, triangulation.num_points);
    TEST_ASSERT_EQUAL_INT(0, triangulation.num_triangles);

    triangulation_free(&triangulation);
}

void test_triangulation_free(void){
    Triangulation triangulation;
    triangulation_init(&triangulation);

    triangulation_add_point(&triangulation, create_point(0.0, 0.0));
    triangulation_add_point(&triangulation, create_point(4.0, 0.0));
    triangulation_add_point(&triangulation, create_point(0.0, 4.0));

    triangulation_add_triangle(&triangulation, create_triangle(0, 1, 2));

    triangulation_free(&triangulation);

    TEST_ASSERT_NULL(triangulation.points);
    TEST_ASSERT_EQUAL_INT(0, triangulation.num_points);
    TEST_ASSERT_EQUAL_INT(0, triangulation.points_capacity);

    TEST_ASSERT_NULL(triangulation.triangles);
    TEST_ASSERT_EQUAL_INT(0, triangulation.num_triangles);
    TEST_ASSERT_EQUAL_INT(0, triangulation.triangles_capacity);
}

void test_remove_bad_triangles_removes_triangle(void){
    Triangulation triangulation;
    triangulation_init(&triangulation);

    triangulation_add_point(&triangulation, create_point(0.0, 0.0));
    triangulation_add_point(&triangulation, create_point(4.0, 0.0));
    triangulation_add_point(&triangulation, create_point(0.0, 4.0));

    triangulation_add_triangle(&triangulation, create_triangle(0, 1, 2));

    EdgeList boundary;
    init_edge_list(&boundary);


    Point new_point = create_point(1.0, 1.0);

    triangulation_remove_bad_triangles(&triangulation, new_point, &boundary);

    TEST_ASSERT_EQUAL_INT(0, triangulation.num_triangles);
    TEST_ASSERT_EQUAL_INT(3, boundary.size);

    free_edge_list(&boundary);
    triangulation_free(&triangulation);
}

void test_remove_bad_triangles_keeps_triangle(void){
    Triangulation triangulation;
    triangulation_init(&triangulation);

    triangulation_add_point(&triangulation, create_point(0.0, 0.0));
    triangulation_add_point(&triangulation, create_point(4.0, 0.0));
    triangulation_add_point(&triangulation, create_point(0.0, 4.0));

    triangulation_add_triangle(&triangulation, create_triangle(0, 1, 2));

    EdgeList boundary;
    init_edge_list(&boundary);

    Point new_point = create_point(5.0, 5.0);

    triangulation_remove_bad_triangles(&triangulation, new_point, &boundary);

    TEST_ASSERT_EQUAL_INT(1, triangulation.num_triangles);
    TEST_ASSERT_EQUAL_INT(0, boundary.size);

    free_edge_list(&boundary);
    triangulation_free(&triangulation);

}

void test_remove_bad_triangles_removes_shared_edge(void){
    Triangulation triangulation;
    triangulation_init(&triangulation);

    triangulation_add_point(&triangulation, create_point(0.0, 0.0));
    triangulation_add_point(&triangulation, create_point(4.0, 0.0));
    triangulation_add_point(&triangulation, create_point(4.0, 4.0));
    triangulation_add_point(&triangulation, create_point(0.0, 4.0));

    triangulation_add_triangle(&triangulation, create_triangle(0, 1, 2));
    triangulation_add_triangle(&triangulation, create_triangle(0, 2, 3));

    EdgeList boundary;
    init_edge_list(&boundary);

    Point new_point = create_point(2.0, 2.0);

    triangulation_remove_bad_triangles(&triangulation, new_point, &boundary);

    TEST_ASSERT_EQUAL_INT(0, triangulation.num_triangles);
    TEST_ASSERT_EQUAL_INT(4, boundary.size);

    Edge shared_edge = create_edge(0, 2);

    for (int i = 0; i< boundary.size; i++){
        TEST_ASSERT_FALSE(edge_equals(boundary.edges[i], shared_edge));
    }


    free_edge_list(&boundary);
    triangulation_free(&triangulation);
}


void test_create_new_triangles(void){
    Triangulation triangulation;
    triangulation_init(&triangulation);

    triangulation_add_point(&triangulation, create_point(0.0, 0.0));
    triangulation_add_point(&triangulation, create_point(4.0, 0.0));
    triangulation_add_point(&triangulation, create_point(0.0, 4.0));
    triangulation_add_point(&triangulation, create_point(1.0, 1.0));

    EdgeList boundary;
    init_edge_list(&boundary);

    add_edge_list(&boundary, create_edge(0, 1));
    add_edge_list(&boundary, create_edge(1, 2));
    add_edge_list(&boundary, create_edge(2, 0));

    triangulation_create_new_triangles(&triangulation, &boundary, 3);

    TEST_ASSERT_EQUAL_INT(3, triangulation.num_triangles);


    free_edge_list(&boundary);
    triangulation_free(&triangulation);

}

void test_create_new_triangles_skips_collinear(void){

    Triangulation triangulation;
    triangulation_init(&triangulation);

    triangulation_add_point(&triangulation, create_point(0.0, 0.0));
    triangulation_add_point(&triangulation, create_point(2.0, 0.0));
    triangulation_add_point(&triangulation, create_point(1.0, 0.0));

    EdgeList boundary;
    init_edge_list(&boundary);

    add_edge_list(&boundary, create_edge(0, 1));

    triangulation_create_new_triangles(&triangulation, &boundary, 2);

    TEST_ASSERT_EQUAL_INT(0, triangulation.num_triangles);

    free_edge_list(&boundary);
    triangulation_free(&triangulation);
}   

void test_bowyer_watson_three_points(void){
    Triangulation triangulation;
    triangulation_init(&triangulation);

    triangulation_add_point(&triangulation, create_point(0.0, 0.0));
    triangulation_add_point(&triangulation, create_point(4.0, 0.0));
    triangulation_add_point(&triangulation, create_point(0.0, 4.0));

    int result = bowyer_watson(&triangulation);
    
    TEST_ASSERT_EQUAL_INT(1, result);

    TEST_ASSERT_EQUAL_INT(3, triangulation.num_points);
    TEST_ASSERT_EQUAL_INT(1, triangulation.num_triangles);

    double area = get_triangle_area(triangulation.triangles[0], triangulation.points);
    TEST_ASSERT_DOUBLE_WITHIN(0.0001, 8.0, area);



    triangulation_free(&triangulation);
}


void test_bowyer_watson_four_points(void){
    Triangulation triangulation;
    triangulation_init(&triangulation);

    triangulation_add_point(&triangulation, create_point(0.0, 0.0));
    triangulation_add_point(&triangulation, create_point(4.0, 0.0));
    triangulation_add_point(&triangulation, create_point(3.0, 3.0));
    triangulation_add_point(&triangulation, create_point(0.0, 4.0));

    int result = bowyer_watson(&triangulation);
    
    TEST_ASSERT_EQUAL_INT(1, result);

    TEST_ASSERT_EQUAL_INT(4, triangulation.num_points);
    TEST_ASSERT_EQUAL_INT(2, triangulation.num_triangles);

    double total_area = 0.0;
    for (int i = 0; i < triangulation.num_triangles; i++){
        Triangle t = triangulation.triangles[i];

        TEST_ASSERT_TRUE(t.p1 < 4);
        TEST_ASSERT_TRUE(t.p2 < 4);
        TEST_ASSERT_TRUE(t.p3 < 4);
        total_area += get_triangle_area(t, triangulation.points);

    }

    TEST_ASSERT_DOUBLE_WITHIN(0.0001, 12.0, total_area);

    triangulation_free(&triangulation);
}


void test_bowyer_watson_not_enough_points(void){
    Triangulation triangulation;
    triangulation_init(&triangulation);

    triangulation_add_point(&triangulation, create_point(0.0, 0.0));
    triangulation_add_point(&triangulation, create_point(4.0, 0.0));

    int result = bowyer_watson(&triangulation);
    
    TEST_ASSERT_EQUAL_INT(0, result);

    TEST_ASSERT_EQUAL_INT(2, triangulation.num_points);
    TEST_ASSERT_EQUAL_INT(0, triangulation.num_triangles);

    triangulation_free(&triangulation);
}


void test_bowyer_existing_triangles(void){
    Triangulation triangulation;
    triangulation_init(&triangulation);

    triangulation_add_point(&triangulation, create_point(0.0, 0.0));
    triangulation_add_point(&triangulation, create_point(4.0, 0.0));
    triangulation_add_point(&triangulation, create_point(0.0, 4.0));

    triangulation_add_triangle(&triangulation, create_triangle(0, 1, 2));

    int result = bowyer_watson(&triangulation);

    TEST_ASSERT_EQUAL_INT(0, result);

    triangulation_free(&triangulation);
}

void test_bowyer_watson_collinear_points(void){
    Triangulation triangulation;
    triangulation_init(&triangulation);

    triangulation_add_point(&triangulation, create_point(0.0, 0.0));
    triangulation_add_point(&triangulation, create_point(2.0, 2.0));
    triangulation_add_point(&triangulation, create_point(4.0, 4.0));

    int result = bowyer_watson(&triangulation);
    
    TEST_ASSERT_EQUAL_INT(1, result);
    TEST_ASSERT_EQUAL_INT(0, triangulation.num_triangles);

    triangulation_free(&triangulation);
}


void test_bowyer_watson_four_collinear_points(void){

    Triangulation triangulation;
    triangulation_init(&triangulation);

    triangulation_add_point(&triangulation, create_point(0.0, 0.0));
    triangulation_add_point(&triangulation, create_point(2.0, 2.0));
    triangulation_add_point(&triangulation, create_point(4.0, 4.0));
    triangulation_add_point(&triangulation, create_point(6.0, 6.0));

    int result = bowyer_watson(&triangulation);
    
    TEST_ASSERT_EQUAL_INT(1, result);
    TEST_ASSERT_EQUAL_INT(0, triangulation.num_triangles);

    triangulation_free(&triangulation);
}

void test_bowyer_watson_points_on_same_circle(void){
    Triangulation triangulation;
    triangulation_init(&triangulation);

    triangulation_add_point(&triangulation, create_point(0.0, 0.0));
    triangulation_add_point(&triangulation, create_point(4.0, 0.0));
    triangulation_add_point(&triangulation, create_point(4.0, 4.0));
    triangulation_add_point(&triangulation, create_point(0.0, 4.0));

    TEST_ASSERT_EQUAL_INT(1, bowyer_watson(&triangulation));

    TEST_ASSERT_EQUAL_INT(2, triangulation.num_triangles);


    double total_area = 0.0;
    for(int i = 0; i < triangulation.num_triangles; i++){
        Triangle t = triangulation.triangles[i];
        total_area += get_triangle_area(t, triangulation.points);

    }

    TEST_ASSERT_DOUBLE_WITHIN(0.0001, 16.0, total_area);
    triangulation_free(&triangulation);

}

int triangulation_satisfies_delaynay(const Triangulation *triangulation){
    for (int i = 0; i < triangulation->num_triangles; ++i){
        Triangle triangle = triangulation->triangles[i];
        for(int j = 0; j < triangulation->num_points; ++j){
            if (j == triangle.p1 || j == triangle.p2 || j == triangle.p3){
                continue; // Skip the vertices of the triangle
            }
            Point point = triangulation->points[j];
            if (point_in_circumcicle(triangle, triangulation->points, point)){
                return 0;
            }
        }
    }

    return  1;
}

void test_bowyer_watson_six_points(void){
    Triangulation triangulation;
    triangulation_init(&triangulation);

    triangulation_add_point(&triangulation, create_point(0.0 , 0.0));
    triangulation_add_point(&triangulation, create_point(6.0, 0.0));
    triangulation_add_point(&triangulation, create_point(6.0, 6.0));
    triangulation_add_point(&triangulation, create_point(0.0, 6.0));
    triangulation_add_point(&triangulation, create_point(2.0, 2.0));
    triangulation_add_point(&triangulation, create_point(4.0, 3.0));

    TEST_ASSERT_EQUAL_INT(1, bowyer_watson(&triangulation));


    TEST_ASSERT_EQUAL_INT(6, triangulation.num_points);
    TEST_ASSERT_EQUAL_INT(6, triangulation.num_triangles);


    double total_area = 0.0;
    for(int i = 0; i < triangulation.num_triangles; i++){
        Triangle t = triangulation.triangles[i];
        TEST_ASSERT_TRUE(t.p1 < 6);
        TEST_ASSERT_TRUE(t.p2 < 6);
        TEST_ASSERT_TRUE(t.p3 < 6);
        total_area += get_triangle_area(t, triangulation.points);
    }

    TEST_ASSERT_DOUBLE_WITHIN(0.0001, 36.0, total_area);
    TEST_ASSERT_TRUE(triangulation_satisfies_delaynay(&triangulation));
    triangulation_free(&triangulation);
}

void test_bowyer_watson_eight_points(void){
    Triangulation triangulation;
    triangulation_init(&triangulation);


    triangulation_add_point(&triangulation, create_point(0.0 , 0.0));
    triangulation_add_point(&triangulation, create_point(10.0, 0));
    triangulation_add_point(&triangulation, create_point(10.0, 10.0));
    triangulation_add_point(&triangulation, create_point(0.0, 10.0));

    triangulation_add_point(&triangulation, create_point(2.0, 3.0));
    triangulation_add_point(&triangulation, create_point(7.0, 2.0));
    triangulation_add_point(&triangulation, create_point(8.0, 7.0));
    triangulation_add_point(&triangulation, create_point(3.0, 8.0));


    TEST_ASSERT_EQUAL_INT(1, bowyer_watson(&triangulation));

    TEST_ASSERT_EQUAL_INT(8, triangulation.num_points);
    TEST_ASSERT_EQUAL_INT(10, triangulation.num_triangles);

    double total_area = 0.0;
    int used_points[8] = {0};

    for (int i = 0; i < triangulation.num_triangles; i++){
        Triangle triangle = triangulation.triangles[i];
        TEST_ASSERT_TRUE(triangle.p1 < 8);
        TEST_ASSERT_TRUE(triangle.p2 < 8);
        TEST_ASSERT_TRUE(triangle.p3 < 8);

        used_points[triangle.p1] = 1;
        used_points[triangle.p2] = 1;
        used_points[triangle.p3] = 1;

        total_area += get_triangle_area(triangle, triangulation.points);
    }

    for(int i = 0; i < 8; i++){
         TEST_ASSERT_EQUAL_INT(1, used_points[i]);
    }


    TEST_ASSERT_DOUBLE_WITHIN(0.0001, 100.0, total_area);
    TEST_ASSERT_TRUE(triangulation_satisfies_delaynay(&triangulation));
    triangulation_free(&triangulation);

}