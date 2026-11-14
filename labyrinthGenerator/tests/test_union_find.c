#include "unity.h"
#include "union_find.h"

void test_union_find_init(void) {
    UnionFind uf;
    int result = union_find_init(&uf, 5);
    TEST_ASSERT_EQUAL_INT(1, result);
    TEST_ASSERT_NOT_NULL(uf.parent);
    TEST_ASSERT_NOT_NULL(uf.rank);
    TEST_ASSERT_EQUAL_INT(5, uf.size);

    for (int i = 0; i < uf.size; i++) {
        TEST_ASSERT_EQUAL_INT(i, uf.parent[i]);
        TEST_ASSERT_EQUAL_INT(0, uf.rank[i]);
    }

    union_find_free(&uf);
}

void test_union_find_init_invalid_size(void) {
    UnionFind uf;
    int result = union_find_init(&uf, -1);
    TEST_ASSERT_EQUAL_INT(-1, result);
    TEST_ASSERT_NULL(uf.parent);
    TEST_ASSERT_NULL(uf.rank);
    TEST_ASSERT_EQUAL_INT(0, uf.size);
}

void test_union_find_init_each_element_is_its_own_parent(void) {
    UnionFind uf;
    union_find_init(&uf, 5);

    for (int i = 0; i < uf.size; i++) {
        int parent = union_find_find(&uf, i);
        TEST_ASSERT_EQUAL_INT(i, parent);
    }

    union_find_free(&uf);
}

void test_union_find_init_rank_is_zero(void) {
    UnionFind uf;
    TEST_ASSERT_EQUAL_INT(1, union_find_init(&uf, 5));

    for (int i = 0; i < uf.size; i++) {
        TEST_ASSERT_EQUAL_INT(0, uf.rank[i]);
    }

    union_find_free(&uf);
}

void test_union_find_init_null_returns_error(void) {
    int result = union_find_init(NULL, 5);
    TEST_ASSERT_EQUAL_INT(-1, result);
}

void test_union_find_init_negative_size_returns_error(void) {
    UnionFind uf;
    int result = union_find_init(&uf, -5);
    TEST_ASSERT_EQUAL_INT(-1, result);
}

void test_union_find_self(void){
    UnionFind uf;
    TEST_ASSERT_EQUAL_INT(1, union_find_init(&uf, 3));

    TEST_ASSERT_EQUAL_INT(0, union_find_find(&uf, 0));
    TEST_ASSERT_EQUAL_INT(2, union_find_find(&uf, 2));

    union_find_free(&uf);
}

void test_union_find_invalid_element(void){
    UnionFind uf;
    TEST_ASSERT_EQUAL_INT(1, union_find_init(&uf, 3));

    TEST_ASSERT_EQUAL_INT(-1, union_find_find(&uf, -1));
    TEST_ASSERT_EQUAL_INT(-1, union_find_find(&uf, 3));

    union_find_free(&uf);
}

void test_uf_find_after_union(void){
    UnionFind uf;
    TEST_ASSERT_EQUAL_INT(1, union_find_init(&uf, 4));

    union_find_union(&uf, 0, 1);
    TEST_ASSERT_EQUAL_INT(union_find_find(&uf, 0), union_find_find(&uf, 1));

    union_find_free(&uf);
}

void test_uf_find_path_compression(void){
    UnionFind uf;
    TEST_ASSERT_EQUAL_INT(1, union_find_init(&uf, 6));

    union_find_union(&uf, 0, 1);
    union_find_union(&uf, 2, 3);
    union_find_union(&uf, 0, 2);

    TEST_ASSERT_EQUAL_INT(2, uf.parent[3]);

    int root = union_find_find(&uf, 3);
    
    TEST_ASSERT_EQUAL_INT(0, root);
    TEST_ASSERT_EQUAL_INT(root, uf.parent[3]); 

    union_find_free(&uf);
}

void test_uf_union_two_singletons(void) {
    UnionFind uf;
    TEST_ASSERT_EQUAL_INT(1, union_find_init(&uf, 3));
    TEST_ASSERT_EQUAL_INT(1, union_find_union(&uf, 0, 1));
    TEST_ASSERT_TRUE(union_find_connected(&uf, 0, 1));
    union_find_free(&uf);
}

void test_uf_union_same_set(void) {
    UnionFind uf;
    TEST_ASSERT_EQUAL_INT(1, union_find_init(&uf, 3));
    union_find_union(&uf, 0, 1);
    TEST_ASSERT_EQUAL_INT(0, union_find_union(&uf, 0, 1));
    union_find_free(&uf);
}

void test_uf_union_invalid_elements(void) {
    UnionFind uf;
    TEST_ASSERT_EQUAL_INT(1, union_find_init(&uf, 3));
    TEST_ASSERT_EQUAL_INT(-1, union_find_union(&uf, -1, 1));
    TEST_ASSERT_EQUAL_INT(-1, union_find_union(&uf, 0, 3));
    union_find_free(&uf);
}

void test_uf_connected_after_chain_unions(void){
    UnionFind uf;
    TEST_ASSERT_EQUAL_INT(1, union_find_init(&uf, 5));

    union_find_union(&uf, 0, 1);
    union_find_union(&uf, 1, 2);
    union_find_union(&uf, 2, 3);

    TEST_ASSERT_TRUE(union_find_connected(&uf, 0, 3));
    TEST_ASSERT_TRUE(union_find_connected(&uf, 0, 2));
    TEST_ASSERT_FALSE(union_find_connected(&uf, 0, 4));

    union_find_free(&uf);
}


void test_uf_two_components(void){
    UnionFind uf;
    TEST_ASSERT_EQUAL_INT(1, union_find_init(&uf, 6));

    union_find_union(&uf, 0, 1);
    union_find_union(&uf, 1, 2);
    union_find_union(&uf, 3, 4);

    TEST_ASSERT_TRUE(union_find_connected(&uf, 0, 2));
    TEST_ASSERT_TRUE(union_find_connected(&uf, 3, 4));
    TEST_ASSERT_FALSE(union_find_connected(&uf, 0, 3));
    TEST_ASSERT_FALSE(union_find_connected(&uf, 0, 4));

    union_find_free(&uf);
}

void test_uf_free(void){
    UnionFind uf;
    TEST_ASSERT_EQUAL_INT(1, union_find_init(&uf, 5));
    union_find_free(&uf);

    TEST_ASSERT_NULL(uf.parent);
    TEST_ASSERT_NULL(uf.rank);
    TEST_ASSERT_EQUAL_INT(0, uf.size);
}

void test_uf_find_null(void) {
    TEST_ASSERT_EQUAL_INT(-1, union_find_find(NULL, 0));
}

void test_uf_connected_invalid_elements(void) {
    UnionFind uf;
    TEST_ASSERT_EQUAL_INT(1, union_find_init(&uf, 3));
    TEST_ASSERT_EQUAL_INT(-1, union_find_connected(&uf, -1, 1));
    TEST_ASSERT_EQUAL_INT(-1, union_find_connected(&uf, 0, 3));
    union_find_free(&uf);
}

void test_uf_union_null(void) {
    TEST_ASSERT_EQUAL_INT(-1, union_find_union(NULL, 0, 1));
}


void test_uf_free_twice(void) {
    UnionFind uf;
    TEST_ASSERT_EQUAL_INT(1, union_find_init(&uf, 5));
    union_find_free(&uf);
    union_find_free(&uf); 
}

void tes_uf_init_zero_size(void) {
    UnionFind uf;
    int result = union_find_init(&uf, 0);
    TEST_ASSERT_EQUAL_INT(1, result);
    TEST_ASSERT_NULL(uf.parent);
    TEST_ASSERT_NULL(uf.rank);
    TEST_ASSERT_EQUAL_INT(0, uf.size);
}
