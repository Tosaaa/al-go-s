#include <stdio.h>
#include <stdlib.h>
#include "graph.h" // use graph_list.c

#define MAX_SIZE 3

//TODO:
// any way to use bellman-ford for undirected graphs?

// bellman-ford is only valid for directed graphs
void shortest_distance(Graph *graph, int s, int *dst) {
    int v = graph->V;
    int e = graph->E;
    int *d = malloc(sizeof *d * v); // storing distances.
    for (int i = 0; i < v; i++)
        d[i] = INF;
    d[s] = 0;
    int (*edges)[3] = malloc(sizeof *edges * e);

    GraphNode *walk;
    int cnt = 0;
    for (int i = 0; i < v; i++) {
        walk = graph->adj[i];
        while (walk != NULL) {
            edges[cnt][0] = i;
            edges[cnt][1] = walk->val;
            edges[cnt][2] = walk->weight;
            cnt++;
            walk = walk->next;            
        }
    }

    for (int i = 0; i < v-1; i++) { // repeat v-1 times
        for (int j = 0; j < e; j++) {
            int a, b, w;
            a = edges[j][0];
            b = edges[j][1];
            w = edges[j][2];
            if ((d[a] < INF) && (d[b] > d[a] + w)) // edge relaxation
                d[b] = d[a] + w;
        }
    }

    int valid = 1;
    for (int j = 0; j < e; j++) { // if update occurs, the graph has negative cycle.
            int a, b, w;
            a = edges[j][0];
            b = edges[j][1];
            w = edges[j][2];
            if ((d[a] < INF) && (d[b] > d[a] + w))
                valid = 0;
    }

    if (valid == 0) {
        printf("Bellman-Ford impossible: negative cycle detected.\n");
        for (int i = 0; i < v; i++)
            dst[i] = -1;
    }
    else {
        for (int i = 0; i < v; i++)
            dst[i] = d[i];
    }
    
    free(d);
    free(edges);
    return;
}

void shortest_path(Graph *graph, int s, int e, int *dst) {

}

int main() {
    Graph *graph = init_graph(MAX_SIZE);
    // int weight[MAX_SIZE][MAX_SIZE] = {
    //     {0, 7, INF, INF, 3, 10, INF},
    //     {7, 0, 4, 10, 2, 6, INF},
    //     {INF, 4, 0, 2, INF, INF, INF},
    //     {INF, 10, 2, 0, INF, 9, 4},
    //     {3, 2, INF, INF, 0, INF, 5},
    //     {10, 6, INF, 9, INF, 0, INF},
    //     {INF, INF, INF, 4, 5, INF, 0}
    // };

    int weight2[MAX_SIZE][MAX_SIZE] = { 
        {0, 20, INF},
        {INF, 0, -15},
        {INF, INF, 0}
    };

    for (int i = 0; i < MAX_SIZE; i++) {
        for (int j = 0; j < MAX_SIZE; j++) {
            setEdgeWeight(graph, i, j, weight2[i][j]);
        }
    }

    int d[MAX_SIZE];
    shortest_distance(graph, 0, d);

    for (int i = 0; i < MAX_SIZE; i++) {
        printf("%d ", d[i]);
    }
    printf("\n");


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
    
    traversal(graph);
    del_graph(graph);

    return 0;
}
