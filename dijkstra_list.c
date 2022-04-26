#include <stdio.h>
#include <stdlib.h>
#include "graph.h" // use graph_list.c

#define MAX_SIZE 7

//TODO:
// find unvisited min을 PQ로 구현

void shortest_distance(Graph *graph, int s, int *dst) {
    int V = graph->V;
    GraphNode **weight = graph->adj;
    int visited_nodes = 0;
    int *visited = calloc(V, sizeof *visited); // storing visited nodes.
    int *d = malloc(sizeof *d * V); // storing distances.
    for (int i = 0; i < V; i++)
        d[i] = INF;
    d[s] = 0;

    while (visited_nodes < V) {
        // extract unvisited min
        int u_dist = INF;
        int u = -1;
        for (int i = 0; i < V; i++) {
            if (!visited[i] && (d[i] < u_dist)) {
                u_dist = d[i];
                u = i;
            }
        }
        if (u_dist == INF) break; // when the given graph is not connected graph

        visited[u] = 1;
        visited_nodes++;

        GraphNode *walk = weight[u];
        while (walk != NULL) {
            if (!visited[walk->val] && (d[u] + walk->weight < d[walk->val]))
                d[walk->val] = d[u] + walk->weight;
            walk = walk->next;
        }
    }

    for (int i = 0; i < V; i++)
        dst[i] = d[i];

    free(visited);
    free(d);
    return;
}

void shortest_path(Graph *graph, int s, int e, int *dst) {
    int V = graph->V;
    GraphNode **weight = graph->adj;
    int visited_nodes = 0;
    int *visited = calloc(V, sizeof *visited); // storing visited nodes.
    int *d = malloc(sizeof *d * V); // storing distances.
    for (int i = 0; i < V; i++)
        d[i] = INF;
    d[s] = 0;

    int *p = malloc(sizeof *p * V); // storing parents
    for (int i = 0; i < V; i++)
        p[i] = -1;

    while (visited_nodes < V) {
        // extract unvisited min
        int u_dist = INF;
        int u = -1;
        for (int i = 0; i < V; i++) {
            if (!visited[i] && (d[i] < u_dist)) {
                u_dist = d[i];
                u = i;
            }
        }
        if (u_dist == INF) break; // when the given graph is not connected graph

        visited[u] = 1;
        visited_nodes++;
        if (u == e) break;

        GraphNode *walk = weight[u];
        while (walk != NULL) {
            if (!visited[walk->val] && (d[u] + walk->weight < d[walk->val])) {
                d[walk->val] = d[u] + walk->weight;
                p[walk->val] = u;
            }
                
            walk = walk->next;
        }
    }

    // create path
    if (s == e) {
        dst[0] = s;
    }
    else {
        // backtrack to create path
        int idx = 0;
        dst[idx++] = e;
        while (p[e] != s) {
            dst[idx++] = p[e];
            e = p[e];        
        }
        dst[idx] = s;

        //reverse array
        int tmp;
        for (int i = 0; i <= idx/2; i++) {
            tmp = dst[i];
            dst[i] = dst[idx-i];
            dst[idx-i] = tmp;        
        }
    }
    
    free(visited);
    free(d);
    free(p);
    return;
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

    int d[MAX_SIZE];
    shortest_distance(graph, 0, d);

    for (int i = 0; i < MAX_SIZE; i++) {
        printf("%d ", d[i]);
    }
    printf("\n");


    for (int j = 0; j < MAX_SIZE; j++) {
        int path[MAX_SIZE];
        for (int i = 0; i < MAX_SIZE; i++)
            path[i] = -1;
        shortest_path(graph, 0, j, path);

        for (int i = 0; i < MAX_SIZE; i++) {
            if (path[i] == -1) break;
            printf("%d ", path[i]);
        }
        printf("\n");
    }
    
    traversal(graph);
    del_graph(graph);

    return 0;
}
