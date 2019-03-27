/*
 * Author: Alexey A. Munishkin
 * 
 * File name: recommand.c
 * Date: 5/19/2013
 * Class: CMPS 101
 * 
 * From prog1: 4/16/2013
 * This program ulitizes the ADT module called List to read in one or more text
 * files, input the data into the ADT, and then print out the result in a nice,
 * formatted and sorted order.
 * 
 * Modified version: 5/17/2013
 * This program ulitizes two ADT modules called List and Hash to read, extract,
 * and analyze the input text and then print out a recommandation based on a thrid
 * number in addition to the customer id number and book id number.
 * ex:
 *  input: 12 1945287 0 <-- No flag (as indicated by a zero)
 *  input: 19 2983560 1 <-- A flag (as indicated by a one)
 *  output: Customers buying book 2983560 also purchased book 123498765 (as an example)
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Hash.h" // List.h defined in here also

#define SUCCESS 0
#define FAILURE 1

#define TRUE  1 // Elementary Boolean values
#define FALSE 0

/**************************************************************************
 * Global Variables.
 *************************************************************************/
int exit_status = SUCCESS;

/**************************************************************************
 * Structures.
 *************************************************************************/
// Customer Array
typedef struct ListArray{
    int length;
    ListRef* array; // ListType**
} ArrayType;

typedef ArrayType* ArrayRef;

// Book holder
typedef struct bookInfo{
    long bookId;
    int copurchaseCount;
} BookType;

typedef BookType* BookRef;

/**************************************************************************
 * Function Prototypes.
 *************************************************************************/
// Main Loop -- other than main()
void RunInput(FILE* in, FILE* out);

// Customer Array Operations
void PutDataInList(int customerData, long bookData, ArrayRef customerArray);
ArrayRef CreateArray(int size);
void FreeArray(ArrayRef arrayList, int size);
void insertIntoList(ListRef list, void* data);

// Hash Table of Books Operations
void InsertData(HashRef H, ListRef L, long key);
void FreeData(HashRef H);
void SortData(HashRef H);
int coPurchaseCompare(void* A, void* B);
void UpdateData(HashRef H, long key);
int foundKey(ListRef L, long key);

// Universal Usage
int LongCompare(void* A, void* B);
int LongCompareBook(void* A, void* B);
void PrintLongBook(FILE* out, void* data);

// Recommand Output
void Recommand(FILE* out, HashRef H, long key);

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
// Input given as:
//  # of Customers
//  # of transactions
//  size of hash table (for collision resolution by chaining)
// each other line as follows:
//  customerID# bookID# flag
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

    int hashSize;
    rc = fscanf(in, "%d", &hashSize);
    if(rc < 0){
        printf("Error in input...\n");
        return;
    }

    HashRef hashTable = NewHash(hashSize);

    for(;;){        
        int customerData;
        rc = fscanf(in, "%d", &customerData);

        if(rc < 0){
            break;
        }

        long bookData;
        rc = fscanf(in, "%ld", &bookData);

        if(rc < 0){
            fprintf(stderr, "Invalid input, customer# book# flag\n");
            exit_status = FAILURE;
            break;
        }

        int flag = FALSE;
        rc = fscanf(in, "%d", &flag);

        if(rc < 0){
            fprintf(stderr, "Invalid input, customer# book# flag\n");
            exit_status = FAILURE;
            break;
        }

        // Continue storing information
        PutDataInList(customerData, bookData, customerArray);
        InsertData(hashTable, customerArray->array[customerData - 1], bookData);
        SortData(hashTable);

        if(TRUE == flag){
            // Recommand a new book to the customer
            Recommand(out, hashTable, bookData);
        }
    }

    // Free all unused data and structures
    FreeArray(customerArray, customerArray->length);
    FreeData(hashTable);
}

/*----------------------------------------------------------------------*
 * Helper Functions.
 *---------------------------------------------------------------------*/
////////////////////////////////////////////////////////////////
// Customer Array
////////////////////////////////////////////////////////////////
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
        if(NULL != arrayList->array[i]){
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
    }

    free(arrayList->array);
    arrayList->array = NULL;
    free(arrayList);
    arrayList = NULL;
}

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

    if(isEmpty(arrayList->array[id - 1]) || !foundKey(arrayList->array[id - 1], book)){
        // Make a copy and store in the heap for perment storage
        // until clean-up at the end.
        long* book_copy = malloc(sizeof(long));
        assert(book_copy != NULL);
        *book_copy = book;

        insertIntoList(arrayList->array[id - 1], book_copy);
    }
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

////////////////////////////////////////////////////////////////
// Hash Table Book ids
////////////////////////////////////////////////////////////////
/*
 * InsertData(HashRef, ListRef, long)
 * 
 * Inserts the co-purchased book id associated with a purchased book id
 * into the hash table of book ids. Also, it updates the copurchased count
 * of the inserted book.
 */
void InsertData(HashRef H, ListRef L, long key)
{
    // Prevents repeats of same book bought, as you
    // do not want to increase the co-purchase count of an existing co-pair.
    if(!foundKey(L, key)){
        moveFirst(L);
        while(!atLast(L)){
            // Add the new co-purchase location
            BookRef book = malloc(sizeof(BookType));
            assert(book != NULL);

            // Create the structure for the item to put in the hash table
            book->copurchaseCount = 1;
            book->bookId = *((long*) getCurrent(L));
            moveNext(L);

            // Insert the new item and update the result
            Insert(H, &key, book, DivisionFunctionLong, LongCompareBook);
            UpdateData(H, key);
        }
        // Update previous co-purchase locations      
        if((getLength(L) - 1) > 0){ // Want at least two items on list
            moveFirst(L);
            while(!atLast(L)){
                // Add the new co-purchase location
                BookRef book = malloc(sizeof(BookType));
                assert(book != NULL);

                // Create the structure for the item to put in the hash table
                book->copurchaseCount = 1;
                book->bookId = *((long*) getLast(L));

                BookRef oldKeyBook = getCurrent(L);
                moveNext(L);

                // Update the old list with the new item
                Insert(H, &oldKeyBook->bookId, book, DivisionFunctionLong, LongCompareBook);
                UpdateData(H, oldKeyBook->bookId);
            }
        }
    }
}

/*
 * UpdateData(HashRef, long)
 * 
 * Updates the co-purchase counts of the hash table.
 */
void UpdateData(HashRef H, long key)
{
    int slotIndex = DivisionFunctionLong(H, &key);
    ListRef L = getSlot(H, slotIndex);
    ListRef updatedL = newList();

    while(!isEmpty(L)){
        moveFirst(L);

        BookRef updatedBook = malloc(sizeof(BookType));
        assert(NULL != updatedBook);

        BookRef tmp = getCurrent(L);
        updatedBook->bookId = tmp->bookId;
        updatedBook->copurchaseCount = tmp->copurchaseCount;

        free(tmp);
        tmp = NULL;        
        deleteCurrent(L);
        while(!offEnd(L)){            
            BookRef book = getCurrent(L);

            // Found a repeat?
            if(0 == LongCompare(&updatedBook->bookId, &book->bookId)){
                updatedBook->copurchaseCount += book->copurchaseCount;
                free(book);
                book = NULL;
                deleteCurrent(L);
            }else{
                moveNext(L);
            }
        }

        insertBeforeFirst(updatedL, updatedBook);
    }

    freeList(L);
    L = NULL;
    putSlot(H, slotIndex, updatedL);    
}

/*
 * foundKey(ListRef, long)
 * 
 * Searches through a linked list for a key: 
 *  Successful returns TRUE (1) 
 *  Unsuccessful returns FALSE (0)
 */
int foundKey(ListRef L, long key)
{
    moveFirst(L);
    while(!atLast(L)){
        BookRef book = getCurrent(L);

        if(0 == LongCompare(&key, &book->bookId)){
            return TRUE;
        }

        moveNext(L);
    }

    return FALSE;
}

/*
 * FreeData(HashRef)
 * 
 * Frees up all the memory that the hash table and its linked list occupies
 * in memory.
 */
void FreeData(HashRef H)
{
    int i;
    for(i = 0; i < getHashLength(H); i++){
        ListRef list = getSlot(H, i);
        if(NULL != list){
            // Free all the data in a linked list
            moveFirst(list);        
            while(!offEnd(list)){
                free(getCurrent(list));
                moveNext(list);
            }
        }
    }
    FreeHash(H);
}

/*
 * SortData(HashRef)
 * 
 * This functions sorts book ids by the lowest co-purchase count to be
 * the first in the linked list in the hash table. Highest is the last node.
 */
void SortData(HashRef H)
{
    int i;
    for(i = 0; i < getHashLength(H); i++){
        ListRef slot = getSlot(H, i);
        if(NULL != slot){
            slot = insertionSort(slot, coPurchaseCompare);
            putSlot(H, i, slot);
        }
    }
}

/*
 * coPurchaseSort(void*, void*)
 * 
 * This function compares book ids by the co-purchase count as described below:
 *  if A <  B returns -1
 *  if A >  B returns  1
 *  if A == B returns  0
 */
int coPurchaseCompare(void* A, void* B)
{
    BookRef A_book = (BookRef) A;
    BookRef B_book = (BookRef) B;

    if(A_book->copurchaseCount < B_book->copurchaseCount){
        return -1;
    }
    else if(A_book->copurchaseCount > B_book->copurchaseCount){
        return 1;
    }
    else{
        return 0;
    }
}

////////////////////////////////////////////////////////////////
// Universal Usage
////////////////////////////////////////////////////////////////
/*
 * LongCompare(void*, void*)
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
 * LongCompareBook(void*, void*)
 * 
 * For use with generic data type comparision. This function
 * compares two BookRefs by book ids: 
 *  if A <  B returns -1
 *  if A >  B returns  1
 *  if A == B returns  0
 */
int LongCompareBook(void* A, void* B)
{
    BookRef A_cmp = (BookRef) A;
    BookRef B_cmp = (BookRef) B;    

    if(A_cmp->bookId < B_cmp->bookId){
        return -1;
    }
    else if(A_cmp->bookId > B_cmp->bookId){
        return 1;
    }
    else{
        return 0;
    }
}

/*
 * PrintLongBook(FILE*, void*)
 * 
 * For use with generic data type printing. This function
 * prints out a long on the same line with a space after the
 * long.
 * ex:
 *  "12894532 "
 */
void PrintLongBook(FILE* out, void* data)
{
    BookRef book = (BookRef) data;
    fprintf(out, "%ld.\n", book->bookId);
}

////////////////////////////////////////////////////////////////
// Recommand Output
////////////////////////////////////////////////////////////////
/*
 * Recommand(FILE*, HashRef, long)
 * 
 * Finds the book's slot in the hash table and finds the highest co-purchase count
 * that is not the original book itself, and it returns a message about finding it and recommanding
 * a new book, not finding it, or finding a book that is not new.
 */
void Recommand(FILE* out, HashRef H, long key)
{
    ListRef L = getSlot(H, DivisionFunctionLong(H, &key));
    
    if(isEmpty(L)){
        fprintf(out, "Sorry, not enough information in your account for recommandations at this time.\n");
        return; // Exit
    }
    
    moveLast(L);
    BookRef recommandBook = getCurrent(L);
    
    if(0 == LongCompare(&recommandBook->bookId, &key)){
        movePrev(L);        
        if(!offEnd(L)){
            recommandBook = getCurrent(L);            
        }else{
            fprintf(out, "Sorry, no new recommandations based on your current buying history.\n");
            return; // Exit
        }
    }
    
    // Recommand the highest co-purchased new book 
    fprintf(out, "Customers buying book %ld also purchased book %ld.\n", key, recommandBook->bookId);
}
