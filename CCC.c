// Count connected components in a graph
#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

#define MAX_SIZE 5

void DFS(Graph *graph);
void DFS_helper(Graph *graph, int v, int *visited);

void DFS(Graph *graph) {
    int *visited = calloc(graph->V, sizeof *visited);
    
    for (int i = 0; i < graph->V; i++) {
        if (visited[i] == 0) {
            DFS_helper(graph, i, visited);
            printf("\n");
        }
    }
    
    free(visited);
    return;
}

void DFS_helper(Graph *graph, int v, int *visited) {
    visited[v] = 1;
    printf("%d ", v);

    GraphNode *walk = graph->adj[v];
    while (walk != NULL) {
        if (!visited[walk->val])
            DFS_helper(graph, walk->val, visited);
        walk = walk->next;
    }
    return;
}

int main() {
    Graph *graph = init_graph(MAX_SIZE);
    // int weight[MAX_SIZE][MAX_SIZE] = {
    //     {0, 1, INF, INF, 1, 1, INF},
    //     {1, 0, 1, 1, 1, 1, INF},
    //     {INF, 1, 0, 1, INF, INF, INF},
    //     {INF, 1, 1, 0, INF, 1, 1},
    //     {1, 1, INF, INF, 0, INF, 1},
    //     {1, 1, INF, 1, INF, 0, INF},
    //     {INF, INF, INF, 1, 1, INF, 0}
    // };

    int weight[MAX_SIZE][MAX_SIZE] = {
        {0, 1, INF, INF, INF},
        {1, 0, 1, INF, INF},
        {INF, 1, 0, INF, INF},
        {INF, INF, INF, 0, 1},
        {INF, INF, INF, 1, 0}
    };
    
    for (int i = 0; i < MAX_SIZE; i++) {
        for (int j = 0; j < MAX_SIZE; j++) {
            setEdgeWeight(graph, i, j, weight[i][j]);
        }
    }

    DFS(graph);

    del_graph(graph);
    return 0;
}