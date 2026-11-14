#include <unity.h>
#include "../src/triangle.h"

void test_triangle_create(void) {


    Triangle t = create_triangle(0, 1, 2);

    TEST_ASSERT_EQUAL_INT(0, t.p1);
    TEST_ASSERT_EQUAL_INT(1, t.p2);
    TEST_ASSERT_EQUAL_INT(2, t.p3);
}

void test_triangle_area(void){
    Point points[3] = {
        create_point(0.0, 0.0),
        create_point(4.0, 0.0),
        create_point(0.0, 4.0)
    };
    Triangle t = create_triangle(0, 1, 2);
    
    TEST_ASSERT_DOUBLE_WITHIN(0.0001, 8.0, get_triangle_area(t, points));
}

void test_triangle_area_reversed(void){
    Point points[] = {
        create_point(0.0, 0.0),
        create_point(2.0, 2.0),
        create_point(4.0, 4.0)
    };

    Triangle t = create_triangle(0, 1, 2);

    TEST_ASSERT_DOUBLE_WITHIN(0.0001, 0.0, get_triangle_area(t, points));

}


void test_triangle_area_collinear(void){
    Point points[] = {
        create_point(0.0, 0.0),
        create_point(2.0, 2.0),
        create_point(4.0, 4.0)
    };

    Triangle t = create_triangle(0, 1, 2);

    TEST_ASSERT_DOUBLE_WITHIN(0.0001, 0.0, get_triangle_area(t, points));
}

void test_triangle_orientation_counterclockwise(void){
    Point points[] = {
        create_point(0.0, 0.0),
        create_point(4.0, 0.0),
        create_point(0.0, 4.0)
    };

    Triangle t = create_triangle(0, 1, 2);

    TEST_ASSERT_EQUAL(COUNTERCLOCKWISE, get_triangle_orientation(t, points));
}

void test_triangle_orientation_clockwise(void){
    Point points[] = {
        create_point(0.0, 0.0),
        create_point(4.0, 0.0),
        create_point(0.0, 4.0)
    };

    Triangle t = create_triangle(0, 2, 1);

    TEST_ASSERT_EQUAL(CLOCKWISE, get_triangle_orientation(t, points));
}

void test_triangle_orientation_collinear(void){
    Point points[] = {
        create_point(0.0, 0.0),
        create_point(2.0, 2.0),
        create_point(4.0, 4.0)
    };

    Triangle t = create_triangle(0, 1, 2);

    TEST_ASSERT_EQUAL_INT(COLLINEAR, get_triangle_orientation(t, points));
}

void test_point_in_circumcircle_inside(void){
    Point points[] = {
        create_point(0.0, 0.0),
        create_point(4.0, 0.0),
        create_point(2.0, 4.0)
    };

    Triangle t = create_triangle(0, 1, 2);
    Point p = create_point(2.0, 2.0);

    TEST_ASSERT_TRUE(point_in_circumcicle(t, points, p));
}

void test_point_in_circumcircle_outside(void){
    Point points[] = {
        create_point(0.0, 0.0),
        create_point(4.0, 0.0),
        create_point(2.0, 4.0)
    };

    Triangle t = create_triangle(0, 1, 2);
    Point p = create_point(5.0, 5.0);

    TEST_ASSERT_FALSE(point_in_circumcicle(t, points, p));
}

void test_point_in_circumcircle_boundary(void){
    Point points[] = {
        create_point(0.0, 0.0),
        create_point(4.0, 0.0),
        create_point(0.0, 4.0)
    };

    Triangle t = create_triangle(0, 1, 2);
    Point p = create_point(4.0, 4.0);

    TEST_ASSERT_FALSE(point_in_circumcicle(t, points, p));
}

void test_point_in_circumcircle_collinear(void){
    Point points[] = {
        create_point(0.0, 0.0),
        create_point(2.0, 2.0),
        create_point(4.0, 4.0)
    };

    Triangle t = create_triangle(0, 1, 2);
    Point p = create_point(2.0, 3.0);

    TEST_ASSERT_FALSE(point_in_circumcicle(t, points, p));
}

void test_point_in_triangle_vertex(void){
    Point points[] = {
        create_point(0.0, 0.0),
        create_point(4.0, 0.0),
        create_point(0.0, 4.0)
    };

    Triangle t = create_triangle(0, 1, 2);
    Point p = create_point(0.0, 0.0);

    TEST_ASSERT_EQUAL_INT(1, point_in_triangle(p, t, points));
}



void test_point_in_triangle_outside_other_side(void)   {
    Point points[] = {
        create_point(0.0, 0.0),
        create_point(4.0, 0.0),
        create_point(0.0, 4.0)
    };

    Triangle t = create_triangle(0, 1, 2);
    Point p = create_point(5.0, 5.0);

    TEST_ASSERT_EQUAL_INT(0, point_in_triangle(p, t, points));
}

void test_point_in_triangle(void){
    Point points[] = {
        create_point(0.0, 0.0),
        create_point(4.0, 0.0),
        create_point(0.0, 4.0)
    };

    Triangle t = create_triangle(0, 1, 2);
    Point p_inside = create_point(2.0, 1.0);
    Point p_outside = create_point(5.0, 5.0);
    Point p_on_boundary = create_point(2.0, 0.0);

    TEST_ASSERT_TRUE(point_in_triangle(p_inside, t, points));
    TEST_ASSERT_FALSE(point_in_triangle(p_outside, t, points));
    TEST_ASSERT_TRUE(point_in_triangle(p_on_boundary, t, points));
}