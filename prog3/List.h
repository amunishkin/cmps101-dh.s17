/*
 * Author: Alexey A. Munishkin
 * 
 * File name: List.h
 * Date: 4/14/2013
 * Class: CMPS 101
 * 
 * Acknowledgments: Prof. Helmhold for sample code for (.h) file.
 * 
 * This ADT interface allows the user to manuplate a linked list on an array.
 * The linked list is a double linked list, allowing for more flexability in
 * transversing the linked list. Each node of the linked list holds one valuable
 * piece of data that the user manuplate.
 * 
 * Modified version: 5/11/2013
 * Modified to handle any data type (using void*) not just longs.
 */

#ifndef __LIST_H__
#define __LIST_H__

// NOTE: TRUE  = 1
//       FALSE = 0

/*------------------------------------------------------------------------*
 * Structures.
 *-----------------------------------------------------------------------*/
typedef struct ListHdr ListType;
typedef ListType* ListRef;

/**************************************************************************
 * Constructors-Destructors 
 *************************************************************************/
// Constructor
ListRef newList(void);

// Destructor
//
// Pre:  L != NULL
void freeList(ListRef L);

/**************************************************************************
 * Access functions 
 *************************************************************************/
// Returns true is list is empty else returns false.
//
// Pre:  L != NULL
int isEmpty(ListRef L); 

// Returns true is current == NULL.
int offEnd(ListRef L); 

// Returns true if current == first and !offEnd().
int atFirst(ListRef L); 

// Returns true if current == last and !offEnd().
int atLast(ListRef L); 

// Return the first element.
//
// Pre:  !isEmpty().
void* getFirst(ListRef L); 

// Return the last element.
//
// Pre:  !isEmpty().
void* getLast(ListRef L); 

// Return the current element.
//
// Pre:  !offEnd().
void* getCurrent(ListRef L); 

// Return the length of the list.
//
// Pre:  L != NULL
int getLength(ListRef L); 

// Return true iff the two lists have the same keys in the same order.
//
// Pre:  A != NULL and B != NULL.
//
// NOTE: Modified version: 5/11/2013
//       Included to handle generic data types (aka void*), now must
//       pass a function pointer to indicate what data type equals()
//       is working with and how to compare the data types to the know 
//       if A == B.
//       ex: 
//          (such as char, char*, int, long, struct ...).
int equals(ListRef A, ListRef B, int (*Compare) (void*, void*)); 

/**************************************************************************
 * Manipulation procedures 
 *************************************************************************/
// Make the list empty.
//
// Post: isEmpty().
void makeEmpty(ListRef L);  

// Set current marker to the first element in the list.
//
// Pre:  !isEmpty(). 
// Post: !offEnd().
void moveFirst(ListRef L); 

// Set current marker to the last element in the list.
//
// Pre:  !isEmpty().
// Post: !offEnd().
void moveLast(ListRef L); 

// Set current marker one step backward.
//
// Pre:  !offEnd().
// Post: offEnd() only if atFirst() was true.
void movePrev(ListRef L); 

// Set current marker one step forward.
//
// Pre:  !offEnd().
// Post: offEnd() only if atLast() was true.
void moveNext(ListRef L); 

// Inserts new element before first.
//
// Post: !isEmpty().
void insertBeforeFirst(ListRef L, void* data); 

// Inserts new element after last one.
//
// Post: !isEmpty().
void insertAfterLast(ListRef L, void* data); 

// Inserts new element before current one.
//
// Pre:  !offEnd().
// Post: !isEmpty(), !offEnd().
void insertBeforeCurrent(ListRef L, void* data); 

// Inserts new element after current one.
//
// Pre:  !offEnd().
// Post: !isEmpty(), !offEnd().
void insertAfterCurrent(ListRef L, void* data); 

// Delete the first element.
//
// Pre:  !isEmpty().
void deleteFirst(ListRef L); 

// Delete the last element.
//
// Pre:  !isEmpty().
void deleteLast(ListRef L); 

// Delete the current element.
//
// Pre:  !isEmpty(), !offEnd()
// Post: offEnd().

void deleteCurrent(ListRef L); 

/*****************************************************************************
 * Other operations 
 ****************************************************************************/
// Pre:  L != NULL.
//
// NOTE: Modified version: 5/11/2013
//       Included to handle generic data types (aka void*), now must
//       pass a function pointer to indicate what data type printList()
//       is working with and how to print the data types to the specified
//       output.
//       ex: 
//          (such as char, char*, int, long, struct ...).
void printList(FILE* out, ListRef L, void (*Print) (FILE*, void*));

// Pre:  L != NULL.
ListRef copyList(ListRef L);

// Sorts the doubly linked list in expected runtime O(n^2).
//
// Pre:  old != NULL
// Post: new list is sorted in increasing order
//
// NOTE: Modified version: 5/11/2013
//       Included to handle generic data types (aka void*), now must
//       pass a function pointer to indicate what data type insertionSort()
//       is working with and how to compare the data types to output a ListRef
//       in increasing lexographic order.
//       ex: 
//          (such as char, char*, int, long, struct ...).
ListRef insertionSort(ListRef old, int (*Compare) (void*, void*));

#endif 
