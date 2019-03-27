#
# Author: Alexey A. Munishkin
#
# File name: Makefile
# Date: 5/18/2013
# Class: CMPS 101
#
# This Makefile compiles the 
#

MKFILE       = Makefile
GMAKE        = gmake --no-print-directory

GCC          = gcc -g -O0 -Wall -Wextra -std=gnu99

CSOURCE      = List.c Listdr.c Hash.c Hashdr.c recommand.c
CHEADER      = List.h Hash.h
OBJECTS      = ${CSOURCE:.c=.o}
EXECBINS     = ListTest HashTest Recommand
SUBMITS      = ${CHEADER} ${CSOURCE} ${MKFILE} README
SOURCES      = ${SUBMITS}
PROJECT      = cmps101-dh.s13 prog3

all : ${EXECBINS}

ListTest : List.o Listdr.o
	${GCC} -o $@ List.o Listdr.o

HashTest : Hash.o Hashdr.o List.o
	${GCC} -o $@ Hash.o Hashdr.o List.o

Recommand : Hash.o List.o recommand.o
	${GCC} -o $@ Hash.o List.o recommand.o

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
