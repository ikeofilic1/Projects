#include <stdio.h>
#include <stdlib.h>

#include "heap.h"

int main() {
    char fname[51];
    FILE *fp;

    printf("Enter the filename: ");
    scanf("%s", fname);
    fp = fopen(fname, "r");
    if (!fp) {
        printf("Could not open the file.\n");
        return -1;
    }

    int N = 0, *arr;
    fscanf(fp,"%d",&N);
    if (N <= 0) {
        fclose(fp);
        return -1;
    }
    arr = malloc(N*sizeof(int));
    for (int i = 0; i < N && !feof(fp); ++i) 
    	fscanf(fp,"%d",&arr[i]);

    struct heap_struct heap = make_heap(N, arr);         
    print_heap(heap);
    fscanf(fp,"%d",&N);

    if (N <= 0) {
        destroy(&heap);
        fclose(fp);
        return -1;
    }

    for (int i = 1; i <= N && !feof(fp); ++i) {
    	char op[11];
    	fscanf(fp," %s", op);
    	printf("\nOperation number %d, String: %s\n", i, op);

    	if (op[0] == 'p' || op[0] == 'P') {
    		printf("peek: %10d", peek(heap));
    	}
    	else if (op[0] == 'S' || op[0] == 's') {
            printf("sorted: ");
            int sz = 0, *sorted = heap_sort(heap, &sz);
            print_array(sorted, sz);
            free(sorted);
    	}
    	else if (op[0] == '*') {
            printf("removed: %7d", poll(&heap));
    	}
    	else {
    		int val = atoi(op);
    		printf("add: %10d", val);
    		add(&heap, val);
    	}

    	print_heap(heap);
    }

    destroy(&heap);
    fclose(fp);
    return 0;
}