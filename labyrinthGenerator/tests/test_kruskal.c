#include "unity.h"
#include "kruskal.h"
#include <math.h>

void test_kruskal_empty_graph(void) {
    Graph graph;
    graph_init(&graph);

    Graph mst;
    int result = kruskal_minimum_spanning_tree(&graph, 0, &mst);

    TEST_ASSERT_EQUAL_INT(-1, result);
    TEST_ASSERT_EQUAL_INT(0, mst.num_edges);
    TEST_ASSERT_NULL(mst.edges);

    graph_free(&graph);
    graph_free(&mst);
}

void test_kruskal_single_vertex(void) {
    Graph graph;
    graph_init(&graph);

    Graph mst;
    int result = kruskal_minimum_spanning_tree(&graph, 1, &mst);

    TEST_ASSERT_EQUAL_INT(1, result);
    TEST_ASSERT_EQUAL_INT(0, mst.num_edges);
    TEST_ASSERT_NULL(mst.edges);

    graph_free(&graph);
    graph_free(&mst);
}

void test_kruskal_null_arguments(void) {
    Graph graph;
    graph_init(&graph);

    Graph mst;
    graph_init(&mst);

    int result = kruskal_minimum_spanning_tree(NULL, 3, &mst);
    TEST_ASSERT_EQUAL_INT(-1, result);

    result = kruskal_minimum_spanning_tree(&graph, 3, NULL);
    TEST_ASSERT_EQUAL_INT(-1, result);

    result = kruskal_minimum_spanning_tree(&graph, -1, &mst);
    TEST_ASSERT_EQUAL_INT(-1, result);


    graph_free(&graph);
    graph_free(&mst);
}

void test_kruskal_no_edges(void) {
    Graph graph;
    graph_init(&graph);

    Graph mst;
    int result = kruskal_minimum_spanning_tree(&graph, 3, &mst);

    TEST_ASSERT_EQUAL_INT(-1, result);
    TEST_ASSERT_EQUAL_INT(0, mst.num_edges);
    TEST_ASSERT_NULL(mst.edges);

    graph_free(&graph);
    graph_free(&mst);
}

void test_kruskal_single_edge(void){
    Graph graph;
    graph_init(&graph);

    Edge edge = create_edge(0, 1);
    graph_add_edge(&graph, edge, 3.0);

    Graph mst;
    int result = kruskal_minimum_spanning_tree(&graph, 2, &mst);

    TEST_ASSERT_EQUAL_INT(1, result);
    TEST_ASSERT_EQUAL_INT(1, mst.num_edges);
    TEST_ASSERT_TRUE(edge_equals(mst.edges[0].edge, edge));
    TEST_ASSERT_DOUBLE_WITHIN(0.0001, 3.0, mst.edges[0].weight);

    graph_free(&graph);
    graph_free(&mst);
}

void test_kruskal_triangle_drops_heaviest_edge(void){

    Graph graph;
    graph_init(&graph);

    Edge edge1 = create_edge(0, 1);
    Edge edge2 = create_edge(1, 2);
    Edge edge3 = create_edge(0, 2);

    graph_add_edge(&graph, edge1, 1.0);
    graph_add_edge(&graph, edge2, 2.0);
    graph_add_edge(&graph, edge3, 5.0);

    Graph mst;
    int result = kruskal_minimum_spanning_tree(&graph, 3, &mst);

    TEST_ASSERT_EQUAL_INT(1, result);
    TEST_ASSERT_EQUAL_INT(2, mst.num_edges);

    // Painavin reuna (edge3) ei saa olla mukana MST:ssä
    for (int i = 0; i < mst.num_edges; i++) {
        TEST_ASSERT_FALSE(edge_equals(mst.edges[i].edge, edge3));
    }

    graph_free(&graph);
    graph_free(&mst);
}

void test_kruskal_four_node_known_mst(void){
    Graph graph;
    graph_init(&graph);

    Edge edge1 = create_edge(0, 1);
    Edge edge2 = create_edge(1, 2);
    Edge edge3 = create_edge(2, 3);
    Edge edge4 = create_edge(3, 0);
    Edge edge5 = create_edge(0, 2);
    Edge edge6 = create_edge(1, 3);

    graph_add_edge(&graph, edge1, 1.0);
    graph_add_edge(&graph, edge2, 1.0);
    graph_add_edge(&graph, edge3, 1.0);
    graph_add_edge(&graph, edge4, 1.0);
    graph_add_edge(&graph, edge5, sqrt(2.0)); // sqrt(2)
    graph_add_edge(&graph, edge6, sqrt(2.0)); // sqrt(2)

    Graph mst;
    int result = kruskal_minimum_spanning_tree(&graph, 4, &mst);

    TEST_ASSERT_EQUAL_INT(1, result);
    TEST_ASSERT_EQUAL_INT(3, mst.num_edges);

    // Tarkistetaan että MST sisältää oikeat reunat
    double total_weight = 0.0;
    for (int i = 0; i < mst.num_edges; i++) {
        total_weight += mst.edges[i].weight;
    }
    TEST_ASSERT_DOUBLE_WITHIN(0.0001, 3.0, total_weight); 

    graph_free(&graph);
    graph_free(&mst);

}

void test_kruskal_disconnected_fails(void) {
    Graph g;
    graph_init(&g);

    Edge edge1 = create_edge(0, 1);
    Edge edge2 = create_edge(2, 3);

    graph_add_edge(&g, edge1, 1.0);
    graph_add_edge(&g, edge2, 1.0);

    Graph mst;
    TEST_ASSERT_EQUAL_INT(-1, kruskal_minimum_spanning_tree(&g, 4, &mst));

    graph_free(&g);
}

void test_kruskal_input_graph_not_mutated(void){
    Graph graph;
    graph_init(&graph);

    Edge edge1 = create_edge(0, 1);
    Edge edge2 = create_edge(1, 2);
    Edge edge3 = create_edge(0, 2);

    graph_add_edge(&graph, edge1, 5.0);
    graph_add_edge(&graph, edge2, 1.0);
    graph_add_edge(&graph, edge3, 3.0);

    Graph mst;
    int result = kruskal_minimum_spanning_tree(&graph, 3, &mst);
    TEST_ASSERT_EQUAL_INT(1, result);
    TEST_ASSERT_DOUBLE_WITHIN(0.0001, 5.0, graph.edges[0].weight);
    TEST_ASSERT_DOUBLE_WITHIN(0.0001, 1.0, graph.edges[1].weight);
    TEST_ASSERT_DOUBLE_WITHIN(0.0001, 3.0, graph.edges[2].weight);  

    graph_free(&graph);
    graph_free(&mst);
}

void test_kruskal_skips_out_of_bounds_vertices(void){
    Graph graph;
    graph_init(&graph);

    Edge edge1 = create_edge(0, 1);
    Edge edge2 = create_edge(1, 99); 

    graph_add_edge(&graph, edge1, 1.0);
    graph_add_edge(&graph, edge2, 1.0);

    Graph mst;
    int result = kruskal_minimum_spanning_tree(&graph, 2, &mst);
    TEST_ASSERT_EQUAL_INT(1, result);
    TEST_ASSERT_EQUAL_INT(1, mst.num_edges);

    graph_free(&graph);
    graph_free(&mst);
}

void test_kruskal_self_loop(void){
    Graph graph;
    graph_init(&graph);

    Edge edge1 = create_edge(0, 0); 
    Edge edge2 = create_edge(0, 1); 

    graph_add_edge(&graph, edge1, 1.0);
    graph_add_edge(&graph, edge2, 1.0);

    Graph mst;
    int result = kruskal_minimum_spanning_tree(&graph, 2, &mst);
    TEST_ASSERT_EQUAL_INT(1, result);
    TEST_ASSERT_EQUAL_INT(1, mst.num_edges);
    TEST_ASSERT_TRUE(edge_equals(mst.edges[0].edge, edge2));

    graph_free(&graph);
    graph_free(&mst);
}
void test_kruskal_dublicate_edges(void){
    Graph graph;
    graph_init(&graph);

    Edge edge1 = create_edge(0, 1);
    Edge edge2 = create_edge(0, 1); 

    graph_add_edge(&graph, edge1, 1.0);
    graph_add_edge(&graph, edge2, 2.0); 

    Graph mst;
    int result = kruskal_minimum_spanning_tree(&graph, 2, &mst);
    TEST_ASSERT_EQUAL_INT(1, result);
    TEST_ASSERT_EQUAL_INT(1, mst.num_edges);
    TEST_ASSERT_TRUE(edge_equals(mst.edges[0].edge, edge1));
    TEST_ASSERT_DOUBLE_WITHIN(0.0001, 1.0, mst.edges[0].weight);

    graph_free(&graph);
    graph_free(&mst);
}


void test_kruskal_negative_weight(void){
    Graph graph;
    graph_init(&graph);

    Edge edge1 = create_edge(0, 1);
    Edge edge2 = create_edge(1, 2);

    graph_add_edge(&graph, edge1, -1.0); 
    graph_add_edge(&graph, edge2, 1.0); 

    Graph mst;
    int result = kruskal_minimum_spanning_tree(&graph, 3, &mst);
    TEST_ASSERT_EQUAL_INT(1, result); 
    TEST_ASSERT_EQUAL_INT(2, mst.num_edges);

    double total_weight = 0.0;
    for (int i = 0; i < mst.num_edges; i++) {
        total_weight += mst.edges[i].weight;
    }
    TEST_ASSERT_DOUBLE_WITHIN(0.0001, 0.0, total_weight);

    graph_free(&graph);
    graph_free(&mst);
}

void test_kruskal_equal_weight(void){
    Graph graph;
    graph_init(&graph);

    Edge edge1 = create_edge(0, 1);
    Edge edge2 = create_edge(1, 2);
    Edge edge3 = create_edge(0, 2);

    graph_add_edge(&graph, edge1, 1.0);
    graph_add_edge(&graph, edge2, 1.0);
    graph_add_edge(&graph, edge3, 1.0);

    Graph mst;
    int result = kruskal_minimum_spanning_tree(&graph, 3, &mst);
    TEST_ASSERT_EQUAL_INT(1, result);
    TEST_ASSERT_EQUAL_INT(2, mst.num_edges);

    double total_weight = 0.0;
    for (int i = 0; i < mst.num_edges; i++) {
        total_weight += mst.edges[i].weight;
    }
    TEST_ASSERT_DOUBLE_WITHIN(0.0001, 2.0, total_weight); 

    graph_free(&graph);
    graph_free(&mst);
}

void test_kruskal_null_edges_array(void){
    Graph graph;
    graph_init(&graph);

    graph.num_edges = 2;
    graph.capacity = 2;
    graph.edges = NULL;

    Graph mst;
    graph_init(&mst);

    int result = kruskal_minimum_spanning_tree(&graph, 3, &mst);

    TEST_ASSERT_EQUAL_INT(-1, result);

    graph_free(&graph);
    graph_free(&mst);
}

void test_kruskal_zero_weight(void){
    Graph graph;
    graph_init(&graph);

    Edge edge1 = create_edge(0, 1);
    Edge edge2 = create_edge(1, 2);
    Edge edge3 = create_edge(0, 2);

    graph_add_edge(&graph, edge1, 0.0);
    graph_add_edge(&graph, edge2, 2.0);
    graph_add_edge(&graph, edge3, 5.0);

    Graph mst;
    int result = kruskal_minimum_spanning_tree(&graph, 3, &mst);

    TEST_ASSERT_EQUAL_INT(1, result);
    TEST_ASSERT_EQUAL_INT(2, mst.num_edges);

    double total_weight = 0.0;
    for (int i = 0; i < mst.num_edges; i++) {
        total_weight += mst.edges[i].weight;
    }

    TEST_ASSERT_DOUBLE_WITHIN(0.0001, 2.0, total_weight);

    graph_free(&graph);
    graph_free(&mst);
}