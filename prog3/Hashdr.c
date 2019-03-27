/*
 * Author: Alexey A. Munishkin
 * 
 * File name: Hashdr.c
 * Date: 5/16/2013
 * Class: CMPS 101
 * 
 * This diver program tests the functionality of the module Hash, which is composed
 * of Hash.h, the interface, and Hash.c, the implementation.
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Hash.h"

#define SUCCESS 0

#define TRUE  1 // Elementary Boolean values
#define FALSE 0

/**************************************************************************
 * Structures.
 *************************************************************************/
typedef struct{
    long bookId;
    int coPurchaseCount;
} bookInfo;

/**************************************************************************
 * Function Prototypes.
 *************************************************************************/
void RunInput(void);
void InsertData(HashRef H, long bookData);
void FreeData(HashRef H);
int LongCompare(void* A, void* B);
void PrintLong(FILE* out, void* data);

/**************************************************************************
 * Function Implemenations.
 *************************************************************************/
int main(void)
{
    printf("Welcome to the driver program for the module 'Hash'.\n");

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
//  size of hash table (for collision resolution by chaining)
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

    int bookSize;
    rc = scanf("%d\n", &bookSize);

    if(rc < 0){
        printf("Error in input...\n");
        return;
    }

    int hashSize;
    rc = scanf("%d\n", &hashSize);
    if(rc < 0){
        printf("Error in input...\n");
        return;
    }

    HashRef hashTable = NewHash(hashSize);

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

        InsertData(hashTable, bookData);
    }
    printf("Ending User Input\n");

    printf("Here is the data in the hash table:\n");
    PrintHash(stdout, hashTable, TRUE, PrintLong);

    // Free up all the unused data and structures
    FreeData(hashTable);

    printf("Exiting user input mode...\n");
}

/*----------------------------------------------------------------------*
 * Helper Functions.
 *---------------------------------------------------------------------*/
/*
 * 
 */
void InsertData(HashRef H, long bookData)
{
    long* bookId = malloc(sizeof(long));
    assert(NULL != bookId);

    *bookId = bookData;

    Insert(H, bookId, bookId, DivisionFunctionLong, LongCompare);
}

/*
 * 
 */
void FreeData(HashRef H)
{
    int i;
    for(i = 0; i < getHashLength(H); i++){
        if(NULL != getSlot(H, i)){
            // Free all the data in a linked list
            moveFirst(getSlot(H, i));        
            int j;
            for(j = 0; j < getLength(getSlot(H, i)); j++){
                free(getCurrent(getSlot(H, i)));
                moveNext(getSlot(H, i));
            }
        }
    }
    FreeHash(H);
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
