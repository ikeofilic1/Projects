#include <stdlib.h>
#include <stdio.h>

#include "heap.h"  

//#define DEBUG 1


struct heap_struct make_heap_empty(int cap){
    struct heap_struct new;
    new.N = 0; 
    new.capacity = cap;
    new.items = malloc(sizeof(int) * cap);
    return new;
}

struct heap_struct make_heap(int N, int * arr){
    struct heap_struct new;
    new.N = N; 
    new.capacity = N;
    new.items = arr;
    for (int i = (N-1)/2; i >= 0; --i)
        heapify(i, N, arr);

    return new;
}

void destroy(struct heap_struct * heapP){
    heapP->N = 0;
    heapP->capacity = 0;
    free(heapP->items);
    heapP->items = 0x0;
}

void print_array(int *arr, int N) {
    for (int i = 0; i < N; ++i) 
        printf("%7d, ", arr[i]);
}

void print_heap(struct heap_struct heapS){
    printf("\nHeap: size: %d, capacity: %d\n", heapS.N, heapS.capacity);
    printf("indexes: ");
	for (int i = 0; i < heapS.N; ++i) 
            printf("%7d, ", i);

    printf("\nvalues:  ");
    print_array(heapS.items, heapS.N);    
    printf("\n");
}


void swim_up(int idx, int * arr){
    for (int p = idx; idx > 0 && p == idx;) {
        p = (idx-1)/2;
        if (arr[p] < arr[idx]) {
            int temp = arr[p];
            arr[p] = arr[idx];
            arr[idx] = temp;
            idx = p;
        }
    }
}

//aka sinkdown
void heapify(int i, int N, int * arr){
    if (i < 0 || N == 0) return;
    while (i <= (N/2)-1) {
        int left = 2*i + 1, right = left + 1, largest = i;
        if (left < N && arr[left] > arr[largest])
            largest = left;
        if (right < N && arr[right] > arr[largest])
            largest = right;

        if (largest == i) return;
        else {
            int temp = arr[i];
            arr[i] = arr[largest];
            arr[largest] = temp;
            i = largest;
        }
    }
}

void add(struct heap_struct * heapP, int new_item){
	if (heapP->N == heapP->capacity) {
        printf("\nresizing...");
		heapP->capacity *= 2;
		heapP->items = realloc(heapP->items, sizeof(int)*heapP->capacity);
	}

    heapP->items[heapP->N++] = new_item;
    swim_up(heapP->N - 1, heapP->items);
}

int peek(struct heap_struct heapS){
	return heapS.items[0];
}


int poll(struct heap_struct * heapP){
    if (heapP->N == 0) {
        printf("Heap is empty.\n");
        return 0;
    }
    int head = heapP->items[0];
    heapP->items[0] = heapP->items[--(heapP->N)];
    heapify(0, heapP->N, heapP->items);

    return head;
}

int* create_copy_malloc(int *arr, int N) {
    int *res = malloc(N*sizeof(int));
    for (int i = 0; i < N; ++i) 
        res[i] = arr[i];
    return res;
}

int* heap_sort(struct heap_struct heapS, int * sz){
    if (heapS.N == 0) {
        printf("Heap is empty");
        return 0x0;
    }
    *sz = heapS.N;
    int *sorted = create_copy_malloc(heapS.items, *sz);
    for (int i = 1; i <= *sz; ++i) {
        int temp = sorted[0];
        sorted[0] = sorted[*sz-i];
        sorted[*sz-i] = temp;
        heapify(0, (*sz)-i, sorted);
    }
    return sorted;
}
