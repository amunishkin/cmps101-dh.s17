/*
 * Author: Alexey A. Munishkin
 * 
 * File name: heapdr.c
 * Date: 4/30/2013
 * Class: CMPS 101
 * 
 * This diver program tests the functionality of the module 'heapSort', which is composed
 * of heap.h, the interface, and heap.c, the implementation.
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "heap.h"

#define SUCCESS 0

/**************************************************************************
 * Function Prototypes.
 *************************************************************************/
void printData(int array[], int size);

/**************************************************************************
 * Function Implemenations.
 *************************************************************************/
int main(void)
{
    printf("Welcome to the driver program for the module 'heap'.\n");
    printf("Enter the data (NOTE: only positive numbers):\n");

    // Receive the input data from the user through stdin
    int array[10] = {}; // Initialize to zeros
    int data = 0;

    int i;
    for(i = 0; i < 10; i++){
        int rc = scanf("%d", &data);

        if(rc < 0){
            printf("Error in input...\nPlease try again...\n");
            i--;
            continue;
        }

        array[i] = data;
    }

    // Construct the heap structure
    heap heapStr = newHeap(i); // 10 elements
    for(i = 0; i < 10; i++){
        insert(heapStr, array[i]);
    }

    // Print the various results:
    // (1) Print the original data.
    printf("Here is the data you inputed:\n");
    printData(array, i);

    // (2) Print the heap structure.
    printf("Here is the data sorted according to heap property:\n");
    printHeap(heapStr);

    // (3) Print the heap structure after every delete.
    for(i = 0; i < 9; i++){
        deleteMax(heapStr);
        printf("Here is the data after one delete:\n");
        printHeap(heapStr);
    }

    // Construct another heap structure using a faster algorithm
    heap heapStr2 = buildHeap(10, array, 10);

    // Print the second heap structure.
    printf("Here is the data sorted according to heap property, made by buildHeap():\n");
    printHeap(heapStr2);

    // Print the heap structure after every delete.
    for(i = 0; i < 9; i++){
        deleteMax(heapStr2);
        printf("Here is the data after one delete:\n");
        printHeap(heapStr2);
    }

    // Free up all memory space
    freeHeap(heapStr);
    freeHeap(heapStr2);

    return SUCCESS;
}

/*----------------------------------------------------------------------*
 * Helper Functions.
 *---------------------------------------------------------------------*/
void printData(int array[], int size)
{
    int i;
    for(i = 0; i < size; i++){
        printf("%d ", array[i]);
    }

    printf("\n");
}
