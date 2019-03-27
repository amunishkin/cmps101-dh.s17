/*
 * Author: Alexey A. Munishkin
 * 
 * File name: Graphdr.c
 * Date: 5/26/2013
 * Class: CMPS 101
 * 
 * This diver program tests the functionality of the module Graph, which is composed
 * of the interface, Graph.h, and the implementation, Graph.c.
 */

#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"

#define SUCCESS 0 // Operating System program execution return status
#define FAILURE 1

#define GRAPH_SIZE 10 // Max size for graph

/**************************************************************************
 * Function Prototypes.
 *************************************************************************/
void PrintInt(FILE* out, void* data);

/**************************************************************************
 * Function Implemenations.
 *************************************************************************/
// Input given as:
//  # of Vertices
//  # of Queries
// each other line as follows:
//  mainVertix adjVertices...
int main(void)
{
    int numVerts, numQueries;

    // Read in the number of vertices
    int rc = scanf("%d", &numVerts);

    // Error-checking: valid read and at least one vertix
    if(0 > rc || 0 > numVerts){
        printf("ERROR: invalid read of numVerts\n");
        return FAILURE;
    }

    // Read in the number of queries
    rc = scanf("%d", &numQueries);

    // Error-checking: valid read
    if(0 > rc){
        printf("ERROR: invalid read of numQueries\n");
        return FAILURE;
    }

    GraphRef graph = newGraph(numVerts); // Create a graph

    // Add edges to the graph
    int i;
    for(i = 0; i < GRAPH_SIZE; i++){
        int vertix, adjVertix;
        char symbol;

        rc = scanf("%d%c", &vertix, &symbol);
        
        // Vertix with no adjacent vertices or self loops
        if('\n' == symbol){
            continue; // Don't even need to add it
        }

        // End of adding graph vertices?
        if(EOF == rc ){
            break;
        }

        // Error-checking: valid read
        if(0 > rc){
            printf("ERROR: invalid read of vertix\n");
            freeGraph(graph);
            return FAILURE;
        }

        // Read in the edges to this vertix        
        do{            
            rc = scanf("%d%c", &adjVertix, &symbol);

            // End of adding adjacent vertices to this vertix?
            if(EOF == rc){
                break;
            }

            addEdge(graph, vertix, adjVertix);
        }while('\n' != symbol);
    }

    // Print the graph
    PrintGraph(graph);

    // Do Breadth-First Search a couple of times at different
    // locations and print results of each.
    doBFS(graph, 5); // Test with vertix 5
    ListRef path = getPathTo(graph, 4);
    
    printf("Here is a path from 5 to 4\n");
    printList(stdout, path, PrintInt); // To vertix 4
    printf("Distance: %d\n", getDistance(graph, 4));

    // Free the memory occupied by the graph structure and path
    freeGraph(graph);
    
    moveFirst(path);
    while(!isEmpty(path)){
        free(getFirst(path));
        deleteFirst(path);
    }
    
    freeList(path);

    return SUCCESS;
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
void PrintInt(FILE* out, void* data)
{
    fprintf(out, "%d ", *((int*) data));
}
