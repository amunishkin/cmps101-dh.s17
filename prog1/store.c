/*
 * Author: Alexey A. Munishkin
 * 
 * File name: store.c
 * Date: 4/16/2013
 * Class: CMPS 101
 * 
 * This program ulitizes the ADT module called List to read in one or more text
 * files, input the data into the ADT, and then print out the result in a nice,
 * formatted and sorted order.
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "List.h"

#define SUCCESS 0
#define FAILURE 1

/**************************************************************************
 * Global Variables.
 *************************************************************************/
int exit_status = SUCCESS;

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
void RunInput(FILE* in, FILE* out);
void PutDataInList(int customerData, long bookData, ArrayRef customerArray);
ArrayRef CreateArray(int size);
void PrintData(FILE* out, ArrayRef arrayList);
void Sort(ArrayRef arrayList);
void FreeArray(ArrayRef arrayList, int size);
void insertIntoList(ListRef list, long data);

/**************************************************************************
 * Function Implemenations.
 *************************************************************************/
int main(int argc, char** argv)
{
    if(argc == 1){
        printf("Usage: %s files...\n", argv[0]);
        exit_status = FAILURE;
    }else{
        int i;
        for(i = 1; i < argc; i++){
            FILE* inputFile = fopen(argv[i], "r");

            if(inputFile != NULL){
                printf("%s Data Summary:\n", argv[i]);
                RunInput(inputFile, stdout);
            }else{
                fflush(NULL);
                fprintf(stderr, "Error in opening file %s\n", argv[i]);
                fflush(NULL);
                exit_status = FAILURE;
            }

            fclose(inputFile);
        }
    }

    return exit_status;
}

/*----------------------------------------------------------------------*
 * Input Data Analysis and Extracation.
 *---------------------------------------------------------------------*/
void RunInput(FILE* in, FILE* out)
{    
    int customerSize;
    int rc = fscanf(in, "%d", &customerSize);

    if(rc < 0){
        fprintf(stderr, "Error in customer input\n");
        exit_status = FAILURE;
        return;
    }

    ArrayRef customerArray = CreateArray(customerSize);

    int bookSize;
    rc = fscanf(in, "%d", &bookSize);

    if(rc < 0){
        fprintf(stderr, "Error in book size input\n");
        exit_status = FAILURE;
        return;
    }

    for(;;){        
        int customerData;
        rc = fscanf(in, "%d", &customerData);

        if(rc < 0){
            break;
        }

        long bookData;
        rc = fscanf(in, "%ld", &bookData);

        if(rc < 0){
            fprintf(stderr, "Invalid input, customer# book#\n");
            exit_status = FAILURE;
            break;
        }

        PutDataInList(customerData, bookData, customerArray);
    }

    Sort(customerArray);
    PrintData(out, customerArray);

    FreeArray(customerArray, customerArray->length);
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
    fprintf(out, "Customer#     books bought\n");

    int i;
    for(i = 0; i < arrayList->length; i++){
        if(arrayList->array[i] != NULL){
            fprintf(out, "%d\t", i + 1); // index 0 is Customer 1.
            printList(out, arrayList->array[i]);
        }else{
            fprintf(out, "%d\n", i + 1); // Empty to indicate
            // not used.
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
        if(arrayList->array[i] == NULL){
            // No data to free up
        }else{
            freeList(arrayList->array[i]);
            arrayList->array[i] = NULL;
        }
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
