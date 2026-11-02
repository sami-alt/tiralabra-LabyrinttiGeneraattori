#ifndef TRIANGLE_H
#define TRIANGLE_H  

typedef struct Triangle {
    int p1;
    int p2;
    int p3;
} Triangle;

Triangle createTriangle(int p1, int p2, int p3);

#endif // TRIANGLE_H