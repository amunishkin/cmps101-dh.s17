/*
 * Author: Alexey A. Munishkin
 * 
 * File name: insertionSort.c
 * Date: 4/27/2013
 * Class: CMPS 101
 * 
 * This simple ADT implemenation of the module 'insertionSort' sorts an array using
 * the insertion sort algorithm, which has expected run time of O(n^2).
 */

#include <stdlib.h>
#include <assert.h>

/**************************************************************************
 * Implemenation:
 *    See insertionSort.h for details on the undocumented functions below.
 *************************************************************************/
/*------------------------------------------------------------------------*
 * Function Prototypes.
 *-----------------------------------------------------------------------*/
#include "insertionSort.h"

/*------------------------------------------------------------------------*
 * Function Implementations.
 *-----------------------------------------------------------------------*/
void insertionSort(int keys[], int numKeys)
{
    assert(keys != NULL);
    assert(numKeys > 0);
    
    // Sort in increasing order
    int i;
    for(i = 0; i < numKeys; i++){
        int j;
        for(j = 0; j < numKeys; j++){
            // Swap if left key is > right key
            if(keys[i] < keys[j]){
                int tmp = keys[i];
                keys[i] = keys[j];
                keys[j] = tmp;
            }
        }
    }
}
