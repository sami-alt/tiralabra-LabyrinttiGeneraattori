#include "unity.h"
#include "../src/point.h"


void setUp(void){

}

void tearDown(void){

}

void test_point_create(void){
    Point p = create_point(2.0, 3.0);
    TEST_ASSERT_EQUAL_DOUBLE(2.0, p.x);
    TEST_ASSERT_EQUAL_DOUBLE(3.0, p.y);
}

void test_point_equals_same(void){
    Point p1 = create_point(2.0, 3.0);
    Point p2 = create_point(2.0, 3.0);
    TEST_ASSERT_TRUE(point_equals(p1, p2));
}

void test_point_equals_different(void){
    Point p1 = create_point(2.0, 3.0);
    Point p2 = create_point(3.0, 2.0);
    TEST_ASSERT_FALSE(point_equals(p1, p2));
}


void test_point_equals_different_y(void){
    Point p1 = create_point(2.0, 3.0);
    Point p2 = create_point(2.0, 4.0);
    TEST_ASSERT_FALSE(point_equals(p1, p2));
}

void test_point_equals_different_x(void){
    Point p1 = create_point(2.0, 3.0);
    Point p2 = create_point(3.0, 3.0);  
    TEST_ASSERT_FALSE(point_equals(p1, p2));
}