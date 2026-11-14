#ifndef UNION_FIND_H
#define UNION_FIND_H

#include <stdlib.h>

typedef struct UnionFind {
    int* parent;
    int* rank;
    int size;
} UnionFind;

int union_find_init(UnionFind* uf, int size);
int union_find_find(UnionFind* uf, int element);
int union_find_union(UnionFind* uf, int element1, int element2);
int union_find_connected(UnionFind* uf, int element1, int element2);
void union_find_free(UnionFind* uf);

#endif // UNION_FIND_H