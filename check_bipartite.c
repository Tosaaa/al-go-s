// check for bipartite graph
// using DFS

#include <stdio.h>
#include <stdlib.h>

#include "graph.h"  // use graph_list

#define MAX_SIZE 5

int isBipartiteDFS(Graph *graph, int v);
int DFS_helper(Graph *graph, int v, int *visited, int *color);
int isBipartiteMaxFlow(Graph *graph, int v);

int isBipartiteDFS(Graph *graph, int v) {
    int *visited = calloc(graph->V, sizeof *visited);
    int *color = malloc(sizeof *color * graph->V);
    for (int i = 0; i < graph->V; i++) {
        color[i] = -1;
    }
    color[v] = 0;
    int ret = DFS_helper(graph, v, visited, color);
    free(visited);
    free(color);
    return ret;
}

int DFS_helper(Graph *graph, int v, int *visited, int *color) {
    static int isBipartite = 1;
    visited[v] = 1;
    printf("node: %d, color: %d\n", v, color[v]);

    GraphNode *walk = graph->adj[v];
    while (walk != NULL && isBipartite == 1) {
        if (!visited[walk->val]) {
            color[walk->val] = !color[v];
            DFS_helper(graph, walk->val, visited, color);
        } else if (color[walk->val] == color[v]) {
            printf("not bipartite\n");
            isBipartite = 0;
        }
        walk = walk->next;
    }
    return isBipartite;
}

int isBipartiteMaxFlow(Graph *graph, int v) {
    
    return 0;
}


int main() {
    Graph *graph = init_graph(MAX_SIZE);
    // dijkstra graph
    // int weight[MAX_SIZE][MAX_SIZE] = {
    //     {0, 7, INF, INF, 3, 10, INF},
    //     {7, 0, 4, 10, 2, 6, INF},
    //     {INF, 4, 0, 2, INF, INF, INF},
    //     {INF, 10, 2, 0, INF, 9, 4},
    //     {3, 2, INF, INF, 0, INF, 5},
    //     {10, 6, INF, 9, INF, 0, INF},
    //     {INF, INF, INF, 4, 5, INF, 0}
    // };

    // 육각형
    // int weight[MAX_SIZE][MAX_SIZE] = {
    //     {0, 1, INF, INF, INF, 1},
    //     {1, 0, 1, INF, INF, INF},
    //     {INF, 1, 0, 1, INF, INF},
    //     {INF, INF, 1, 0, 1, INF},
    //     {INF, INF, INF, 1, 0, 1},
    //     {1, INF, INF, INF, 1, 0}};

    // 오각형
    int weight[MAX_SIZE][MAX_SIZE] = {
        {0, 1, INF, INF, 1},
        {1, 0, 1, INF, INF},
        {INF, 1, 0, 1, INF},
        {INF, INF, 1, 0, 1},
        {1, INF, INF, 1, 0}};

    for (int i = 0; i < MAX_SIZE; i++) {
        for (int j = 0; j < MAX_SIZE; j++) {
            setEdgeWeight(graph, i, j, weight[i][j]);
        }
    }

    printf("isBipartite: %d\n", isBipartiteDFS(graph, 0));

    del_graph(graph);

    return 0;
}