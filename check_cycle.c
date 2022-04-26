#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // to use sleep()
#include "graph.h" // use graph_list.c
#include "union_find.h"

#define MAX_SIZE 7

int isCycle(Graph *graph, int s);
int isCycle_helper(Graph *graph, int s, int *seq, int *parent);
int isCycle2(Graph *graph, int s);
int isCycle2_helper(Graph *graph, int s, int *visited, int *finished, int *parent);
int isCycle3(Graph *graph);


// only for undirected graphs
// prints cycle
int isCycle(Graph *graph, int s) {
    int v = graph->V;
    int *seq = malloc(sizeof *seq * v);
    for (int i = 0; i < v; i++)
        seq[i] = -1;

    int *parent = malloc(sizeof *parent * v);
    for (int i = 0; i < v; i++)
        parent[i] = i;

    int result = isCycle_helper(graph, s, seq, parent);

    free(seq);
    free(parent);
    return result;
}

int isCycle_helper(Graph *graph, int s, int *seq, int *parent) {
    static int result = 0;
    static int cnt = 0;
    seq[s] = cnt++;
    printf("current node: %d\n", s);

    GraphNode *walk = graph->adj[s];
    while (walk != NULL) {
        printf("adj node: %d\n", walk->val);
        if ((seq[walk->val] == -1) && (parent[s] != walk->val)) { // not visited && not parent => do DFS
            parent[walk->val] = s;
            isCycle_helper(graph, walk->val, seq, parent);
        }
        else if ((seq[walk->val] > -1) && (seq[s] > seq[walk->val]) && (parent[s] != walk->val)) { // visited(back edge) && not parent => cycle found
            // cycle found!
            result = 1;
            printf("cycle found!\n");
            printf("nodes forming the cycle: ");
            int tmp = s;
            while (tmp != walk->val) {
                printf("%d ", tmp); 
                tmp = parent[tmp];
            }
            printf("%d\n", walk->val);
        }
        // visited (forward edge) && not parent => ignore
        // not visited && parent => impossible
        walk = walk->next;
    }
    return result;
}

// only for directed graphs ?
// prints cycle
int isCycle2(Graph *graph, int s) {
    int v = graph->V;
    int *visited = calloc(v, sizeof *visited);
    int *finished = calloc(v, sizeof *finished);
    int *parent = malloc(sizeof *parent * v);
    for (int i = 0; i < v; i++)
        parent[i] = i;

    int result = isCycle2_helper(graph, s, visited, finished, parent);

    free(visited);
    free(finished);
    free(parent);
    return result;
}

int isCycle2_helper(Graph *graph, int s, int *visited, int *finished, int *parent) {
    static int result = 0;
    visited[s] = 1;
    //printf("%d ", s);

    GraphNode *walk = graph->adj[s];
    while (walk != NULL) {
        if (!visited[walk->val] && (parent[s] != walk->val)) { // not visited => do DFS
            parent[walk->val] = s;
            isCycle2_helper(graph, walk->val, visited, finished, parent);
        }
        else if (visited[walk->val] && (finished[walk->val] == 0) && (parent[s] != walk->val)) { // visited(back edge) && not parent => cycle found
            // cycle found!
            result = 1;
            printf("cycle found!\n");
            printf("nodes forming the cycle: ");
            int tmp = s;
            while (tmp != walk->val) {
                printf("%d ", tmp); 
                tmp = parent[tmp];
            }
            printf("%d\n", walk->val);
        }
        // visited && finished => ignore
        walk = walk->next;
    }
    finished[s] = 1;
    return result;
}

// only for undirected graphs (kruskal without sorting edge list)
// does not print cycle
int isCycle3(Graph *graph) {
    int v = graph->V;
    int e = (graph->E)/2;
    int (*edges)[2] = malloc(sizeof *edges * e);
    int *weight = malloc(sizeof *weight * e);
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

    int result = 0;
    int (*root)[2] = (int (*)[2])uf_init(e);
    for (int i = 0; i < e; i++) {
        if (!uf_same(root, edges[i][0], edges[i][1])) {
            uf_unite(root, edges[i][0], edges[i][1]);
            //printf("%d %d %d\n", edges[idx[i][0], edges[i][1], weight[i]);
        }
        else {
            result = 1;
            printf("cycle found!\n");
            printf("adjacent two nodes of the cycle: %d %d\n", edges[i][0], edges[i][1]);
        }
    }
    uf_del(root);
    free(edges);
    free(weight);
    return result;
}

int main() {
    Graph *graph = init_graph(MAX_SIZE);
    // int d1[MAX_SIZE][MAX_SIZE] = {
    //     {0, 1, 0, 0},
    //     {0, 0, 1, 1},
    //     {0, 0, 0, 1},
    //     {0, 0, 0, 0}
    // };
    // int d2[MAX_SIZE][MAX_SIZE] = {
    //     {0, 1, 0, 0},
    //     {0, 0, 1, 0},
    //     {0, 0, 0, 1},
    //     {0, 1, 0, 0}
    // };
    // int ud[MAX_SIZE][MAX_SIZE] = {
    //     {0, 1, 0, 0},
    //     {1, 0, 1, 1},
    //     {0, 1, 0, 1},
    //     {0, 1, 1, 0}
    // };
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

    printf("return value: %d\n", isCycle2(graph, 0));
    del_graph(graph);
    return 0;
}