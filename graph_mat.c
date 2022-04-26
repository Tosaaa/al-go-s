#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

Graph *init_graph(int v) {
    Graph *graph = malloc(sizeof *graph);
    graph->V = v;
    graph->E = 0;
    graph->adj = calloc(v, sizeof *(graph->adj));
    for (int i = 0; i < v; i++)
        graph->adj[i] = calloc(v, sizeof *(graph->adj[i]));
    for (int i = 0; i < v; i++) {
        for (int j = 0 ; j < v; j++) {
            if (i == j) continue;
            graph->adj[i][j].val = INF;
        }
    }
    return graph;
}

void addEdge(Graph *graph, int v, int w) { // adjacency mat.
    graph->E++;
    graph->adj[v][w].val += 1;
    return;
}

void setEdgeWeight(Graph *graph, int v, int w, int weight) {
    if (weight != 0 && weight != INF)
        graph->E++;
    graph->adj[v][w].val = weight;
    return;
}

int isEdge(Graph *graph, int v, int w) {
    printf("isEdge: not implemente yet.\n");
    return 0;
}

void del_graph(Graph *graph) { 
    if (graph == NULL) return;
    if (graph->V == 0) {
        free(graph);
        return;
    }

    for (int i = 0; i < graph->V; i++) {
        free(graph->adj[i]);
    }
    free(graph->adj);
    free(graph);
    return;
}

void traversal(Graph *graph) {
    int v = graph->V;
    for (int i = 0; i < v; i++) {
        for (int j = 0; j < v; j++)
            if (graph->adj[i][j].val == INF)
                printf("- ");
            else
                printf("%d ", graph->adj[i][j].val);
        printf("\n");
    }
}
