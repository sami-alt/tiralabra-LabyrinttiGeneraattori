
#include "../src/graph.h"

#include <stdlib.h>
#include "unity.h"


void test_graph_init(void) {
    Graph graph;
    graph_init(&graph);

    TEST_ASSERT_NULL(graph.edges);
    TEST_ASSERT_EQUAL_INT(0, graph.num_edges);
    TEST_ASSERT_EQUAL_INT(0, graph.capacity);

    graph_free(&graph);
}


void test_graph_add_edge(void) {
    Graph graph;
    graph_init(&graph);

    Edge edge = create_edge(0, 1);
    double weight = 1.0;

    int result = graph_add_edge(&graph, edge, weight);

    TEST_ASSERT_EQUAL_INT(1, result);
    TEST_ASSERT_EQUAL_INT(1, graph.num_edges);
    TEST_ASSERT_EQUAL_INT(1, graph.capacity);
    TEST_ASSERT_TRUE(edge_equals(graph.edges[0].edge, edge));
    TEST_ASSERT_DOUBLE_WITHIN(0.0001, weight, graph.edges[0].weight);

    graph_free(&graph);
}


void test_graph_add_multiple_edges(void) {
    Graph graph;
    graph_init(&graph);

    Edge edge1 = create_edge(0, 1);
    Edge edge2 = create_edge(1, 2);

    graph_add_edge(&graph, edge1, 2.5);
    graph_add_edge(&graph, edge2, 3.5);

    TEST_ASSERT_EQUAL_INT(2, graph.num_edges);
    TEST_ASSERT_EQUAL_INT(2, graph.capacity);

    TEST_ASSERT_TRUE(edge_equals(graph.edges[0].edge, edge1));
    TEST_ASSERT_TRUE(edge_equals(graph.edges[1].edge, edge2));

    TEST_ASSERT_DOUBLE_WITHIN(0.0001, 2.5, graph.edges[0].weight);
    TEST_ASSERT_DOUBLE_WITHIN(0.0001, 3.5, graph.edges[1].weight);

    graph_free(&graph);
}


void test_calculate_edge_weight(void) {
    Triangulation triangulation = {0};

    Point points[] = {
        {0, 0},
        {3, 4}
    };

    triangulation.points = points;
    triangulation.num_points = 2;

    Edge edge = create_edge(0, 1);

    double weight = calculate_edge_weight(&triangulation, edge);

    TEST_ASSERT_DOUBLE_WITHIN(0.0001, 5.0, weight);
}


void test_one_triangle_graph(void) {
    Graph graph;
    graph_init(&graph);

    Triangulation triangulation = {0};

    triangulation.num_triangles = 1;
    triangulation.triangles = malloc(sizeof(Triangle));

    triangulation.num_points = 3;
    triangulation.points = malloc(3 * sizeof(Point));

    TEST_ASSERT_NOT_NULL(triangulation.triangles);
    TEST_ASSERT_NOT_NULL(triangulation.points);

    triangulation.triangles[0] = create_triangle(0, 1, 2);

    triangulation.points[0] = create_point(0, 0);
    triangulation.points[1] = create_point(3, 0);
    triangulation.points[2] = create_point(0, 4);

    int result = graph_from_triangulation(&graph, &triangulation);

    TEST_ASSERT_EQUAL_INT(1, result);
    TEST_ASSERT_EQUAL_INT(3, graph.num_edges);

    // Check that all three edge weights are correct.
    for (int i = 0; i < graph.num_edges; i++) {
        Edge edge = graph.edges[i].edge;
        double weight = calculate_edge_weight(&triangulation, edge);

        TEST_ASSERT_DOUBLE_WITHIN(
            0.0001,
            weight,
            graph.edges[i].weight
        );
    }

    free(triangulation.triangles);
    free(triangulation.points);
    graph_free(&graph);
}


void test_two_triangles_five_edges_graph(void) {
    Graph graph;
    graph_init(&graph);

    Triangulation triangulation = {0};

    triangulation.num_triangles = 2;
    triangulation.triangles = malloc(2 * sizeof(Triangle));

    triangulation.num_points = 4;
    triangulation.points = malloc(4 * sizeof(Point));

    TEST_ASSERT_NOT_NULL(triangulation.triangles);
    TEST_ASSERT_NOT_NULL(triangulation.points);

    triangulation.triangles[0] = create_triangle(0, 1, 2);
    triangulation.triangles[1] = create_triangle(2, 1, 3);

    triangulation.points[0] = create_point(0, 0);
    triangulation.points[1] = create_point(3, 0);
    triangulation.points[2] = create_point(0, 4);
    triangulation.points[3] = create_point(3, 4);

    int result = graph_from_triangulation(&graph, &triangulation);

    TEST_ASSERT_EQUAL_INT(1, result);
    TEST_ASSERT_EQUAL_INT(5, graph.num_edges);

    // The shared edge must appear exactly once.
    Edge shared_edge = create_edge(1, 2);
    int count = 0;

    for (int i = 0; i < graph.num_edges; i++) {
        if (edge_equals(graph.edges[i].edge, shared_edge)) {
            count++;
        }
    }

    TEST_ASSERT_EQUAL_INT(1, count);

    free(triangulation.triangles);
    free(triangulation.points);
    graph_free(&graph);
}


void test_no_edges_graph(void) {
    Graph graph;
    graph_init(&graph);

    Triangulation triangulation = {0};

    int result = graph_from_triangulation(&graph, &triangulation);

    TEST_ASSERT_EQUAL_INT(1, result);
    TEST_ASSERT_EQUAL_INT(0, graph.num_edges);
    TEST_ASSERT_NULL(graph.edges);

    graph_free(&graph);
}


void test_graph_from_null_triangulation(void) {
    Graph graph;
    graph_init(&graph);

    int result = graph_from_triangulation(&graph, NULL);

    TEST_ASSERT_EQUAL_INT(-1, result);

    graph_free(&graph);
}


void test_free_graph(void) {
    Graph graph;
    graph_init(&graph);

    Edge edge1 = create_edge(0, 1);
    Edge edge2 = create_edge(1, 2);

    graph_add_edge(&graph, edge1, 1.0);
    graph_add_edge(&graph, edge2, 2.0);

    graph_free(&graph);

    TEST_ASSERT_NULL(graph.edges);
    TEST_ASSERT_EQUAL_INT(0, graph.num_edges);
    TEST_ASSERT_EQUAL_INT(0, graph.capacity);
}