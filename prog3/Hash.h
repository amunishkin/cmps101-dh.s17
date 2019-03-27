/*
 * Author: Alexey A. Munishkin
 * 
 * File name: Hash.h
 * Date: 5/16/2013
 * Class: CMPS 101
 * 
 * This ADT interface allows the user to manulate and use a hash table, which
 * is made to hold any data type (by using the generic void*). The user just has
 * to specify what data type he/she is using by casting.
 * 
 * NOTE: operations on this hash table should take expected runtime of O(1).
 * NOTE: collisions are resolved by seperate chaining (aka this hash table uses 
 *       a lot of memory if the input is big enough because it relies on a linked
 *       list ADT).
 */

#ifndef __HASH_H__
#define __HASH_H__

#include "List.h" // For resolting collisions by seperate chaining

// NOTE: TRUE  = 1
//       FALSE = 0

/*------------------------------------------------------------------------*
 * Structures.
 *-----------------------------------------------------------------------*/
typedef struct HashType HashTable;
typedef HashTable* HashRef;

/**************************************************************************
 * Constructors-Destructors 
 *************************************************************************/
// Constructor
HashRef NewHash(int size);

// Destructor
//
// Pre:  H != NULL
void FreeHash(HashRef H);

/**************************************************************************
 * Access functions 
 *************************************************************************/
// Returns true if the hash table is full based on the load factor given
//
// Pre:  H != NULL and size of hash table >= alpha > 0
int IsFull(HashRef H, int alpha);

// Returns the linked list associated with the look-up or NULL if not found
//
// Pre:  H != NULL and key != NULL and HashFunction != NULL
//       and maps to within range of hash table. (0 < h(k) < size of hash table)
// Post: on Success the data (have to cast to type wanted)
//       on Failure a NULL pointer
void* LookUp(HashRef H, void* key, void* data, int (*HashFunction) (HashRef, void*), int (*Compare) (void*, void*));

/**************************************************************************
 * Manipulation procedures 
 *************************************************************************/
// Inserts the key-data pair into the hash table according to the
// hash function given.
//
// Pre:  H != NULL and key != NULL and HashFunction != NULL
//       and maps to within range of hash table. (0 < h(k) < size of hash table)
void Insert(HashRef H, void* key, void* data, int (*HashFunction) (HashRef, void*), int (*Compare) (void*, void*));

// Deletes the data associated with the key and hash function
//
// Pre:  H != NULL and LookUp at that place != NULL and key != NULL and HashFunction != NULL
//       and maps to within range of hash table. (0 < h(k) < size of hash table)
void Delete(HashRef H, void* key, void* data, int (*HashFunction) (HashRef, void*), int (*Compare) (void*, void*));

/*****************************************************************************
 * Other operations 
 ****************************************************************************/
// Prints the hash table's entries one by one to the specified output
// and prints out a summary of the hash table if indicated by TRUE (1).
//
// Pre:  out != NULL and H != NULL
void PrintHash(FILE* out, HashRef H, int summaryFlag, void (*Print) (FILE*, void*));

// Returns the head of the linked list for the specified slot number by slotIndex.
//
// Pre:  H != NULL and length of hashTable > slotIndex >= 0
ListRef getSlot(HashRef H, int slotIndex);

// Puts the head of a linked list in the hash table at the slot specified by slotIndex
//
// Pre:  H != NULL and length of hashTable > slotIndex >= 0
void putSlot(HashRef H, int slotIndex, ListRef slot);

// Returns the length or size of the hash table
//
// Pre:  H != NULL
int getHashLength(HashRef H);

/*------------------------------------------------------------------------*
 * Some Hash Functions for use.
 *-----------------------------------------------------------------------*/
// This hash function is:
//  h(k) = k mod m
// where 
//      h(k) is the hash value
//      k is the key (assumes longs)
//      m is the size of the hash table
//
// Pre:  H != NULL and key != NULL
int DivisionFunctionLong(HashRef H, void* key);

// Same as above but key assumes BookRef
int DivisonFunctionBook(HashRef H, void* key);

#endif
