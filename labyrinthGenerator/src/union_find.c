#include "union_find.h"

int union_find_init(UnionFind *uf, int size){
    if (!uf || size < 0 )
        return -1;

    uf->parent = NULL;
    uf->rank = NULL;
    uf->size = 0;

    uf->parent = (int*)malloc(size * sizeof(int));
    uf->rank = (int*)malloc(size * sizeof(int));
    if (!uf->parent || !uf->rank){
        union_find_free(uf);
        return -1;
    }

    uf->size = size;

    for (int i = 0; i < size; i++) {
        uf->parent[i] = i;
        uf->rank[i] = 0;
    }
    return 1;
};

int union_find_find(UnionFind *uf, int element){
    if (!uf || element < 0 || element >= uf->size)
        return -1;

    int root = element;
    while (uf->parent[root] != root) {
        root = uf->parent[root];
    }

    while (uf->parent[element] != element) {
        int next = uf->parent[element];
        uf->parent[element] = root;
        element = next;
    }
    return root;
};

int union_find_union(UnionFind *uf, int element1, int element2){
    int root1 = union_find_find(uf, element1);
    int root2 = union_find_find(uf, element2);
    if (root1 == -1 || root2 == -1)
        return -1;  
    if (root1 == root2)
        return 0;
    if (uf->rank[root1] < uf->rank[root2])
        uf->parent[root1] = root2;
    else {
        if (uf->rank[root1] > uf->rank[root2])
            uf->parent[root2] = root1;
        else {
            uf->parent[root2] = root1;
            uf->rank[root1]++;
        }
    }
    return 1;
}

int union_find_connected(UnionFind *uf, int element1, int element2){
    int root1 = union_find_find(uf, element1);
    int root2 = union_find_find(uf, element2);
    if (root1 == -1 || root2 == -1)
        return -1;  
    return root1 == root2;
}

void union_find_free(UnionFind *uf){
    if (!uf)
        return;
    free(uf->parent);
    free(uf->rank);
    uf->parent = NULL;
    uf->rank = NULL;
    uf->size = 0;
}