#ifndef PQ_H_
#define PQ_H_

typedef struct MaxPQ {
    int *arr;
    int n;
    int size; // size of arr allocated at heap area.
} MaxPQ;

MaxPQ *pq_init(int size);
void pq_insert(MaxPQ *pq, int val);
int pq_delMax(MaxPQ *pq);
int pq_isEmpty(MaxPQ *pq);
void pq_free(MaxPQ *pq);

#endif