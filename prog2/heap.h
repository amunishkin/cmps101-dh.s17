/*
 * Author: Alexey A. Munishkin
 * 
 * File name: heap.h
 * Date: 4/28/2013
 * Class: CMPS 101
 * 
 * This ADT interface allows the user to use the module 'heap'. This is priority queque based
 * array structure based on the binary tree. The implemenation code uses the array implementation
 * of a binary tree to create the heap structure.
 */

#ifndef __HEAP_H__
#define __HEAP_H__

/*------------------------------------------------------------------------*
 * Structures.
 *-----------------------------------------------------------------------*/
typedef struct heapArray* heap;

/**************************************************************************
 * Constructors-Destructors 
 *************************************************************************/
// Constructors
// Creates an empty heapArray and passes a handle to the caller.
//
// Pre:  maxSize > 0
heap newHeap(int maxSize);

// Creates and initializes a heapArray with the given data and passes a handle to the caller.
//
// Pre:  maxSize > 0 and numData > 0 and data != NULL
heap buildHeap(int maxSize, int data[], int numData);

// Destructor
//
// Pre:  h != NULL
void freeHeap(heap h);

/**************************************************************************
 * Access functions 
 *************************************************************************/
// Checks if the heapArray memory allocation is full.
//
// Pre:  h != NULL
// Post: TRUE  (1) if memory allocation space filled
//       FALSE (0) otherwise
int isFull(heap h);

// Checks if heapArray has no elements
//
// Pre:  h != NULL
// Post: TRUE  (1) if array is empty
//       FALSE (0) otherwise
int isEmpty(heap h);

// Returns the top value of the heapArray
//
// Pre:  !isEmpty
int maxValue(heap h);

/**************************************************************************
 * Manipulation procedures 
 *************************************************************************/
// Removes the top value of the heapArray and reorders the heap
// according to max priority heap ordering property.
//
// Pre:  !isEmpty
void deleteMax(heap h);

// Inserts a priority item into the heapArray.
//
// Pre:  !isFull
void insert(heap h, int priority);

/*****************************************************************************
 * Other operations 
 ****************************************************************************/
// Prints the data as is in the heap
//
// Pre:  !isEmpty
void printHeap(heap h);

#endif
