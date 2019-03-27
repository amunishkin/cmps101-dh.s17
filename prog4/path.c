/*
 * Author: Alexey A. Munishkin
 * 
 * File name: path.c
 * Date: 5/27/2013
 * Class: CMPS 101
 * 
 * This program reads in a text file which is formatted as
 * input:
 *  # of Vertices
 *  # of Queries
 * each other line as follows:
 *  mainVertix adjVertices...
 * and ending with Queries
 *  start destination
 * 
 * and produces an output message based on the last # of Queries
 * specified at the second line of input
 * output:
 *  (last # of Queries lines)
 *  Successful: To get to (a) to (b) requires (c) edges, follow the path (path).
 *  Unsuccessful: I am sorry, there is no way to get from (a) to (b) in this graph.
 *
 * where (a) is the start vertex (first number)
 *       (b) is the destination vertex (second number)
 *       (c) is the distance from (a) to (b)
 *       (path) is the shortest path from (a) to (b)
 */

#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"

#define SUCCESS 0 // Operating System program execution return status
#define FAILURE 1

/**************************************************************************
 * Function Prototypes.
 *************************************************************************/
void PrintInt(FILE* out, void* data);
void ProcessInput(FILE *input);

/**************************************************************************
 * Function Implemenations.
 *************************************************************************/
int main(int argc, char** argv)
{
    if(2 != argc){
        printf("Usage: %s file\n", argv[0]);
    }else{
        FILE* file = fopen(argv[1], "r");

        // Error-checking: valid file for reading
        if(NULL == file){
            fflush(NULL);
            printf("ERROR: opening file %s\n", argv[1]);
            fflush(NULL);
            return FAILURE;
        }

        ProcessInput(file);
        fclose(file);
    }

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

/*
 * ProcessInput(FILE*)
 * 
 * Main function other than main(), which is ment to read and process
 * the file based on the specifications at the top of this program's file.
 */
void ProcessInput(FILE* input)
{
    int numVerts, numQueries;

    // Read in the number of vertices
    int rc = fscanf(input, "%d", &numVerts);

    // Error-checking: valid read and at least one vertix
    if(0 > rc || 0 > numVerts){
        printf("ERROR: invalid read of numVerts\n");
        return; // Exit
    }

    // Read in the number of queries
    rc = fscanf(input, "%d", &numQueries);

    // Error-checking: valid read
    if(0 > rc){
        printf("ERROR: invalid read of numQueries\n");
        return; // Exit
    }

    GraphRef graph = newGraph(numVerts); // Create a graph

    // Add edges to the graph
    int i;
    for(i = 0; i < numVerts; i++){
        int vertix, adjVertix;
        char symbol;

        rc = fscanf(input, "%d%c", &vertix, &symbol);

        // Vertix with no adjacent vertices or self loops
        if('\n' == symbol){
            continue; // Don't even need to add it
        }

        // End of adding graph vertices?
        if(EOF == rc){
            break;
        }

        // Error-checking: valid read
        if(0 > rc){
            printf("ERROR: invalid read of vertix\n");
            freeGraph(graph);
            return; // Exit
        }

        // Read in the edges to this vertix        
        do{            
            rc = fscanf(input, "%d%c", &adjVertix, &symbol);

            // End of adding adjacent vertices to this vertix?
            if(EOF == rc){
                break;
            }

            addEdge(graph, vertix, adjVertix);
        }while('\n' != symbol);
    }

    // Read and process the queries
    for(i = 0; i < numQueries; i++){
        int start, end;        
        fscanf(input, "%d %d", &start, &end);

        doBFS(graph, start);
        ListRef path = getPathTo(graph, end);

        // Successful path find
        if(NULL != path){
            printf("To get from %d to %d requires %d edges, follow the path ", start, end, getDistance(graph, end));
            printList(stdout, path, PrintInt);
            printf("\n");

            // Free memory allocated by path creation
            moveFirst(path);
            while(!isEmpty(path)){
                free(getFirst(path));
                deleteFirst(path);
            }
            
            // Free memory allocated by path structure
            freeList(path);
        }
        // Unsuccessful path find
        else{
            printf("I am sorry, there is no way to get from %d to %d in this graph.\n", start, end);
            printf("\n");
        }        
    }

    // Free the memory occupied by the graph structure
    freeGraph(graph);
}
