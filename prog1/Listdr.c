/*
 * Author: Alexey A. Munishkin
 * 
 * File name: Listdr.c
 * Date: 4/14/2013
 * Class: CMPS 101
 * 
 * This diver program tests the functionality of the module List, which is composed
 * of List.h, the interface, and List.c, the implementation.
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "List.h"

#define SUCCESS 0

/**************************************************************************
 * Structures.
 *************************************************************************/
typedef struct ListArray{
    int length;
    ListRef* array; // ListType**
} ArrayType;

typedef ArrayType* ArrayRef;

/**************************************************************************
 * Function Prototypes.
 *************************************************************************/
void RunInput(void);
void PutDataInList(int customerData, long bookData, ArrayRef customerArray);
ArrayRef CreateArray(int size);
void PrintData(FILE* out, ArrayRef arrayList);
void Sort(ArrayRef arrayList);
void FreeArray(ArrayRef arrayList, int size);
void insertIntoList(ListRef list, long data);

/**************************************************************************
 * Function Implemenations.
 *************************************************************************/
int main(void)
{
    printf("Welcome to the driver program for the module 'List'.\n");

    RunInput();

    printf("Ending...\n");
    return SUCCESS;
}

/*----------------------------------------------------------------------*
 * User Input Test
 *---------------------------------------------------------------------*/
void RunInput(void)
{
    printf("Enter data:\n");

    int customerSize;
    int rc = scanf("%d\n", &customerSize);

    if(rc < 0){
        printf("Error in input...\n");
        return;
    }

    ArrayRef customerArray = CreateArray(customerSize);

    int bookSize;
    rc = scanf("%d\n", &bookSize);

    if(rc < 0){
        printf("Error in input...\n");
        return;
    }

    for(;;){        
        int customerData;
        rc = scanf("%d", &customerData);

        if(rc < 0){
            break;
        }

        long bookData;
        rc = scanf("%ld", &bookData);

        if(rc < 0){
            printf("Invalid input, try again...\n");
            continue;
        }

        PutDataInList(customerData, bookData, customerArray);
    }
    printf("Ending User Input\n");
    printf("Here is the data unsorted:\n");
    PrintData(stdout, customerArray);

    Sort(customerArray);
    printf("Here is the data sorted:\n");
    PrintData(stdout, customerArray);

    FreeArray(customerArray, customerArray->length);

    printf("Exiting user input mode...\n");
}

/*----------------------------------------------------------------------*
 * Helper Functions.
 *---------------------------------------------------------------------*/
void PutDataInList(int id, long book, ArrayRef arrayList)
{
    if(arrayList->array[id - 1] == NULL){ // Customer 1 should be in index 0.
        arrayList->array[id - 1] = newList();
    }

    insertIntoList(arrayList->array[id - 1], book);
}

ArrayRef CreateArray(int size)
{
    ArrayRef arrayList = malloc(sizeof(ArrayType));
    assert(arrayList != NULL);

    arrayList->array = malloc(size * sizeof(ListRef));
    assert(arrayList->array != NULL);

    // Clear all data.
    int i;
    for(i = 0; i < size; i++){
        arrayList->array[i] = NULL;
    }

    arrayList->length = size;

    return arrayList;
}

void PrintData(FILE* out, ArrayRef arrayList)
{
    fprintf(out, "Customer#\t books bought\n");

    int i;
    for(i = 0; i < arrayList->length; i++){
        if(arrayList->array[i] != NULL){
            fprintf(out, "%d\t", i + 1); // index 0 is Customer 1.
            printList(out, arrayList->array[i]);
        }else{
            fprintf(out, "%d is unused\n", i + 1);
        }
    }
}

void Sort(ArrayRef arrayList)
{
    int i;
    for(i = 0; i < arrayList->length; i++){
        if(arrayList->array[i] == NULL){
            // No data to sort
        }else{
            arrayList->array[i] = insertionSort(arrayList->array[i]);
        }
    }
}

void FreeArray(ArrayRef arrayList, int size)
{
    int i;
    for(i = 0; i < size; i++){
        freeList(arrayList->array[i]);
        arrayList->array[i] = NULL;
    }

    free(arrayList->array);
    arrayList->array = NULL;
    free(arrayList);
    arrayList = NULL;
}

void insertIntoList(ListRef list, long data)
{
    if(isEmpty(list)){
        // Nothing
    }else{
        moveLast(list);
    }
    insertAfterLast(list, data);
}
