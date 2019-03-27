
README file for Sort ADTs (heapSort and insertionSort):
-------------------------------------------------------
Author: Alexey A. Munishkin

File name: README.txt
Date: 5/1/2013
Class: CMPS 101

NOTES:
-------------------------------------------
The Sort ADTs contains the following files:
README.txt           This documentation file.
insertionSort.h      The header file describing insertionSort's ADT operations.
insertionSort.c	     The implementation of the insertionSort ADT.
heap.h               The header file describing heap's ADT operations.
heap.c               The implementation of the heap ADT.
heapdr.c             The driver program testing the module 'heapSort'.
heapSort.h           The header file describing heapSort's ADT operations.
heapSort.c           The implementation of the heapSort ADT.
sortPrint.c          Tests the output of both modules 'insertionSort' and 'heapSort'.
sortComp.c           Tests the running time of both modules 'insertionSort' and 'heapSort'.
Makefile             A makefile that complies the modules, driver, and user programs;
	             (1) it makes the object files insertionSort.o heap.o heapSort.o sortPrint.o into the executionable 'sortPrintCmp'.
	             (2) it makes the object files insertionSort.o heap.o heapSort.o sortComp.o into the executionable 'sortTimeCmp'.
	             (3) it makes the object files heap.o heapdr.o into the executionable 'driverHeap'.
                 NOTE: 'make all' or 'gmake all' compiles and links the object files into the executionable.

Experimental procedure:
-----------------------
Here are the results for various sizes (tested with random integers created by random.org)
--------------------------------------------------------------------------------------------
 size  | InsertionSort() Time (sec)                       | HeapSort() Time (sec)          |
-------|-----------------------------------------------------------------------------------|
    10 | 0, 0, 0, 0, 0, 0, 0, 0, 0                        | 0, 0, 0, 0, 0, 0, 0, 0, 0      |
-------|-----------------------------------------------------------------------------------|
   100 | 0, 0, 0, 0, 0, 0, 0, 0, 0                        | 0, 0, 0, 0, 0, 0, 0, 0, 0      |
-------|-----------------------------------------------------------------------------------|
  1000 | 0, 0, 0, 0, 0, 0, 0, 0, 0                        | 0, 0, 0, 0, 0, 0, 0, 0, 0      |
-------|-----------------------------------------------------------------------------------|
 10000 | .32, .32, .32, .32, .32, .46, .45, .46, .46, .45 | 0, 0, 0, 0, 0, .01, 0, 0, .01  |
-------|-----------------------------------------------------------------------------------|
100000 | 38.029999, 37.759998, 37.759998, 37.75, 37.75    | .03, .03, .03, .03, .03        |
-------|-----------------------------------------------------------------------------------|

Based on the results InsertionSort() and HeapSort() run in the same time for sizes 10, 100, and 1000.
However, sizes of 10000 and 100000 (and probability greater) HeapSort() is faster than InsertionSort() in
size 10000
     HeapSort() average run time:  0.002 sec
InsertionSort() average run time:  0.388 sec
and size 100000
     HeapSort() average run time:  0.03 sec
InsertionSort() average run time: 37.809999 sec

According to my data, HeapSort() is more efficient (in terms of speed) than InsertionSort.