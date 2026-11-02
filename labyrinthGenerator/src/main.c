#include <stdio.h>

#include "point.h"
#include "triangle.h"

int main(void) {
    Point points[] = {
        {0, 0},  // A
        {4, 0},  // B
        {2, 2}   // C
    };

    Triangle t = createTriangle(0, 1, 2);

    Point p_inside = {2, 0.5};
    Point p_outside = {5, 2};

    printf("Area: %.2f\n",
        triangleArea(t, points));

    printf("Orientation: %d\n",
        getTriangleOrientation(t, points));

    printf("Inside: %d\n",
        pointInCircumcircle(t, points, p_inside));

    printf("Outside: %d\n",
        pointInCircumcircle(t, points, p_outside));

    return 0;
}