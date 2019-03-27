/*
 * Author: Alexey A. Munishkin
 * 
 * File name: sortComp.c
 * Date: 5/1/2013
 * Class: CMPS 101
 * 
 * This diver program tests the run time of the modules 'heapSort' and 'insertionSort, 
 * which is composed of heapSort.h, insertionSort.h, the interfaces, and heap.c, insertionSort.c,
 * the implementations.
 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h> // For measureing run time in seconds
// NOTE: based on "clock ticks"
// NOTE: could vary by computer because its based on clock speed

#include "heapSort.h" // Sorting algorithms
#include "insertionSort.h"

#define FAILURE 1 // System error checking
#define SUCCESS 0

#define INSERTION_SORT 0
#define HEAP_SORT      1 // Symbolic references to algorithms

/**************************************************************************
 * Function Prototypes.
 *************************************************************************/
int* ReadData(FILE* file, long sizeOfData);
void RunTimeMeasure(int algorithm, int* data, long size);

/**************************************************************************
 * Function Implemenations.
 *************************************************************************/
int main(int argc, char** argv)
{
    if(2 != argc){
        printf("Usage: %s filename\n", argv[0]);
    }else{
        FILE* file = fopen(argv[1], "r");

        // Error in opening file
        if(NULL == file){
            fflush(NULL);
            printf("Error in opening file: %s\n", argv[1]);
            fflush(NULL);
            return FAILURE;
        }

        // Read first line:
        // Should contain size for array size
        long size;
        int rc = fscanf(file, "%ld", &size);
        if(rc < 0){
            printf("Error in reading size\n");
            return FAILURE;
        }

        // Read the input
        int* data = ReadData(file, size);
        if(NULL == data){
            return FAILURE;
        }

        // Copy data over twice: for each sorting algorithm
        int* copy1 = calloc(size, sizeof(int));
        int* copy2 = calloc(size, sizeof(int));
        int i;
        for(i = 0; i < size; i++){
            copy1[i] = data[i];
            copy2[i] = data[i];
        }

        // Measure and output the run time of insertionSort()
        RunTimeMeasure(INSERTION_SORT, copy1, size);

        // Measure and output the run time of insertionSort()
        RunTimeMeasure(HEAP_SORT, copy2, size);

        // Free-up all memory in use
        free(data);
        free(copy1);
        free(copy2);

        fclose(file);
    }

    return SUCCESS;
}


/*----------------------------------------------------------------------*
 * Helper Functions.
 *---------------------------------------------------------------------*/
int* ReadData(FILE* file, long sizeOfData)
{
    // Create the array with size indicated
    int* data = calloc(sizeOfData, sizeof(int));

    int i;
    for(i = 0; i < sizeOfData; i++){
        int rc = fscanf(file, "%d", &data[i]);
        if(rc < 0){
            printf("Error in reading data\n");
            return NULL; 
        }
    }

    return data;
}

void RunTimeMeasure(int algorithm, int* data, long size)
{
    // Time measurement variables.
    clock_t startTime, duration;

    if(INSERTION_SORT == algorithm){
        // Measure run time of the insertion sort algorithm
        startTime = clock();
        insertionSort(data, size);
        duration = clock() - startTime;

        // Print the run time
        printf("InsertionSort(): %ld size : %f seconds.\n", 
                size, ((float) duration) / CLOCKS_PER_SEC);
    }
    if(HEAP_SORT == algorithm){
        // Measure run time of the insertion sort algorithm
        startTime = clock();
        heapSort(data, size);
        duration = clock() - startTime;

        // Print the run time
        printf("HeapSort(): %ld size : %f seconds.\n", 
                size, ((float) duration) / CLOCKS_PER_SEC);
    }
}
