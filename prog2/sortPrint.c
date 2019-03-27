/*
 * Author: Alexey A. Munishkin
 * 
 * File name: sortPrint.c
 * Date: 4/30/2013
 * Class: CMPS 101
 * 
 * This diver program tests the functionality of the modules 'heapSort' and 'insertionSort, 
 * which is composed of heapSort.h, insertionSort.h, the interfaces, and heap.c, insertionSort.c,
 * the implementations.
 */

#include <stdlib.h>
#include <stdio.h>

#include "heapSort.h" // Sorting algorithms
#include "insertionSort.h"

#define FAILURE 1 // System error checking
#define SUCCESS 0

#define TRUE  1 // Basic boolean types
#define FALSE 0

/**************************************************************************
 * Function Prototypes.
 *************************************************************************/
int* ReadData(FILE* file, long sizeOfData);
int CheckSort(int* data, long size);
void printData(int* data, long size);

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

        printf("Here is the orginal data:\n");
        printData(data, size);

        // Copy data over twice: for each sorting algorithm
        int* copy1 = calloc(size, sizeof(int));
        int* copy2 = calloc(size, sizeof(int));
        int i;
        for(i = 0; i < size; i++){
            copy1[i] = data[i];
            copy2[i] = data[i];
        }

        // Sort the data with each sorting algorithm
        // (1) InsertionSort
        insertionSort(copy1, size);

        // Check its sorted
        rc = CheckSort(copy1, size);
        if(FALSE == rc){
            printf("InsertionSort() FAILED\n");
        }

        printf("Here is the sorted output by insertionSort():\n");
        printData(copy1, size);

        // (2) HeapSort
        heapSort(copy2, size);

        // Check its sorted
        rc = CheckSort(copy2, size);
        if(FALSE == rc){
            printf("HeapSort() FAILED\n");
        }

        printf("Here is the sorted output by heapSort():\n");
        printData(copy2, size);

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

int CheckSort(int* data, long size)
{    
    // Check each data[i] with data[i+1]
    int i;
    for(i = 0; i < (size - 1); i++){
        if(data[i] > data[i+1]){
            return FALSE;
        }
    }

    return TRUE;
}

void printData(int* data, long size)
{
    int i;
    for(i = 0; i < size; i++){
        printf("%d ", data[i]);
    }

    printf("\n");
}
