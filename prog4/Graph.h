/*
 * Author: Alexey A. Munishkin
 * 
 * File name: Graph.h
 * Date: 5/23/2013
 * Class: CMPS 101
 * 
 * Acknowledgments: Prof. Helmhold for sample code for (.h) file.
 * 
 * This ADT interface allows the user to manuplate a simple graph (no weights added
 * to the vertixes or edges) that is directed.
 */

#ifndef GRAPH_H_
#define GRAPH_H_

#include "List.h" // Creates a graph using the adjacency list implemenation

/*------------------------------------------------------------------------*
 * Structures.
 *-----------------------------------------------------------------------*/
typedef struct GraphType GraphArray;
typedef GraphArray* GraphRef;

/**************************************************************************
 * Constructors-Destructors 
 *************************************************************************/
// Constructor: Creates a new graph with n vertices numbered 0 to n-1 and no edges, 
// and returns a handle to it.
//
// Pre:  n > 0
GraphRef newGraph(int n);

// Destructor: Frees the storage used by a no longer needed Graph ADT object.
//
// Pre:  G != NULL
void freeGraph(GraphRef G);


/**************************************************************************
 * Access functions 
 *************************************************************************/
// Returns the number of edges in the shortest path from
// the last BFS source to the destination.
//
// Pre:  G != NULL and destination within range of G
// Post: on Success returns distance from doBFS (source-->destination)
//       on Failure returns -1
int getDistance(GraphRef G, int destination);

// Returns a List containing the path from the last doBFS
// source to the destination, or a null pointer if no such path exists.
// 
// Pre:  G != NULL and destination within range of G
// Post: on Success returns List from doBFS (source-->destination)
//       on Failure returns NULL
ListRef getPathTo(GraphRef G, int destination);

/**************************************************************************
 * Manipulation procedures 
 *************************************************************************/
// Adds the edge (from, to) to the graph.
//
// Pre:  G != NULL and from and to be within the range of G
void addEdge(GraphRef G, int from, int to);

// Performs BFS and updates the graph’s parent and distance arrays. This
// will erase the results of any previous BFS.
//
// Pre:  G != NULL and source is within range of G
void doBFS(GraphRef G, int source);

/*****************************************************************************
 * Other operations 
 ****************************************************************************/
// Prints out the edges for each vertix in the graph starting with the first
// vertix added to the graph and ending with the last vertix added to the graph.
//
// Pre:  G != NULL
void PrintGraph(GraphRef G);

#endif
