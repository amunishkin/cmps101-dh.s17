/*
 * Author: Alexey A. Munishkin
 * 
 * File name: insertionSort.h
 * Date: 4/27/2013
 * Class: CMPS 101
 * 
 * This simple ADT interface allows the user to use the module 'insertionSort'. 
 * This algorithm should run at O(n^2) speed to sort 'n' keys. The implemenation 
 * code uses the array given to sort the keys.
 */

#ifndef __INSERTIONSORT_H__
#define __INSERTIONSORT_H__

// Sorts the array in increasing order
//
// Pre:  keys != NULL and numKeys > 0
// Post: sorted keys[]
void insertionSort(int keys[], int numKeys);

#endif
