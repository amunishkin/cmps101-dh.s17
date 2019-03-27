/*
 * Author: Alexey A. Munishkin
 * 
 * File name: heapSort.c
 * Date: 4/30/2013
 * Class: CMPS 101
 * 
 * This ADT implemenation of the module 'heapSort' sorts an array using the 
 * heapSort algorithm, which has expected O(nlgn) run time.
 */

#include <stdlib.h>
#include <assert.h>

// Uses the heap structure to obtain O(nlgn) runtime speed
#include "heap.h"

void heapSort(int keys[], int numKeys)
{
    // Construct the heap structure using the quicker method
    heap heapStr = buildHeap(numKeys, keys, numKeys);

    // Retain the old data and create a new place for
    // the sorted data.
    int* sortedKeys = calloc(numKeys, sizeof(int));
    assert(sortedKeys != NULL);

    // Sort in increasing order.
    int i;
    for(i = (numKeys - 1); i >= 0; i--){
        sortedKeys[i] = maxValue(heapStr);
        deleteMax(heapStr);
    }
    
    // Copy over the sorted data
    for(i = 0; i < numKeys; i++){
        keys[i] = sortedKeys[i];
    }
    
    freeHeap(heapStr);
    free(sortedKeys);
    sortedKeys = NULL;
}