/*
 * Author: Alexey A. Munishkin
 * 
 * File name: List.c
 * Date: 4/14/2013
 * Class: CMPS 101
 * 
 * This ADT implemenation creates and manages a double linked list, which is
 * accessed through an array. Each index of the array is a different customer
 * who has his own link list header. The header manages the data into yet another
 * double linked list. The front points to the first  node, which has 
 * its front point to NULL. The last points to the last node, which has its last
 * point to NULL.
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE  1

/**************************************************************************
 * Implemenation:
 *    See List.h for details on the undocumented functions below.
 *************************************************************************/
/*------------------------------------------------------------------------*
 * Structures.
 *-----------------------------------------------------------------------*/
struct Node {
    long data;
    struct Node* next; // NodeType is not declared before here, 
    struct Node* prev; // so cannot use it here.
};

typedef struct Node NodeType;
typedef NodeType* NodeRef;

struct ListHdr {
    NodeRef first;
    NodeRef last;
    NodeRef current;
    int length;
};

/*------------------------------------------------------------------------*
 * Function Prototypes.
 *-----------------------------------------------------------------------*/
#include "List.h"

NodeRef newNode(long data);
void Swap(ListRef L, NodeRef A, NodeRef B);

/*------------------------------------------------------------------------*
 * Function Implementations.
 *-----------------------------------------------------------------------*/
ListRef newList(void)
{
    ListRef list = malloc(sizeof(ListType));
    assert(list != NULL);

    list->first = NULL;
    list->last = NULL;
    list->current = NULL;
    list->length = 0;

    return list;
}

void freeList(ListRef L)
{
    assert(L != NULL);

    makeEmpty(L);
    free(L);
    L = NULL;
}

int isEmpty(ListRef L)
{
    assert(L != NULL);

    if(L->first == NULL){
        return TRUE;
    }

    return FALSE;
}

int offEnd(ListRef L)
{
    if(L->current == NULL){
        return TRUE;
    }

    return FALSE;
}

int atFirst(ListRef L)
{
    if(L->current == L->first && !offEnd(L)){
        return TRUE;
    }

    return FALSE;
}

int atLast(ListRef L)
{
    if(L->current == L->last && !offEnd(L)){
        return TRUE;
    }

    return FALSE;
}

long getFirst(ListRef L)
{
    assert(!isEmpty(L));

    return L->first->data;
}

long getLast(ListRef L)
{
    assert(!isEmpty(L));

    return L->last->data;
}

long getCurrent(ListRef L)
{
    assert(!offEnd(L));

    return L->current->data;
}

int getLength(ListRef L)
{
    return L->length;
}

int equals(ListRef A, ListRef B)
{
    assert(A != NULL);
    assert(B != NULL);

    if(getLength(A) != getLength(B)){
        return FALSE;
    }

    moveFirst(A);
    moveFirst(B);
    while(!offEnd(A)){
        if(getCurrent(A) != getCurrent(B)){
            return FALSE;
        }
        moveNext(A);
        moveNext(B);
    }

    return TRUE;
}

void makeEmpty(ListRef L)
{
    if(L->length == 0){
        // Already empty
    }else{
        moveFirst(L);
        while(!offEnd(L)){
            moveNext(L);
            deleteFirst(L);
        }
        
        L->length = 0;
    }
}

void moveFirst(ListRef L)
{
    assert(!isEmpty(L));

    L->current = L->first;
}

void moveLast(ListRef L)
{
    assert(!isEmpty(L));

    L->current = L->last;
}

void movePrev(ListRef L)
{
    assert(!offEnd(L));

    L->current = L->current->prev;
}

void moveNext(ListRef L)
{
    assert(!offEnd(L));

    L->current = L->current->next;
}

void insertBeforeFirst(ListRef L, long data)
{
    NodeRef node = newNode(data);
    node->next = L->first;
    if(L->first != NULL){
        L->first->prev = node;
    }
    L->first = node;

    // Create Link
    if(L->first->next == NULL){
        L->last = node;
    }

    L->length++;
}

void insertAfterLast(ListRef L, long data)
{
    NodeRef node = newNode(data);
    node->prev = L->last;
    if(L->last != NULL){
        L->last->next = node;
    }
    L->last = node;

    // Create Link
    if(L->last->prev == NULL){
        L->first = node;
    }

    L->length++;
}

void insertBeforeCurrent(ListRef L, long data)
{
    assert(!offEnd(L));

    NodeRef node = newNode(data);
    node->next = L->current;
    node->prev = L->current->prev;
    if(L->current->prev != NULL){
        L->current->prev->next = node;
        L->current->prev = node;
    }

    // Keep Link right
    if(L->first == L->current){
        L->first = node;
    }

    L->length++;
}

void insertAfterCurrent(ListRef L, long data)
{
    assert(!offEnd(L));

    NodeRef node = newNode(data);
    node->prev = L->current;
    node->next = L->current->next;
    if(L->current->next != NULL){
        L->current->next->prev = node;
        L->current->next = node;
    }

    // Keep Link right
    if(L->last == L->current){
        L->last = node;
    }

    L->length++;
}

void deleteFirst(ListRef L)
{
    assert(!isEmpty(L));

    if(L->length == 1){
        free(L->first);
        L->first = L->last = L->current = NULL;
    }else{
        L->first = L->first->next;
        free(L->first->prev);
        L->first->prev = NULL;
    }

    L->length--;
}

void deleteLast(ListRef L)
{
    assert(!isEmpty(L));

    if(L->length == 1){
        free(L->last);
        L->first = L->last = L->current = NULL;
    }else{
        L->last = L->last->prev;
        free(L->last->next);
        L->last->next = NULL;
    }

    L->length--;
}

void deleteCurrent(ListRef L)
{
    assert(!isEmpty(L));
    assert(!offEnd(L));

    if(L->length == 1){
        free(L->current);
        L->first = L->last = L->current = NULL;
    }
    else if(atFirst(L) || atLast(L)){
        if(atFirst(L)){
            deleteFirst(L);
            L->current = L->first;
        }else{
            deleteLast(L);
            L->current = L->last;
        }
        return;
    }
    else{
        L->current = L->current->next;
        L->current->prev = L->current->prev->prev;
        free(L->current->prev->next);
        L->current->prev->next = L->current;
    }

    L->length--;
}

void printList(FILE* out, ListRef L)
{
    assert(L != NULL);

    moveFirst(L);
    int i;
    for(i = 0; i < L->length; i++){
        fprintf(out, "%ld ", getCurrent(L));
        moveNext(L);
    }
    fprintf(out, "\n");
}

ListRef copyList(ListRef L)
{
    assert(L != NULL);

    ListRef copyList = newList();

    moveFirst(L);
    insertBeforeFirst(copyList, L->current->data);

    moveFirst(copyList);
    int i;
    for(i = 0; i < (L->length - 1); i++){
        moveNext(L);
        insertAfterCurrent(copyList, L->current->data);
        moveNext(copyList);
    }

    assert(L->length == copyList->length);

    return copyList;
}

ListRef insertionSort(ListRef old)
{
    assert(old != NULL);

    ListRef new = newList();

    for(; old->length > 0;){
        moveFirst(old);
        new->current = old->current;
        long tmp_data_A = new->current->data;

        for(; !offEnd(old); moveNext(old)){
            long tmp_data_B = getCurrent(old);

            if(tmp_data_A > tmp_data_B){
                tmp_data_A = tmp_data_B;
                new->current = old->current;
            }
        }

        old->current = new->current;
        deleteCurrent(old);
        insertAfterLast(new, tmp_data_A);
    }

    freeList(old);

    return new;
}

/*------------------------------------------------------------------------*
 * Helper Functions.
 *-----------------------------------------------------------------------*/
// Creates a new double linked node to store the passed data, and returns it.
NodeRef newNode(long data)
{
    NodeRef node = malloc(sizeof(NodeType));
    assert(node != NULL);

    node->data = data;
    node->next = NULL;
    node->prev = NULL;

    return node;
}

