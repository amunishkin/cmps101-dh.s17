/*
 * Author: Alexey A. Munishkin
 * 
 * File name: Graph.c
 * Date: 5/26/2013
 * Class: CMPS 101
 * 
 * This ADT implemenation creates and manages a directed (unweighted) graph.
 * This graph ADT uses the List ADT to create an adjacency representation of
 * a graph.
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "Graph.h"

#define NO_DISTANCE -1
#define NO_PARENT -1

/**************************************************************************
 * Implemenation:
 *    See Graph.h for details on the undocumented functions below.
 *************************************************************************/
/*------------------------------------------------------------------------*
 * Structures.
 *-----------------------------------------------------------------------*/
typedef enum color {WHITE, GREY, BLACK} color;

typedef struct vertix {
    ListRef adjVerts;
    int distance; // Distance from source to desition (crossing here)
    int parent; // BFS parent
    color mainVertColor; // BFS processing
} adjList;

struct GraphType {
    adjList* vertices;
    int numVerts;
    int numQueries; // Number of paths
};

/*------------------------------------------------------------------------*
 * Function Prototypes.
 *-----------------------------------------------------------------------*/
void PrintIntGraph(FILE* out, void* data);

/*------------------------------------------------------------------------*
 * Function Implementations.
 *-----------------------------------------------------------------------*/
GraphRef newGraph(int n)
{
    assert(n > 0);

    GraphRef G = malloc(sizeof(GraphArray));
    assert(G != NULL);

    // Create the adjacency list of size n
    G->vertices = malloc(n * sizeof(adjList));
    assert(G->vertices != NULL);

    G->numVerts = n; // Set how many vertices there are in the graph

    // Clear all the memory
    int i;
    for(i = 0; i < n; i++){
        G->vertices[i].adjVerts = NULL;
        G->vertices[i].distance = NO_DISTANCE;
        G->vertices[i].mainVertColor = WHITE;
        G->vertices[i].parent = NO_PARENT;        
    }

    return G;
}

void freeGraph(GraphRef G)
{
    assert(G != NULL);

    // Free all the lists
    int i;
    for(i = 0; i < G->numVerts; i++){

        if(NULL != G->vertices[i].adjVerts){
            // Free all the memory used by the vertices
            moveFirst(G->vertices[i].adjVerts);
            while(!offEnd(G->vertices[i].adjVerts)){
                free(getCurrent(G->vertices[i].adjVerts));
                moveNext(G->vertices[i].adjVerts);
            }

            freeList(G->vertices[i].adjVerts);
            G->vertices[i].adjVerts = NULL;
        }
    }

    // Free the main structures
    free(G->vertices);
    G->vertices = NULL;
    free(G);
    G = NULL;
}

int getDistance(GraphRef G, int destination)
{
    assert(G != NULL);
    assert(destination < G->numVerts);

    return G->vertices[destination].distance;
}

ListRef getPathTo(GraphRef G, int destination)
{
    assert(G != NULL);
    assert(destination < G->numVerts);

    // Retrace the steps from the destination
    ListRef path = newList();

    int vertix, end = destination;  
    do{
        vertix = G->vertices[end].parent;

        // Check if there is a backtrace
        if(NO_PARENT != vertix){
            int* vertixPtr = malloc(sizeof(int));
            assert(vertixPtr != NULL);
            *vertixPtr = vertix;

            insertBeforeFirst(path, vertixPtr);
            end = vertix;
        }else{
            break; // Exit
        }

    }while(end != NO_PARENT);

    // Successful path find
    if(end != destination){
        // Add the destination to the list
        int* vertixPtr = malloc(sizeof(int));
        assert(vertixPtr != NULL);
        *vertixPtr = destination;

        insertAfterLast(path, vertixPtr);
        return path;
    }
    
    // Failure
    freeList(path);
    return NULL;
}

void addEdge(GraphRef G, int from, int to)
{
    assert(G != NULL);
    assert(from < G->numVerts);
    assert(to < G->numVerts);

    // Add the edge to the adjacency List
    int* data = malloc(sizeof(int));
    assert(data != NULL);
    *data = to;

    // Check if there is a list, if not then create one
    if(NULL == G->vertices[from].adjVerts){
        G->vertices[from].adjVerts = newList();
    }

    insertAfterLast(G->vertices[from].adjVerts, data);
}

// Implemenation of the Breadth-First Search Algorithm
// Runtime -- O(V + E) -- NOTE: V = |V|, cardinality not abs()
void doBFS(GraphRef G, int source)
{
    // Uses a list to implement the queue
    ListRef queue = newList(); // Start with empty queue

    // Start vertix: source
    G->vertices[source].mainVertColor = GREY; // s
    G->vertices[source].distance = 0; // Set distance: d(s) = 0, Set parent: pi(s) = NO_PARENT
    insertBeforeFirst(queue, &source);

    while(!isEmpty(queue)){
        int* vertix = (int*) getFirst(queue); // u

        // Search and process each adjancent vertix
        ListRef L = G->vertices[*vertix].adjVerts;

        // Test if empty to whither search each adjacent vertix
        if(NULL != L){
            moveFirst(L); // Not empty, then search
            while(!offEnd(L)){
                int* index = (int*) getCurrent(L); // v

                if(WHITE == G->vertices[*index].mainVertColor){
                    G->vertices[*index].mainVertColor = GREY; // Set to processing
                    G->vertices[*index].distance = G->vertices[*vertix].distance + 1; // Set distance: d(v) = d(u) + 1
                    G->vertices[*index].parent = *vertix; // Set parent: pi(v) = u
                    insertAfterLast(queue, index);
                }

                moveNext(L);
            }
        }

        // Done processing this vertex on queue
        G->vertices[*vertix].mainVertColor = BLACK;
        deleteFirst(queue);
    }

    // Free the memory used by the queue
    freeList(queue);
}

void PrintGraph(GraphRef G)
{
    printf("\n");

    int i;
    for(i = 0; i < G->numVerts; i++){

        // Print only valid lists
        if(NULL != G->vertices[i].adjVerts){
            printf("Vertix[%d] -> ", i);
            printList(stdout, G->vertices[i].adjVerts, PrintIntGraph);
        }
    }

    printf("\n");
}

/*------------------------------------------------------------------------*
 * Helper Functions.
 *-----------------------------------------------------------------------*/
/*
 * PrintInt(FILE*, void*)
 * 
 * For use with generic data type printing. This function
 * prints out an int on the same line with a space after the
 * int.
 * ex:
 *  "4 "
 */
void PrintIntGraph(FILE* out, void* data)
{
    fprintf(out, "%d ", *((int*) data));
}
