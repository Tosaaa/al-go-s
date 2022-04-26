#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

Graph *init_graph(int v) { 
    Graph *graph = malloc(sizeof *graph);
    graph->V = v;
    graph->E = 0;
    graph->adj = calloc(v, sizeof *(graph->adj));
    return graph;
}

void addEdge(Graph *graph, int v, int w) { // adjacency list based on linked list.
    graph->E++; // assuming there was no edge between v, w
    GraphNode *node = malloc(sizeof *node);
    node->val = w;
    node->next = NULL;
    node->weight = 1;

    if (graph->adj[v] == NULL) {
        graph->adj[v] = node;
        return;
    }

    GraphNode *walk = graph->adj[v];
    for (; walk->next != NULL; walk = walk->next); // walk becomes tail.
    walk->next = node;
    return;
}

void setEdgeWeight(Graph *graph, int v, int w, int weight) {
    if (weight == 0 || weight == INF) return;
    graph->E++; // assuming there was no edge between v, w
    GraphNode *node = malloc(sizeof *node);
    node->val = w;
    node->next = NULL;
    node->weight = weight;

    if (graph->adj[v] == NULL) {
        graph->adj[v] = node;
        return;
    }

    GraphNode *walk = graph->adj[v];
    for (; walk->next != NULL; walk = walk->next); // walk becomes tail.
    walk->next = node;
    return;
}

int isEdge(Graph *graph, int v, int w) {
    GraphNode *walk = graph->adj[v];
    while (walk != NULL) {
        if (walk->val == w)
            return 1;
        walk = walk->next;
    }
    return 0;
}

void del_graph(Graph *graph) {
    if (graph == NULL) return;
    if (graph->V == 0) {
        free(graph);
        return;
    }

    GraphNode *walk;
    GraphNode *temp;
    for (int i = 0; i < graph->V; i++) {
        walk = graph->adj[i];
        while (walk != NULL) {
            temp = walk;
            walk = walk->next;
            free(temp);
        }
    }
    free(graph->adj);
    free(graph);
    return;
}

void traversal(Graph *graph) { // adj mat으로 출력?
    int v = graph->V;
    GraphNode *walk;
    for (int i = 0; i < v; i++) {
        walk = graph->adj[i];
        while (walk != NULL) {
            printf("%d -> %d: %d\n", i, walk->val, walk->weight);
            walk = walk->next;
        }
        printf("----------\n");
    }
}
