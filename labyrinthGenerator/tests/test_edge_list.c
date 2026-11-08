#include "unity.h"
#include "../src/edge_list.h"

void test_edge_list_init(void){
    EdgeList list;
    init_edge_list(&list);

    TEST_ASSERT_NULL(list.edges);
    TEST_ASSERT_EQUAL_INT(0, list.size);
    TEST_ASSERT_EQUAL_INT(0, list.capacity);
}

void test_edge_list_add(void){
    EdgeList list;
    init_edge_list(&list);

    Edge e = create_edge(1, 2);
    add_edge_list(&list, e);

    TEST_ASSERT_EQUAL_INT(1, list.size);
    TEST_ASSERT_EQUAL_INT(4, list.capacity);
    TEST_ASSERT_EQUAL_INT(1, list.edges[0].p1);
    TEST_ASSERT_TRUE(edge_equals(list.edges[0], e));

    free_edge_list(&list);
}

void test_edge_list_add_multiple(void){
    EdgeList list;
    init_edge_list(&list);

    Edge e1 = create_edge(1, 2);
    Edge e2 = create_edge(2, 3);
    Edge e3 = create_edge(3, 4);

    add_edge_list(&list, e1);
    add_edge_list(&list, e2);
    add_edge_list(&list, e3);

    TEST_ASSERT_EQUAL_INT(3, list.size);
    TEST_ASSERT_TRUE(edge_equals(list.edges[0], e1));
    TEST_ASSERT_TRUE(edge_equals(list.edges[1], e2));
    TEST_ASSERT_TRUE(edge_equals(list.edges[2], e3));

    free_edge_list(&list);
}

void test_edge_list_capacity_increase(void){
    EdgeList list;
    init_edge_list(&list);

    for(int i = 0; i < 5; i++){
        Edge e = create_edge(i, i+1);
        add_edge_list(&list, e);
    }

    TEST_ASSERT_EQUAL_INT(5, list.size);
    TEST_ASSERT_EQUAL_INT(8, list.capacity);

    free_edge_list(&list);
}

void test_edge_list_toggle_add(void){
    EdgeList list;
    init_edge_list(&list);

    Edge e = create_edge(1, 2);

    edge_list_toggle(&list, e);
    TEST_ASSERT_EQUAL_INT(1, list.size);

    TEST_ASSERT_TRUE(edge_equals(list.edges[0], e));

    free_edge_list(&list);
}

void test_edge_list_toggle_remove(void){
    EdgeList list;
    init_edge_list(&list);

    Edge e = create_edge(1, 2);

    edge_list_toggle(&list, e);
    TEST_ASSERT_EQUAL_INT(1, list.size);

    edge_list_toggle(&list, e);
    TEST_ASSERT_EQUAL_INT(0, list.size);

    free_edge_list(&list);
}

void test_edge_list_toggle_reversed(void){

    EdgeList list;
    init_edge_list(&list);

    Edge e1 = create_edge(1, 2);
    Edge e2 = create_edge(2, 1);

    edge_list_toggle(&list, e1);
    TEST_ASSERT_EQUAL_INT(1, list.size);

    edge_list_toggle(&list, e2);
    TEST_ASSERT_EQUAL_INT(0, list.size);

    free_edge_list(&list);
}

void test_edge_list_free(void){
    EdgeList list;
    init_edge_list(&list);

    Edge e1 = create_edge(1, 2);
    Edge e2 = create_edge(2, 3);

    add_edge_list(&list, e1);
    add_edge_list(&list, e2);

    free_edge_list(&list);

    TEST_ASSERT_NULL(list.edges);
    TEST_ASSERT_EQUAL_INT(0, list.size);
    TEST_ASSERT_EQUAL_INT(0, list.capacity);

}