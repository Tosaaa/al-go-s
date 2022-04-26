#include <stdio.h>
#include <stdlib.h>

#define MAX_LENGTH 8

void msort(int *arr, int left, int right);
void msort_helper(int* arr, int *sorted, int left, int right);
void merge(int *arr, int *sorted, int left, int right);

void msort(int* arr, int left, int right) {
    int len = right - left + 1;
    int *sorted = calloc(len, sizeof *sorted);
    msort_helper(arr, sorted, left, right);
    free(sorted);
}

void msort_helper(int* arr, int *sorted, int left, int right) {
    if (left >= right) return; // size 1
    int mid = left + (right-left)/2;
    msort_helper(arr, sorted, left, mid);
    msort_helper(arr, sorted, mid+1, right);
    merge(arr, sorted, left, right);
    return;
}

void merge(int *arr, int *sorted, int left, int right) {
    int mid = left + (right-left)/2; 
    int s1 = left;
    int s2 = mid + 1;
    int idx = left;
    while (1) {
        if (s1 > mid) { // case 1
            while (idx <= right)
                sorted[idx++] = arr[s2++];
            break;
        }
        else if (s2 > right) {// case 2
            while (idx <= right)
                sorted[idx++] = arr[s1++];
            break;
        }

        if (arr[s1] <= arr[s2]) 
            sorted[idx++] = arr[s1++];
        else
            sorted[idx++] = arr[s2++];
    }

    for (int i = left; i <= right; i++)
        arr[i] = sorted[i];
    return;
}

int main() {
    int arr[MAX_LENGTH] = {135, 25, 22, 22, 44, 14, 1, 4};

    for (int i = 0; i < MAX_LENGTH; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    msort(arr, 0, MAX_LENGTH-1);

    for (int i = 0; i < MAX_LENGTH; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}