#
# Author: Alexey A. Munishkin
#
# File name: Makefile
# Date: 4/28/2013
# Class: CMPS 101
#
# This Makefile compiles the three modules 'insertionSort', 'heapSort' and 'heap', the driver program
# for the module 'heapSort', and two user programs and links them into three executionables 'sortOutCmp',
# 'sortTimeCmp' and 'driverHeap'.
#

MKFILE       = Makefile
GMAKE        = gmake --no-print-directory

GCC          = gcc -g -O0 -Wall -Wextra -std=gnu99

CSOURCE      = insertionSort.c heapSort.c heap.c heapdr.c sortPrint.c sortComp.c
CHEADER      = insertionSort.h heapSort.h heap.h
OBJECTS      = ${CSOURCE:.c=.o}
EXECBINS     = driverHeap sortPrintCmp sortTimeCmp
SUBMITS      = ${CHEADER} ${CSOURCE} ${MKFILE} README
SOURCES      = ${SUBMITS}
PROJECT      = cmps101-dh.s13 prog2

all : ${EXECBINS}

sortPrintCmp : insertionSort.o heapSort.o heap.o sortPrint.o
	${GCC} -o $@ insertionSort.o heapSort.o heap.o sortPrint.o

sortTimeCmp : insertionSort.o heapSort.o heap.o sortComp.o
	${GCC} -o $@ insertionSort.o heapSort.o heap.o sortComp.o

driverHeap : heapdr.o heap.o
	${GCC} -o $@ heapdr.o heap.o

%.o : %.c
	${GCC} -c $<
	
ci :
	- checksource ${SOURCES}
	- cid ${SOURCES}

clean :
	- rm ${OBJECTS}

spotless : clean
	- rm ${EXECBINS}

submit : ${SUBMITS}
	submit ${PROJECT} ${SUBMITS}

again :
	${GMAKE} spotless ci all
