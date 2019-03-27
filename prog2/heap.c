/*
 * Author: Alexey A. Munishkin
 * 
 * File name: heap.c
 * Date: 4/30/2013
 * Class: CMPS 101
 * 
 * This ADT implemenation of the module 'heap' allows the user to use the different
 * operations to create a priority queque data structure, which is based on the 
 * binary tree.
 */

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#define TRUE  1 // Elementary boolean values
#define FALSE 0

#define TOP 1 // Top of priority queque is 1 not 0 for easy mangement
#define NONUMBER -1 // Used to indicate stop for deleteMax()

/**************************************************************************
 * Implemenation:
 *    See heap.h for details on the undocumented functions below.
 *************************************************************************/
/*------------------------------------------------------------------------*
 * Structures.
 *-----------------------------------------------------------------------*/
struct heapArray{
    int maxSize;
    int numElements;   // For easy mangement of priority data amount.
    int* priorityQue;  // Storage of priority data.
};                     // NOTE: Made to point to an array structure.

/*------------------------------------------------------------------------*
 * Function Prototypes.
 *-----------------------------------------------------------------------*/
#include "heap.h"

void Swap(int* A, int* B);
void Heapify(int data[], int size, int level);

/*------------------------------------------------------------------------*
 * Function Implementations.
 *-----------------------------------------------------------------------*/
heap newHeap(int maxSize)
{
    assert(maxSize > 0);

    // Allocate the space for the structure.
    heap h = malloc(sizeof(struct heapArray));
    assert(h != NULL);

    // No elements in the array yet...
    h->numElements = 0;
    h->maxSize = maxSize; // For limit checking

    // Allocate the right amount of space for the array (in the structure)
    // and make a pointer to that memory space. Last memorry location
    // is for easy mangement of array limit checking.
    h->priorityQue = malloc((maxSize+1) * sizeof(int));
    assert(h->priorityQue != NULL);

    return h;
}

// Faster and more optimized algorithm than newHeap()
// NOTE: data[] is unchanged after call, it is copied over
heap buildHeap(int maxSize, int data[], int numData)
{
    assert(maxSize > 0);
    assert(data != NULL);
    assert(numData > 0);

    // Create the space for the heap structure
    heap h = newHeap(maxSize);

    // Copy over the data to heap's array
    int i;
    for(i = 1; i <= numData; i++){
        h->priorityQue[i] = data[i-1]; // Usually array indexing should start with 0
    }

    // Build heap algorithm:
    // Recursive bubble-down fix problem parts;
    // If children of i are roots of subheaps,
    // then i becomes the root of the subheap.  
    for(i = numData/2; i >= 1; i--){ 
        Heapify(h->priorityQue, numData, i);
    }

    // To indicate how much data is going into the heap
    h->numElements = numData;

    return h;
}

void freeHeap(heap h)
{
    // Make sure the array's space is zero... 
    while(!isEmpty(h)){
        deleteMax(h);
    }

    // Free the array space, then free the structure.
    free(h->priorityQue);
    h->priorityQue = NULL;
    free(h);
    h = NULL;
}

// Useful for an array doubling function
int isFull(heap h)
{
    assert(h != NULL);

    if(h->maxSize == h->numElements){
        return TRUE;
    }

    return FALSE;
}

// Useful for limit checking
int isEmpty(heap h)
{
    assert(h != NULL);

    if(0 == h->numElements){
        return TRUE;
    }

    return FALSE;
}

// NOTE: Does not delete the top value, need to call deleteMax()
int maxValue(heap h)
{
    assert(!isEmpty(h));

    return h->priorityQue[TOP];
}

// -- O(lgn) -- 
void deleteMax(heap h)
{
    assert(!isEmpty(h));

    // Remove the top priority item and replace with last item in list.
    h->priorityQue[TOP] = h->priorityQue[h->numElements--]; // One more element removed...

    // If one or zero elements than skip everything
    if(1 < h->numElements){
        h->priorityQue[h->numElements+1] = NONUMBER; // Clear away data

        // Bubble down.
        // Resort the heap structure according to heap ordering property:
        // parents have the same or greater priority than their children (left and right).
        int i = 1;
        while(!(h->priorityQue[i] >= h->priorityQue[2*i] && h->priorityQue[i] >= h->priorityQue[2*i + 1])){
            // Array limit checking:
            // Boundary condition only a left child
            if(h->numElements < 2*i + 1){ // NOTE: because left is added before right
                Swap(&h->priorityQue[i], &h->priorityQue[2*i]); // NOTE: because of array indexing
                break;
            }

            // Comparison
            if(h->priorityQue[2*i] >= h->priorityQue[2*i + 1]){
                Swap(&h->priorityQue[i], &h->priorityQue[2*i]);
                i = 2*i;
            }else{
                Swap(&h->priorityQue[i], &h->priorityQue[2*i + 1]);
                i = 2*i + 1;
            }

            // Array limit checking:
            // If at end of or over the array, then exit
            if(h->numElements <= 2*i){
                break;
            }
        }
    }
}

// -- O(lgn) -- 
void insert(heap h, int priority)
{
    assert(!isFull(h));

    // Add at the end
    h->priorityQue[++h->numElements] = priority; // One more element added...

    // Bubble up.
    // Resort the heap structure according to heap ordering property:
    // parents have the same or greater priority than their children (left and right).
    int i = h->numElements;
    while(!(h->priorityQue[(i+1)/2] >= h->priorityQue[i])){
        // Comparison
        Swap(&h->priorityQue[(i+1)/2], &h->priorityQue[i]);
        i = (i+1) / 2;
    }
}

// Useful to visually see if the structure is operating correctly
void printHeap(heap h)
{
    assert(!isEmpty(h));

    int i;
    for(i = 1; i <= h->numElements; i++){
        printf("%d ", h->priorityQue[i]);
    }

    printf("\n");
}

/*------------------------------------------------------------------------*
 * Helper Functions.
 *-----------------------------------------------------------------------*/
// Switches A with B in an array.
// NOTE: needs the addresses of the elements because C passes by value.
void Swap(int* A, int* B)
{
    int tmp = *A;
    *A = *B;
    *B = tmp;
}

// Modified verison of deleteMax():
// Made to recursively construct a heap, bottom-up.
void Heapify(int data[], int size, int level)
{
    // Bubble down.
    // Resort the heap structure according to heap ordering property:
    // parents have the same or greater priority than their children (left and right).
    int j = level; // Control variable for comparisons

    if(level == size/2){ // NOTE: because of array limit checking
        if(!(data[j] >= data[2*j])){
            Swap(&data[j], &data[2*j]);
        }
    }else{
        while(!(data[j] >= data[2*j] && data[j] >= data[2*j + 1])){
            // Comparison
            if(data[2*j] >= data[2*j + 1]){
                Swap(&data[j], &data[2*j]);
                j = 2*j;
            }else{
                Swap(&data[j], &data[2*j + 1]);
                j = 2*j + 1;
            }

            // Array limit checking:
            // If at end of or over the array, then exit
            if(size < 2*j){
                break;
            }
            // Array limit checking:
            // Boundary condition only a left child
            if(size < 2*j + 1){
                if(!(data[j] >= data[2*j])){ // Sort only if unsorted
                    Swap(&data[j], &data[2*j]);
                }
                break; // NOTE: because left is added before right
            }          // NOTE: because of array indexing
        }
    }
}
