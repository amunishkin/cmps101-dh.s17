/*
 * Author: Alexey A. Munishkin
 * 
 * File name: heapSort.h
 * Date: 4/28/2013
 * Class: CMPS 101
 * 
 * This ADT interface allows the user to use the module 'heapSort'. This priority queque based
 * algorithm should run at O(nlgn) speed to sort 'n' keys. The implemenation code uses an array
 * based data structure to create the heap structure.
 */

#ifndef __HEAPSORT_H__
#define __HEAPSORT_H__

// Sorts the array in increasing order
//
// Pre:  keys != NULL and numKeys > 0
// Post: sorted keys[]
void heapSort(int keys[], int numKeys);

#endif
