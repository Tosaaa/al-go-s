#ifndef PQ_H_
#define PQ_H_

typedef struct MinPQ {
    int *arr;
    int n;
    int size; // size of arr allocated at heap area.
} MinPQ;

MinPQ *pq_init(int size);
void pq_insert(MinPQ *pq, int val);
int pq_delMin(MinPQ *pq);
int pq_isEmpty(MinPQ *pq);
void pq_free(MinPQ *pq);

#endif