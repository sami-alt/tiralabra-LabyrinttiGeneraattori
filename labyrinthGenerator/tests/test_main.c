#include "unity.h"

//Unity test functions
void test_point_create(void);
void test_point_equals_same(void);
void test_point_equals_different(void);
void test_point_equals_different_y(void);
void test_point_equals_different_x(void);

void test_edge_create(void);
void test_edge_equals_same(void);
void test_edge_equals_reversed(void);
void test_edge_equals_different(void);
void test_edge_equals_one_endpoint_different(void);

void test_edge_list_init(void);
void test_edge_list_add(void);
void test_edge_list_add_multiple(void);
void test_edge_list_capacity_increase(void);
void test_edge_list_toggle_add(void);
void test_edge_list_toggle_remove(void);
void test_edge_list_toggle_reversed(void);
void test_edge_list_free(void);

void test_triangle_create(void);
void test_triangle_area(void);
void test_triangle_area_reversed(void);
void test_triangle_area_collinear(void);
void test_triangle_orientation_counterclockwise(void);
void test_triangle_orientation_clockwise(void);
void test_triangle_orientation_collinear(void);
void test_point_in_circumcircle_inside(void);
void test_point_in_circumcircle_outside(void);
void test_point_in_circumcircle_boundary(void);
void test_point_in_triangle(void);

void test_triangulation_init(void);
void test_triangulation_add_point(void);
void test_triangulation_add_multiple_point(void);
void test_triangulation_add_triangle(void);
void test_triangulation_remove_triangle(void);
void test_triangulation_create_super_triangle(void);
void test_triangulation_create_super_triangle_not_enough_points(void);
void test_triangulation_free(void);

void test_remove_bad_triangles_keeps_triangle(void);
void test_remove_bad_triangles_removes_triangle(void);
void test_remove_bad_triangles_removes_shared_edge(void);
void test_create_new_triangles(void);
void test_create_new_triangles_skips_collinear(void);

void test_bowyer_watson_three_points(void);
void test_bowyer_watson_four_points(void);
void test_bowyer_watson_not_enough_points(void);
void test_bowyer_existing_triangles(void);
void test_bowyer_watson_collinear_points(void);
void test_bowyer_watson_four_collinear_points(void);
void test_bowyer_watson_points_on_same_circle(void);
void test_bowyer_watson_six_points(void);
void test_bowyer_watson_eight_points(void);

int main(void) {
    UNITY_BEGIN();


    //Unit tests for point.c
    RUN_TEST(test_point_create);
    RUN_TEST(test_point_equals_same);
    RUN_TEST(test_point_equals_different);
    RUN_TEST(test_point_equals_different_y);
    RUN_TEST(test_point_equals_different_x);

    //Unit tests for edge.c
    RUN_TEST(test_edge_create);
    RUN_TEST(test_edge_equals_same);
    RUN_TEST(test_edge_equals_reversed);
    RUN_TEST(test_edge_equals_different);
    RUN_TEST(test_edge_equals_one_endpoint_different);

    //Unit test for edge_list.c
    RUN_TEST(test_edge_list_init);
    RUN_TEST(test_edge_list_add);
    RUN_TEST(test_edge_list_add_multiple);
    RUN_TEST(test_edge_list_capacity_increase);
    RUN_TEST(test_edge_list_toggle_add);
    RUN_TEST(test_edge_list_toggle_remove);
    RUN_TEST(test_edge_list_toggle_reversed);
    RUN_TEST(test_edge_list_free);

    //Unit tests for triangle.c
    RUN_TEST(test_triangle_create);
    RUN_TEST(test_triangle_area);
    RUN_TEST(test_triangle_area_reversed);
    RUN_TEST(test_triangle_area_collinear);
    RUN_TEST(test_triangle_orientation_counterclockwise);
    RUN_TEST(test_triangle_orientation_clockwise);
    RUN_TEST(test_triangle_orientation_collinear);
    RUN_TEST(test_point_in_circumcircle_inside);
    RUN_TEST(test_point_in_circumcircle_outside);
    RUN_TEST(test_point_in_circumcircle_boundary);
    RUN_TEST(test_point_in_triangle);

    //Unit tests for triangulation.c
    RUN_TEST(test_triangulation_init);
    RUN_TEST(test_triangulation_add_point);
    RUN_TEST(test_triangulation_add_multiple_point);
    RUN_TEST(test_triangulation_add_triangle);
    RUN_TEST(test_triangulation_remove_triangle);
    RUN_TEST(test_triangulation_create_super_triangle);
    RUN_TEST(test_triangulation_create_super_triangle_not_enough_points);
    RUN_TEST(test_triangulation_free);

    //Unit tests for triangulation.c functions
    RUN_TEST(test_remove_bad_triangles_removes_triangle);
    RUN_TEST(test_remove_bad_triangles_keeps_triangle);
    RUN_TEST(test_remove_bad_triangles_removes_shared_edge);
    RUN_TEST(test_create_new_triangles);
    RUN_TEST(test_create_new_triangles_skips_collinear);

    //Unit tests for bowyer_watson
    RUN_TEST(test_bowyer_watson_three_points);
    RUN_TEST(test_bowyer_watson_four_points);
    RUN_TEST(test_bowyer_watson_not_enough_points);
    RUN_TEST(test_bowyer_existing_triangles);
    RUN_TEST(test_bowyer_watson_collinear_points);
    RUN_TEST(test_bowyer_watson_four_collinear_points);
    RUN_TEST(test_bowyer_watson_points_on_same_circle);
    RUN_TEST(test_bowyer_watson_six_points);
    RUN_TEST(test_bowyer_watson_eight_points);

    return UNITY_END();
}