#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "graph.h"

void BFS(Graph* graph, int v);
void BFS_helper(Graph* graph, Queue *queue,  int v, int *visited);

void BFS(Graph *graph, int v) {
    int *visited = calloc(graph->V, sizeof *visited);
    Queue *queue = init_queue();
    BFS_helper(graph, queue, v, visited);
    free(visited);
    del_queue(queue);
    return;
}

void BFS_helper(Graph *graph, Queue *queue, int v, int *visited) {
    visited[v] = 1;
    enqueue(queue, v);

    while(!isEmpty(queue)) {
        int r = dequeue(queue);
        printf("%d ", r);
        GraphNode *walk = graph->adj[r];
        while (walk != NULL) {
            if (!visited[walk->val]) {
                enqueue(queue, walk->val);
                visited[walk->val] = 1;
            }
            walk = walk->next;
        }
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

    BFS(graph, 1);

    del_graph(graph);
    return 0;
}