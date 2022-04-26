#ifndef GRAPH_H_
#define GRAPH_H_

#include <limits.h>
#define INF INT_MAX

typedef struct GraphNode {
    int val;
    int weight;
    struct GraphNode *next;
} GraphNode;

typedef struct Graph {
    int V;
    int E; // # of directed edges
    GraphNode **adj;
} Graph;

Graph *init_graph(int v); // v nodes, returns a graph with weight = 0 for diagonal elements, INF otherwise.
void addEdge(Graph *graph, int v, int w); // v->w (directed)
void setEdgeWeight(Graph *graph, int v, int w, int weight); // v->w (directed)
int isEdge(Graph *graph, int v, int w); // returns 1 if there is an edge from v to w, otherwise 0.
void del_graph(Graph *graph);
void traversal(Graph *graph); // prints adjacency matrix

#endif