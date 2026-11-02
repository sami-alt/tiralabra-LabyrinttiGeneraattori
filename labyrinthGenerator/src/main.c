
#include <stdio.h>

#include "point.h"
#include "triangle.h"

int main(void) {
    Point points[] = {
        createPoint(10, 10),
        createPoint(50, 10),
        createPoint(30, 40)
    };

    Triangle triangle = createTriangle(0, 1, 2);

    printf("Triangle points:\n");

    printf("A: (%.2f, %.2f)\n",
        points[triangle.p1].x,
        points[triangle.p1].y);

    printf("B: (%.2f, %.2f)\n",
        points[triangle.p2].x,
        points[triangle.p2].y);

    printf("C: (%.2f, %.2f)\n",
        points[triangle.p3].x,
        points[triangle.p3].y);

    return 0;
}