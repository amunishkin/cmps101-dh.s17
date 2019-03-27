#
# Author: Alexey A. Munishkin
#
# File name: Makefile
# Date: 4/14/2013
# Class: CMPS 101
#
# This Makefile constructs the executationable files 'driverProgram' 
# and 'userProgram' from the the user code 'store.c', module 'List', 
# which is composed of List.h and List.c, and the driver code 'Listdr.c.
#

MKFILE       = Makefile
GMAKE        = gmake --no-print-directory

GCC          = gcc -g -O0 -Wall -Wextra -std=gnu99

CSOURCE      = List.c Listdr.c store.c
CHEADER      = List.h
OBJECTS      = ${CSOURCE:.c=.o}
EXECBINDRI   = testList 
EXECBINUSE   = userList
SUBMITS      = ${CHEADER} ${CSOURCE} ${MKFILE} README
SOURCES      = ${SUBMITS}
PROJECT      = cmps101-dh.s13 proj1

all : ${EXECBINDRI} ${EXECBINUSE}

${EXECBINDRI} : List.o Listdr.o
	${GCC} -o $@ List.o Listdr.o
	
${EXECBINUSE} : List.o store.o
	${GCC} -o $@ List.o store.o

%.o : %.c
	${GCC} -c $<
	
ci :
	- checksource ${SOURCES}
	- cid ${SOURCES}

clean :
	- rm ${OBJECTS}

spotless : clean
	- rm ${EXECBINDRI} ${EXECBINUSE}

submit : ${SUBMITS}
	submit ${PROJECT} ${SUBMITS}

again :
	${GMAKE} spotless ci all
