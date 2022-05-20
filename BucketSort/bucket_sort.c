/* 
 * Updated 2/17/2022 - Alexandra Stefan
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "list.h"


/* 
compile with -g to collect debugging info needed for Valgrind ( -lm links the math library): 
gcc -g bucket_sort.c list.c -lm

run with Valgrind:
valgrind --leak-check=full ./a.out

On some systems, but not all, you can also use the --show-leak-kinds=all flag:
valgrind --leak-check=full --show-leak-kinds=all ./a.out

run without Valgrind:
./a.out
*/

/* // recommended helper functions:
// function to insert a new node in a sorted list.
nodePT insert_sorted(nodePT L, nodePT newP);
//  function to sort an array sing bucket sort
void bucket_sort(int arr[], int N)
*/

void print_array(int arr[], int N){
    int j;
    printf("\n array: ");
    for(j= 0; j<N; j++){
        printf("%5d,", arr[j]);
    }
    printf("\n");
}

//-------------------------------------------------------------

int get_min(int arr[],int N){
    int min = arr[0];
    for (int i = 1; i < N; ++i) {
        if (arr[i] < min) min = arr[i];
    }
    return min;
}

int get_max(int arr[],int N){
    int max = arr[0];
    for (int i = 1; i < N; ++i) {
        if (arr[i] > max) max = arr[i];
    }
    return max;
}

nodePT sorted_insert(nodePT list, nodePT new_node) {
    nodePT prev = NULL, curr = list;
    while (curr != NULL && curr->data <= new_node->data) {
        prev = curr;
        curr = curr->next;
    }
    return insert_node(list,prev,new_node);
}

void push(nodePT Bucket[], int arr[], int N){
    int index = 0;
    for (int i = 0; i < N; ++i) {
        printf("\n----- List at index %d:",i);
        print_list_horiz(Bucket[i]);

        nodePT curr = Bucket[i];
        while (curr != NULL){
            arr[index++] = curr->data;
            curr = curr->next;
        }
        destroy_list(Bucket[i]);
    }
}

void bucketsort(int arr[], int N){
    nodePT Bucket[N];
    int min = get_min(arr,N), max = get_max(arr,N);

    for (int i = 0; i < N; ++i) {
        Bucket[i] = NULL;
    }
    printf("\nBucketsort: min = %d, max = %d, N = %d buckets\n",min,max,N);

    for (int i = 0; i < N; ++i) {
        int index = ((double)arr[i]-(double)min)*N/((double)max-(double)min+1);
        printf("arr[%d]  = %11d, idx = %d\n",i,arr[i],index);

        nodePT new = new_node(arr[i]);
        Bucket[index] = sorted_insert(Bucket[index],new);
    }
    push(Bucket,arr,N);
}

void run1(){
    int N;
    char buffer[51];

    printf("Enter the filename: ");
    scanf("%s",buffer);
    FILE *fp = fopen(buffer,"r");
    if(!fp) {
        printf("Could not open file \"%s\"\n", buffer);
        return;
    }

    fscanf(fp,"%d",&N);
    int arr[N];
    for (int i = 0; i < N && !feof(fp); ++i) fscanf(fp,"%d",&arr[i]);

    print_array(arr,N);
    bucketsort(arr, N);
    print_array(arr,N);
    fclose(fp);
}

int main()
{
    printf("This program will read a file name, load data for an array from there and print the sorted array.\n");
    printf("The array is sorted using bucket sort.\n");
    printf("This will be repeated as long as the user wants.\n");
    int option;
    do {
        run1();
        printf("\nDo you want to repeat? Enter 1 to repeat, or 0 to stop) ");
        char ch;
        scanf("%d%c",&option, &ch);  // ch is used to remove the Enter from the input buffer
    } while (option == 1);

   return 0;
}
