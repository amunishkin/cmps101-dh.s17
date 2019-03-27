/*
 * Author: Alexey A. Munishkin
 * 
 * File name: Listdr.c
 * Date: 4/14/2013
 * Class: CMPS 101
 * 
 * This diver program tests the functionality of the module List, which is composed
 * of List.h, the interface, and List.c, the implementation.
 * 
 * Modified version: 5/11/2013
 * Modified to handle any data type (using void*) not just longs. However, here is an
 * example of how to use it for longs.
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
void insertIntoList(ListRef list, void* data);
int LongCompare(void* A, void* B);
void PrintLong(FILE* out, void* data);

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
// Input given as:
//  # of Customers
//  # of transactions
// each other line as follows:
//  customerID# bookID#
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

    // Free all unused data and structures
    FreeArray(customerArray, customerArray->length);

    printf("Exiting user input mode...\n");
}

/*----------------------------------------------------------------------*
 * Helper Functions.
 *---------------------------------------------------------------------*/
/*
 * PutDataInList(int, long, ArrayRef)
 * 
 * Puts the customer-book information into the customer array.
 * This function allocates memory storage for the book, as the List
 * module (modified version: 5/11/2013) can hold any data type (aka void*)
 * and what is stored in a node is a generic pointer. That pointer can point
 * to variable sizes and so the book is copy onto the heap, which is pointed
 * by the generic pointer (void*).
 */
void PutDataInList(int id, long book, ArrayRef arrayList)
{
    if(arrayList->array[id - 1] == NULL){ // Customer 1 should be in index 0.
        arrayList->array[id - 1] = newList();
    }

    // Make a copy and store in the heap for perment storage
    // until clean-up at the end.
    long* book_copy = malloc(sizeof(long));
    assert(book_copy != NULL);
    *book_copy = book;

    insertIntoList(arrayList->array[id - 1], book_copy);
}

/*
 * CreateArray(int)
 * 
 * Creates the Customer array with each slot being the customer's id
 * minus 1 (to use up all the slots including 0), and each slot has 
 * the doubly linked list of all the books the customer bought.
 */
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

/*
 * PrintData(FILE*, ArrayRef)
 * 
 * Prints the complete summary of every customer's transactions
 * made in the format:
 *  customerID# book(0)ID# book(1)ID#... book(k)ID#
 * where 
 *       k is the total number of books the customer bought.
 */
void PrintData(FILE* out, ArrayRef arrayList)
{
    fprintf(out, "Customer#\t books bought\n");

    int i;
    for(i = 0; i < arrayList->length; i++){
        if(arrayList->array[i] != NULL){
            fprintf(out, "%d\t", i + 1); // index 0 is Customer 1.
            printList(out, arrayList->array[i], PrintLong);
        }else{
            fprintf(out, "%d is unused\n", i + 1);
        }
    }
}

/*
 * Sort(ArrayRef)
 * 
 * Uses the insertionSort() algorithm (expected runtime O(n^2))
 * to sort the doubly linked list in increasing order.
 * ex:
 *  input : 1 7 8 4
 *  output: 1 4 7 8
 */
void Sort(ArrayRef arrayList)
{
    int i;
    for(i = 0; i < arrayList->length; i++){
        if(arrayList->array[i] == NULL){
            // No data to sort
        }else{
            arrayList->array[i] = insertionSort(arrayList->array[i], LongCompare);
        }
    }
}

/*
 * FreeArray(ArrayRef, int)
 * 
 * This function acts as a primitive garbage collector: it only
 * frees up all the old memory not in use anymore, but it doesn't
 * defragment the memory space for efficient use for memory allocation
 * with the heap later.
 */
void FreeArray(ArrayRef arrayList, int size)
{
    // Clean-up all memory not in use anymore.
    int i;
    for(i = 0; i < size; i++){
        // Free all the data in a list
        moveFirst(arrayList->array[i]);        
        int j;
        for(j = 0; j < getLength(arrayList->array[i]); j++){
            free(getCurrent(arrayList->array[i]));
            moveNext(arrayList->array[i]);
        }
        freeList(arrayList->array[i]);
        arrayList->array[i] = NULL;
    }

    free(arrayList->array);
    arrayList->array = NULL;
    free(arrayList);
    arrayList = NULL;
}

/*
 * insertIntoList(ListRef, void*)
 * 
 * Made to insert longs into a doubly linked list (List Module).
 */
void insertIntoList(ListRef list, void* data)
{
    if(isEmpty(list)){
        // Nothing
    }else{
        moveLast(list);
    }

    long* input_data = (long*) data;
    insertAfterLast(list, input_data);
}

/*
 * LongCompare()
 * 
 * For use with generic data type comparision. This function
 * compares two longs: 
 *  if A <  B returns -1
 *  if A >  B returns  1
 *  if A == B returns  0
 */
int LongCompare(void* A, void* B)
{
    long* A_cmp = (long*) A;
    long* B_cmp = (long*) B;    

    if(*A_cmp < *B_cmp){
        return -1;
    }
    else if(*A_cmp > *B_cmp){
        return 1;
    }
    else{
        return 0;
    }
}

/*
 * PrintLong()
 * 
 * For use with generic data type printing. This function
 * prints out a long on the same line with a space after the
 * long.
 * ex:
 *  "12894532 "
 */
void PrintLong(FILE* out, void* data)
{
    fprintf(out, "%ld ", *((long*) data));
}
