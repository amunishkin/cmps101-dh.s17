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
 */

#ifndef __LIST_H__
#define __LIST_H__

/*------------------------------------------------------------------------*
 * Structures.
 *-----------------------------------------------------------------------*/
typedef struct ListHdr ListType;
typedef ListType* ListRef;

/**************************************************************************
 * Constructors-Destructors 
 *************************************************************************/
// Constructors
ListRef newList(void);

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
long getFirst(ListRef L); 

// Return the last element.
//
// Pre:  !isEmpty().
long getLast(ListRef L); 

// Return the current element.
//
// Pre:  !offEnd().
long getCurrent(ListRef L); 

// Return the length of the list.
int getLength(ListRef L); 

// Return true iff the two lists have the same keys in the same order.
//
// Pre:  A != NULL and B != NULL.
int equals(ListRef A, ListRef B); 

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
void insertBeforeFirst(ListRef L, long data); 

// Inserts new element after last one.
//
// Post: !isEmpty().
void insertAfterLast(ListRef L, long data); 

// Inserts new element before current one.
//
// Pre:  !offEnd().
// Post: !isEmpty(), !offEnd().
void insertBeforeCurrent(ListRef L, long data); 

// Inserts new element after current one.
//
// Pre:  !offEnd().
// Post: !isEmpty(), !offEnd().
void insertAfterCurrent(ListRef L, long data); 

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
void printList(FILE* out, ListRef L);

// Pre:  L != NULL.
ListRef copyList(ListRef L);

// Pre:  old != NULL
// Post: new list is sorted in increasing order
ListRef insertionSort(ListRef old);

#endif 
