#include "unity.h"
#include "../src/edge.h"


void test_edge_create(void) {
    Edge e = create_edge(1, 2);
    TEST_ASSERT_EQUAL_INT(1, e.p1);
    TEST_ASSERT_EQUAL_INT(2, e.p2);
}

void test_edge_equals_same(void) {
    Edge e1 = create_edge(1, 2);
    Edge e2 = create_edge(1, 2);
    TEST_ASSERT_TRUE(edge_equals(e1, e2));
}

void test_edge_equals_reversed(void) {
    Edge e1 = create_edge(1, 2);
    Edge e2 = create_edge(2, 1);
    TEST_ASSERT_TRUE(edge_equals(e1, e2));
}

void test_edge_equals_different(void) {
    Edge e1 = create_edge(1, 2);
    Edge e2 = create_edge(3, 4);
    TEST_ASSERT_FALSE(edge_equals(e1, e2));
}

void test_edge_equals_one_endpoint_different(void) {
    Edge e1 = create_edge(1, 2);
    Edge e2 = create_edge(1, 3);
    TEST_ASSERT_FALSE(edge_equals(e1, e2));
}