/*
 * Author: Alexey A. Munishkin
 * 
 * File name: Hash.c
 * Date: 5/16/2013
 * Class: CMPS 101
 * 
 * This ADT implemenation creates and manages a hash table.
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE  1

/**************************************************************************
 * Implemenation:
 *    See Hash.h for details on the undocumented functions below.
 *************************************************************************/
#include "Hash.h"

/*------------------------------------------------------------------------*
 * Structures.
 *-----------------------------------------------------------------------*/
struct HashType{
    ListRef* table; // Hash Table with collision resoltion by seperate chaining
    int length; // length of the hash table (aka m)
    int numOfSlots;
};

/*------------------------------------------------------------------------*
 * Function Prototypes.
 *-----------------------------------------------------------------------*/
// Hash.h put above because need List.h before use of keyword ListRef

HashRef DoubleHash(HashRef H);
/*------------------------------------------------------------------------*
 * Function Implementations.
 *-----------------------------------------------------------------------*/
HashRef NewHash(int size)
{
    HashRef H = malloc(sizeof(HashTable));
    assert(H != NULL);

    H->table = malloc(size * sizeof(ListRef));
    assert(H->table != NULL);

    // Clear all data in table before use
    int i;
    for(i = 0; i < size; i++){
        H->table[i] = NULL;
    }

    H->length = size;
    H->numOfSlots = 0;

    return H;
}

void FreeHash(HashRef H)
{
    assert(H != NULL);

    // Free up the memory used by the chain in each slot
    int i;
    for(i = 0; i < H->length; i++){
        if(NULL != H->table[i]){
            freeList(H->table[i]);
        }
    }

    // Free up the memory used by the hash table itself
    free(H->table);
    H->table = NULL;
    free(H);
    H = NULL;
}

// Useful for collision resoltion by rehashing (aka open adressing) and table doubling
int IsFull(HashRef H, int alpha)
{
    assert(H != NULL);
    assert(0 < alpha);
    assert(H->length >= alpha);

    if(H->numOfSlots > alpha){
        return TRUE;
    }

    return FALSE;
}

void* LookUp(HashRef H, void* key, void* data, int (*HashFunction) (HashRef, void*), int (*Compare) (void*, void*))
{
    assert(H != NULL);
    assert(0 < key);
    assert(HashFunction != NULL);
    assert(Compare != NULL);

    // Create the hash indicator index to start search
    int index = (*HashFunction) (H, key);
    assert(0 < index);
    assert(H->length >= index); // Make sure it maps to within range of hash table

    // Make sure there is a chain in the slot
    if(H->table[index] != NULL){
        // Search through the linked list. Expected runtime O(1)
        moveFirst(H->table[index]);
        do{
            void* currKey = getCurrent(H->table[index]);

            int cmp = (*Compare) (data, currKey);
            if(0 == cmp){
                return currKey; // Successful search
            }
            moveNext(H->table[index]);
        }while(!offEnd(H->table[index]));
    }

    // Unsuccessful search
    return NULL;
}

void Insert(HashRef H, void* key, void* data, int (*HashFunction) (HashRef, void*), int (*Compare) (void*, void*))
{
    assert(H != NULL);
    assert(0 < key);
    assert(HashFunction != NULL);
    assert(Compare != NULL);

    // Check if hash table is full
    if(H->numOfSlots == H->length){
        H = DoubleHash(H);        
    }

    // Create the hash indicator index to start search
    int index = (*HashFunction) (H, key);
    assert(0 < index);
    assert(H->length >= index); // Make sure it maps to within range of hash table

    // Empty list?
    if(NULL == H->table[index]){
        H->table[index] = newList();
        H->numOfSlots++; // Increase slot usage count
    }

    // Insert the key into the list
    insertBeforeFirst(H->table[index], data);
}

void Delete(HashRef H, void* key, void* data, int (*HashFunction) (HashRef, void*), int (*Compare) (void*, void*))
{
    // Find the key if it exists
    // Create the hash indicator index to start search
    int index = (*HashFunction) (H, key);
    assert(0 < index);
    assert(H->length >= index); // Make sure it maps to within range of hash table

    // Search through the linked list. Expected runtime O(1)
    moveFirst(H->table[index]);
    do{
        void* currKey = getCurrent(H->table[index]);

        int cmp = (*Compare) (data, currKey);
        if(0 == cmp){ 
            // Delete that key from the list
            deleteCurrent(H->table[index]);; // Successful search
        }
        moveNext(H->table[index]);
    }while(!offEnd(H->table[index]));    
}

void PrintHash(FILE* out, HashRef H, int summaryFlag, void (*Print) (FILE*, void*))
{
    // Print Summary if requised
    if(TRUE == summaryFlag){
        fprintf(out, "Summary of Hash Table:\n");
        fprintf(out, "Size of table is %d\n", H->length);
        fprintf(out, "Number of used slots is %d\n", H->numOfSlots);
    }
    // Print each element(s) in each slot of the hash table
    int i;
    for(i = 0; i < H->length; i++){
        if(NULL != H->table[i]){
            fprintf(out, "slot %d contains\n", i);

            // Loop through the linked list
            moveFirst(H->table[i]);
            for(; !offEnd(H->table[i]); moveNext(H->table[i])){
                (*Print) (out, getCurrent(H->table[i]));
            }

            fprintf(out, "\n");
        }
    }
}

ListRef getSlot(HashRef H, int slotIndex)
{
    assert(NULL != H);
    assert(H->length >= slotIndex);
    assert(slotIndex >= 0);

    return H->table[slotIndex];
}

void putSlot(HashRef H, int slotIndex, ListRef slot)
{
    assert(NULL != H);
    assert(H->length >= slotIndex);
    assert(slotIndex >= 0);
    
    H->table[slotIndex] = slot;
}

int getHashLength(HashRef H)
{
    assert(NULL != H);

    return H->length;
}

/*------------------------------------------------------------------------*
 * Provided Hash Functions.
 *-----------------------------------------------------------------------*/
int DivisionFunctionLong(HashRef H, void* key)
{
    assert(NULL != key);
    assert(NULL != H);

    long* keyLong = (long*) key;

    // k mod m
    // NOTE: k >= 0 and m > 0 for % to operate the same as mod
    assert(*keyLong >= 0);
    assert(H->length > 0);

    return (int) (*keyLong % (H->length));
}

// defination of BookRef for this function
typedef struct{
    long data;
    int count;
}* BookRef;

int DivisonFunctionBook(HashRef H, void* key)
{
    assert(NULL != key);
    assert(NULL != H);

    BookRef keyBook = (BookRef) key;

    // k mod m
    // NOTE: k >= 0 and m > 0 for % to operate the same as mod
    assert(keyBook->data >= 0);
    assert(H->length > 0);

    return (int) (keyBook->data % (H->length));
}

/*------------------------------------------------------------------------*
 * Helper Functions.
 *-----------------------------------------------------------------------*/
HashRef DoubleHash(HashRef H)
{
    return H;
}
