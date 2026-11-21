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

void test_super_triangle_same_points(void);
void test_remove_triangle_negative_index(void);
void test_bowyer_watson_same_points(void);

void test_graph_init(void);
void test_graph_add_edge(void);
void test_graph_add_multiple_edges(void);
void test_calculate_edge_weight(void);
void test_one_triangle_graph(void);
void test_two_triangles_five_edges_graph(void);
void test_no_edges_graph(void);
void test_graph_from_null_triangulation(void);
void test_free_graph(void);

void test_union_find_init(void);
void test_union_find_init_null_returns_error(void);
void test_union_find_init_negative_size_returns_error(void);
void test_union_find_self(void);
void test_union_find_invalid_element(void);
void test_uf_find_after_union(void);
void test_uf_find_path_compression(void);
void test_uf_union_two_singletons(void);
void test_uf_union_same_set(void);
void test_uf_union_invalid_elements(void);
void test_uf_connected_after_chain_unions(void);
void test_uf_two_components(void);
void test_uf_free(void);

void test_kruskal_empty_graph(void);
void test_kruskal_single_edge(void);
void test_kruskal_triangle_drops_heaviest_edge(void);
void test_kruskal_disconnected_fails(void);
void test_kruskal_input_graph_not_mutated(void);
void test_kruskal_skips_out_of_bounds_vertices(void);   


void test_kruskal_self_loop(void);
void test_kruskal_null_arguments(void);
void test_kruskal_no_edges(void);
void test_kruskal_zero_weight(void);
void test_kruskal_negative_weight(void);
void test_kruskal_equal_weight(void);

void test_place_rooms_null_output_pointer(void);
void test_place_rooms_invalid_arguments(void);
void test_plance_rooms_impossible_minimum_distance(void);
void test_place_too_many_rooms(void);
void test_place_single_room(void);
void test_place_rooms_all_in_bounds(void);
void test_place_rooms_with_deterministic_for_same_seed(void);
void test_place_rooms_with_different_seeds(void);
void test_place_rooms_with_minimum_distance_allows_any_position(void);

void test_render_null_arguments(void);
void test_render_single_room_no_edges(void);
void test_render_room_out_of_bouds(void);
void test_render_two_rooms_horizontal_corridor(void);
void test_render_two_rooms_vertical_corridor(void);
void test_render_two_rooms_diagonal_l_corridor(void);
void test_render_three_rooms_connected(void);
void test_render_rejects_edge_with_out_of_range_room_index(void);   
void test_free_render_grid_null_safe(void);

void test_pipeline_produces_grid_of_requested_size(void);
void test_pipeline_all_rooms_reachable(void);
void test_pipeline_deterministic_for_same_seed(void);
void test_pipeline_different_seeds_produce_different_grids(void);
void test_pipeline_rejects_null_options(void);
void test_pipeline_rejects_too_few_rooms(void);
void test_pipeline_rejects_impossible_minimum_distance(void);
void test_pipeline_rejects_negative_dimesions(void);
void test_pipeline_minimal_viable_input(void);

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

    //Unit tests for graph.c
    RUN_TEST(test_graph_init);
    RUN_TEST(test_graph_add_edge);
    RUN_TEST(test_graph_add_multiple_edges);
    RUN_TEST(test_calculate_edge_weight);
    RUN_TEST(test_one_triangle_graph);
    RUN_TEST(test_two_triangles_five_edges_graph);
    RUN_TEST(test_no_edges_graph);
    RUN_TEST(test_graph_from_null_triangulation);
    RUN_TEST(test_free_graph);

    //Unit tests for union_find.c
    RUN_TEST(test_union_find_init);
    RUN_TEST(test_union_find_init_null_returns_error);
    RUN_TEST(test_union_find_init_negative_size_returns_error);
    RUN_TEST(test_union_find_self);
    RUN_TEST(test_union_find_invalid_element);
    RUN_TEST(test_uf_find_after_union);
    RUN_TEST(test_uf_find_path_compression);
    RUN_TEST(test_uf_union_two_singletons);
    RUN_TEST(test_uf_union_same_set);
    RUN_TEST(test_uf_union_invalid_elements);
    RUN_TEST(test_uf_connected_after_chain_unions);
    RUN_TEST(test_uf_two_components);
    RUN_TEST(test_uf_free);

    //Unit tests for kruskal.c
    RUN_TEST(test_kruskal_empty_graph);
    RUN_TEST(test_kruskal_single_edge);
    RUN_TEST(test_kruskal_triangle_drops_heaviest_edge);
    RUN_TEST(test_kruskal_disconnected_fails);
    RUN_TEST(test_kruskal_input_graph_not_mutated);
    RUN_TEST(test_kruskal_skips_out_of_bounds_vertices);    
    RUN_TEST(test_kruskal_self_loop);
    RUN_TEST(test_kruskal_null_arguments);
    RUN_TEST(test_kruskal_no_edges);
    RUN_TEST(test_kruskal_zero_weight);
    RUN_TEST(test_kruskal_negative_weight);
    RUN_TEST(test_kruskal_equal_weight);

    //Unit tests for rooms.c
    RUN_TEST(test_place_rooms_null_output_pointer);
    RUN_TEST(test_place_rooms_invalid_arguments);
    RUN_TEST(test_plance_rooms_impossible_minimum_distance);
    RUN_TEST(test_place_too_many_rooms);
    RUN_TEST(test_place_single_room);
    RUN_TEST(test_place_rooms_all_in_bounds);
    RUN_TEST(test_place_rooms_with_deterministic_for_same_seed);
    RUN_TEST(test_place_rooms_with_different_seeds);
    RUN_TEST(test_place_rooms_with_minimum_distance_allows_any_position);

    //Unit tests for render.c
    RUN_TEST(test_render_null_arguments);
    RUN_TEST(test_render_single_room_no_edges);
    RUN_TEST(test_render_room_out_of_bouds);
    RUN_TEST(test_render_two_rooms_horizontal_corridor);
    RUN_TEST(test_render_two_rooms_vertical_corridor);
    RUN_TEST(test_render_two_rooms_diagonal_l_corridor);
    RUN_TEST(test_render_three_rooms_connected);
    RUN_TEST(test_render_rejects_edge_with_out_of_range_room_index);
    RUN_TEST(test_free_render_grid_null_safe);

    //Integration tests for the labyrinth generation pipeline
    RUN_TEST(test_pipeline_produces_grid_of_requested_size);
    RUN_TEST(test_pipeline_all_rooms_reachable);
    RUN_TEST(test_pipeline_deterministic_for_same_seed);
    RUN_TEST(test_pipeline_different_seeds_produce_different_grids);
    RUN_TEST(test_pipeline_rejects_null_options);
    RUN_TEST(test_pipeline_rejects_too_few_rooms);
    RUN_TEST(test_pipeline_rejects_impossible_minimum_distance);
    RUN_TEST(test_pipeline_rejects_negative_dimesions);
    RUN_TEST(test_pipeline_minimal_viable_input);

    return UNITY_END();
}