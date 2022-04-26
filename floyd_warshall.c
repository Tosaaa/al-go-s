#include <stdio.h>
#include <stdlib.h>
#include "graph.h" // use graph_mat.c

#define MAX_SIZE 7

//TODO:

void shortest_distance(Graph *graph, int s, int **d) { // only for directed graph
    int V = graph->V;
    GraphNode **weight = graph->adj;
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            d[i][j] = weight[i][j].val;
        }
    }

    int valid = 1;
    for (int k = 0; k < V && valid == 1; k++) {
        for (int i = 0; i < V && valid == 1; i++) {
            for (int j = 0; j < V && valid == 1; j++) {
                if ((d[i][k] < INF) && (d[k][j] < INF) && (d[i][j] > d[i][k] + d[k][j]))
                    d[i][j] = d[i][k] + d[k][j];
                if (i == j && d[i][j] < 0) valid = 0;
            }
        }
    }
    
    if (valid == 0)
        printf("Floyd-Warshall impossible: negative cycle detected.\n");

    return;
}

void shortest_path(Graph *graph, int s, int e, int *dst) {
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

    // int weight2[MAX_SIZE][MAX_SIZE] = { // to test negative cycle.
    //     {0, 20, 10},
    //     {20, 0, -15},
    //     {10, -15, 0}
    // };

    for (int i = 0; i < MAX_SIZE; i++) {
        for (int j = 0; j < MAX_SIZE; j++) {
            setEdgeWeight(graph, i, j, weight[i][j]);
        }
    }

    int **d = malloc(sizeof *d * MAX_SIZE);
    for (int i = 0; i < MAX_SIZE; i++) {
        d[i] = malloc(sizeof **d * MAX_SIZE);
    }
    shortest_distance(graph, 0, d);

    for (int i = 0; i < MAX_SIZE; i++) {
        for (int j = 0; j < MAX_SIZE; j++) {
            if (d[i][j] == INF)
                printf("- ");
            else
                printf("%d ", d[i][j]);
        }
        printf("\n");
    }
    


    // for (int j = 0; j < MAX_SIZE; j++) {
    //     int path[MAX_SIZE];
    //     for (int i = 0; i < MAX_SIZE; i++)
    //         path[i] = -1;
    //     shortest_path(graph, 0, j, path);

    //     for (int i = 0; i < MAX_SIZE; i++) {
    //         if (path[i] == -1) break;
    //         printf("%d ", path[i]);
    //     }
    //     printf("\n");
    // }
    
    //traversal(graph);
    del_graph(graph);

    return 0;
}
