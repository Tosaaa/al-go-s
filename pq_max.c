#include <stdio.h>
#include <stdlib.h>
#include "pq_max.h"

#define DEFAULT_SIZE 10

void swim(MaxPQ *pq, int k);
void sink(MaxPQ *pq, int k);
void swap(MaxPQ *pq, int a, int b);

void swim(MaxPQ *pq, int k) {
    while ((k > 1) && (pq->arr[k/2] < pq->arr[k])) {
        swap(pq, k, k/2);
        k = k/2;
    }
}

void sink(MaxPQ *pq, int k) {
    while (2*k <= pq->n) {
        int j = 2*k;
        if ((j < pq->n) && (pq->arr[j] < pq->arr[j+1]))
            j++;
        if (pq->arr[k] >= pq->arr[j]) break;
        swap(pq, k, j);
        k = j;
    }
}

void swap(MaxPQ *pq, int a, int b) {
    int temp = pq->arr[a];
    pq->arr[a] = pq->arr[b];
    pq->arr[b] = temp;
    return;
}

MaxPQ *pq_init(int size) {
    MaxPQ *pq = malloc(sizeof *pq);
    if (size <= 0)
        size = DEFAULT_SIZE;
    pq->arr = malloc(sizeof *(pq->arr) * size);
    pq->n = 0;
    pq->size = size;
    return pq;
}

void pq_insert(MaxPQ *pq, int val) {
    // dynamically increasing size
    if (pq->n + 1>= pq->size) { // index가 1부터 시작하기 때문에 pq->n + 1과 pq->size 를! 비교해야 함.
        int *tmp = realloc(pq->arr, (pq->size)*2*(sizeof *(pq->arr)));
        if (tmp == NULL) {
            fprintf(stderr, "pq_insert: realloc failed.\n");
            return;
        }
        pq->arr = tmp;
        pq->size *= 2;
    }

    pq->arr[++(pq->n)] = val;
    swim(pq, pq->n);
}

int pq_delMax(MaxPQ *pq) {
    // dynamically descreasing size
    if ((pq->n + 1) * 4 <= pq->size) {
        int *tmp = realloc(pq->arr, (pq->size)/2*(sizeof *(pq->arr)));
        if (tmp == NULL) {
            fprintf(stderr, "pq_delMax: realloc failed.\n");
            return -1;
        }
        pq->arr = tmp;
        pq->size /= 2;
    }

    int max = pq->arr[1];
    swap(pq, 1, (pq->n)--);
    sink(pq, 1);
    //pq->arr[pq->n + 1] = 0; // 굳이 필요 없을 듯.
    return max;
}

int pq_isEmpty(MaxPQ *pq) {
    return !(pq->n);
}

void pq_free(MaxPQ *pq) {
    free(pq->arr);
    free(pq);
    return;
}

// int main() {
//     MaxPQ *pq = pq_init(30);
//     for (int i = 1; i <= 20; i++) {
//         pq_insert(pq, i);
//         printf("i: %d, pq->n: %d, pq->size: %d\n", i, pq->n, pq->size);
//     }

//     for (int i = 1; i <= 20; i++) {
//         int max = pq_delMax(pq);
//         printf("i: %d, pq->n: %d, pq->size: %d, max: %d\n", i, pq->n, pq->size, max);
//         //printf("%d ", pq->arr[i]);
//     }
//     //printf("\n");
//     pq_free(pq);

//     return 0;
// }