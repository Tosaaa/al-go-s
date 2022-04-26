// Max Flow
// Ford-Fulkerson with BFS (Edmonds-Karp)

#include <stdio.h>
#include <stdlib.h>

#include "graph.h"  // use graph_list
#include "queue.h"

#define MAX_SIZE 6

void maxFlow(Graph *graph, int s, int t);
int findPath(Graph *graph, int s, int t, int *path);
int findPathUtil(Graph *graph, Queue *queue, int s, int t, int *visited, int *path);

// s: source, t: sink, O(VE^2)?
void maxFlow(Graph *graph, int s, int t) {
    if (s == t) {
        printf("source is equal to sink\n");
        return;
    } else if (t >= graph->V) {
        printf("sink is too large\n");
        return;
    }
    int maxflow = 0;
    int *path = malloc(sizeof *path * graph->V);

    // 최대 VE번 반복
    while (1) {
        for (int i = 0; i < graph->V; i++)
            path[i] = -1;

        //O(E)
        if (!findPath(graph, s, t, path)) {  // no path, max_flow found
            printf("Max Flow found: %d\n", maxflow);
            break;
        } else {  // update
            int len = 0;
            for (int i = 0; i < graph->V; i++) {
                if (path[i] == -1) break;
                printf("%d ", path[i]);
                len++;
            }
            printf("\n");

            // find min
            GraphNode *walk;
            int min = INF;

            // 아래 반복문은 최악의 경우 O(E)
            for (int i = 0; i < len; i++) {
                //printf("%d -> %d\n", path[i], path[i+1]);
                walk = graph->adj[path[i]];
                while (walk != NULL) {
                    if (walk->val == path[i + 1] && walk->weight < min) {
                        min = walk->weight;
                    }
                    walk = walk->next;
                }
            }
            maxflow += min;  // add incremented flow
            printf("incremented flow: %d, current maxflow: %d\n", min, maxflow);
            //traversal(graph);

            //increase forward flow (decrease weight)
            // 아래 반복문은 최악의 경우 O(E)
            for (int i = 0; i < len; i++) {
                walk = graph->adj[path[i]];
                while (walk != NULL) {
                    if (walk->val == path[i + 1]) {
                        walk->weight -= min;
                    }
                    walk = walk->next;
                }
            }
            //traversal(graph);

            //decrease backward flow (increase weight)
            // 아래 반복문은 최악의 경우 O(E)
            for (int i = len - 1; i > 0; i--) {
                int isEdge = 0;
                //printf("%d -> %d\n", path[i], path[i-1]);
                walk = graph->adj[path[i]];
                while (walk != NULL) {
                    if (walk->val == path[i - 1]) {
                        walk->weight += min;
                        isEdge = 1;
                    }
                    walk = walk->next;
                }
                if (!isEdge) setEdgeWeight(graph, path[i], path[i - 1], min);
            }
            //traversal(graph);
        }
    }
    //free(path);
    return;
}

// use BFS to find a residual capacity(증가 경로) from source to sink => Edmonds-Karp
int findPath(Graph *graph, int s, int t, int *path) {
    int *visited = calloc(graph->V, sizeof *visited);
    Queue *queue = init_queue();
    int valid = findPathUtil(graph, queue, s, t, visited, path);
    free(visited);
    del_queue(queue);
    return valid;
}

int findPathUtil(Graph *graph, Queue *queue, int s, int t, int *visited, int *path) {
    visited[s] = 1;
    enqueue(queue, s);
    int valid = 0;

    // storing parents
    int *p = malloc(sizeof *p * graph->V);
    for (int i = 0; i < graph->V; i++)
        p[i] = -1;

    while (!isEmpty(queue)) {
        int r = dequeue(queue);
        // found path from source to sink
        if (r == t) {
            valid = 1;  // to check if there is a path.
            break;
        }

        GraphNode *walk = graph->adj[r];
        while (walk != NULL) {
            if (!visited[walk->val] && (walk->weight > 0)) {
                enqueue(queue, walk->val);
                visited[walk->val] = 1;
                p[walk->val] = r;  // sets parent info
            }
            walk = walk->next;
        }
    }

    // if there is no path
    if (!valid) {
        free(p);
        return 0;
    } else {
        // backtrack to create path
        int idx = 0;
        path[idx++] = t;
        while (p[t] != s) {
            path[idx++] = p[t];
            t = p[t];
        }
        path[idx] = s;

        //reverse array
        int tmp;
        for (int i = 0; i <= idx / 2; i++) {
            tmp = path[i];
            path[i] = path[idx - i];
            path[idx - i] = tmp;
        }

        free(p);
        return 1;
    }
}

int main() {
    Graph *graph = init_graph(MAX_SIZE);

    // book example
    // int weight[MAX_SIZE][MAX_SIZE] = {
    //     {0, 5, INF, 4, INF, INF},
    //     {INF, 0, 6, INF, INF, INF},
    //     {INF, INF, 0, INF, 8, 5},
    //     {INF, 3, INF, 0, 1, INF},
    //     {INF, INF, INF, INF, 0, 2},
    //     {INF, INF, INF, INF, INF, 0}};

    // ratsgo's example
    // int weight[MAX_SIZE][MAX_SIZE] = {
    //     {0, 2, 5, INF},
    //     {INF, 0, 1, 4},
    //     {INF, INF, 0, 3},
    //     {INF, INF, INF, 0}};

    // gazelle's example
    int weight[MAX_SIZE][MAX_SIZE] = {
        {0, 7, INF, 5, INF, INF},
        {INF, 0, 3, 5, INF, INF},
        {INF, INF, 0, 2, INF, 6},
        {INF, INF, INF, 0, 9, INF},
        {INF, INF, 2, INF, 0, 4},
        {INF, INF, INF, INF, INF, 0}};

    for (int i = 0; i < MAX_SIZE; i++) {
        for (int j = 0; j < MAX_SIZE; j++) {
            setEdgeWeight(graph, i, j, weight[i][j]);
        }
    }
    //traversal(graph);
    maxFlow(graph, 0, 5);

    del_graph(graph);
}