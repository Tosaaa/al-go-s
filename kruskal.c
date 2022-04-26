#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "union_find.h"

#define MAX_SIZE 7

void swap(int *arr, int *idx, int a, int b) {
    int temp = arr[a];
    arr[a] = arr[b];
    arr[b] = temp;

    temp = idx[a];
    idx[a] = idx[b];
    idx[b] = temp;
    return;
}

int partition(int *arr, int *idx, int left, int right) {
    int mid = left + (right-left)/2; // to prevent O(n^2) when arr is already sorted in descending order.
    swap(arr, idx, left, mid);
    int pivot = left;
    int low = left+1;
    int high = right;

    while (1) {
        while (low <= right && arr[low] <= arr[pivot])
            low++;
        while (high >= left+1 && arr[high] > arr[pivot])
            high--;
        if (low > high) // already sorted
            break;
        swap(arr, idx, low, high);
    }
    
    swap(arr, idx, pivot, high);
    return high; //index of pivot
}

void qqsort(int *arr, int *idx, int left, int right) {
    if (left >= right) return;
    int pivot = partition(arr, idx, left, right);
    qqsort(arr, idx, left, pivot-1);
    qqsort(arr, idx, pivot+1, right);
    return;
}

Graph *kruskal(Graph *graph) {
    int v = graph->V;
    int e = (graph->E)/2;
    int (*edges)[2] = malloc(sizeof *edges * e);
    int *weight = malloc(sizeof *weight * e);
    int *idx = malloc(sizeof *idx * e);
    for (int i = 0 ; i < e; i++)
        idx[i] = i;
    int cnt = 0;

    GraphNode *walk;    
    for (int i = 0; i < v; i++) {
        walk = graph->adj[i];
        while (walk != NULL) {
            if (i < walk->val) { // only add when (start node) < (end node) to avoid duplicate
                edges[cnt][0] = i;
                edges[cnt][1] = walk->val;
                weight[cnt] = walk->weight;
                cnt++;
            }
            walk = walk->next;            
        }
    }

    qqsort(weight, idx, 0, e-1);

    Graph *dst = init_graph(v);
    int (*root)[2] = (int (*)[2])uf_init(v);
    for (int i = 0; i < e; i++) {
        if (!uf_same(root, edges[idx[i]][0], edges[idx[i]][1])) {
            uf_unite(root, edges[idx[i]][0], edges[idx[i]][1]);
            //printf("%d %d %d\n", edges[idx[i]][0], edges[idx[i]][1], weight[i]);
            setEdgeWeight(dst, edges[idx[i]][0], edges[idx[i]][1], weight[i]);
            setEdgeWeight(dst, edges[idx[i]][1], edges[idx[i]][0], weight[i]);
        }
    }

    uf_del(root);
    free(edges);
    free(weight);
    free(idx);
    return dst;
}

int main() {
    Graph *graph = init_graph(MAX_SIZE);
    int weight[MAX_SIZE][MAX_SIZE] = {
        {0, 7, INF, INF, 3, 10, INF},
        {7, 0, 4, 10, 2, 6, INF},
        {INF, 4, 0, 2, INF, INF, INF},
        {INF, 10, 2, 0, INF, 9, 4},
        {3, 2, INF, INF, 0, INF, 5},
        {10, 6, INF, 9, INF, 0, INF},
        {INF, INF, INF, 4, 5, INF, 0}
    };

    for (int i = 0; i < MAX_SIZE; i++) {
        for (int j = 0; j < MAX_SIZE; j++) {
            setEdgeWeight(graph, i, j, weight[i][j]);
        }
    }

    Graph *mst = kruskal(graph);
    traversal(mst);

    del_graph(graph);
    del_graph(mst);

    return 0;
}