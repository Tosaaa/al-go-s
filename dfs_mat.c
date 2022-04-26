#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

void DFS(Graph *graph, int v);
void DFS_helper(Graph *graph, int v, int *visited);

void DFS(Graph *graph, int v) {
    int *visited = calloc(graph->V, sizeof *visited);
    DFS_helper(graph, v, visited);
    free(visited);
    return;
}

void DFS_helper(Graph *graph, int v, int *visited) {
    visited[v] = 1;
    printf("%d ", v);

    for (int i = 0; i < graph->V; i++) {
        if (graph->adj[v][i].val && !visited[i])
            DFS_helper(graph, i, visited);
    }
    return;
}

int main() {
    int V = 7;
    Graph *graph = init_graph(V);
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 0);
    addEdge(graph, 1, 3);
    addEdge(graph, 1, 4);
    addEdge(graph, 2, 0);
    addEdge(graph, 2, 5);
    addEdge(graph, 2, 6);
    addEdge(graph, 3, 1);
    addEdge(graph, 4, 1);
    addEdge(graph, 5, 2);
    addEdge(graph, 6, 2);

    DFS(graph, 0);

    del_graph(graph);
    return 0;
}