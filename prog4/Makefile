#
# Author: Alexey A. Munishkin
#
# File name: Makefile
# Date: 5/27/2013
# Class: CMPS 101
#
# This Makefile compiles the two modules 'List' and 'Graph' and creates three
# execbinationable binaries called ListTest, GraphTest, and GetShortestPath.
#

MKFILE       = Makefile
GMAKE        = gmake --no-print-directory

GCC          = gcc -g -O0 -Wall -Wextra -std=gnu99

CSOURCE      = List.c Listdr.c Graph.c Graphdr.c path.c
CHEADER      = Graph.h Graph.h
OBJECTS      = ${CSOURCE:.c=.o}
EXECBINS     = ListTest GraphTest GetShortestPath
SUBMITS      = ${CHEADER} ${CSOURCE} ${MKFILE} README
SOURCES      = ${SUBMITS}
PROJECT      = cmps101-dh.s13 prog4

all : ${EXECBINS}

ListTest : List.o Listdr.o
	${GCC} -o $@ List.o Listdr.o

GraphTest : Graph.o Graphdr.o List.o
	${GCC} -o $@ Graph.o Graphdr.o List.o

GetShortestPath : Graph.o List.o path.o
	${GCC} -o $@ Graph.o List.o path.o

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
