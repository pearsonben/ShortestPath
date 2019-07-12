#include <stdio.h>
#include <stdlib.h>
#define MAX 50
#include <string.h>
#include "shortestPath.h"


int main(void){
    // creating the struct that store the data of the road connections
    struct intertown_distance* roads[1024];
    struct citypairs* citypairs[100];

    // creating the adjacency matrix
    int graph[MAX][MAX];

    //initialising the adjacency matrix, set all values to 0
    initialiseGraph(graph);

    // loads the structs with values taken from the ukcities and citypairs text files
    storeCityPairs(citypairs);
    storeRoads(roads);

    // stores the city names and nodes into a global cities array, defined in the .c file
    storeCities();

    // sorts the roads structure with shortest distances at the top
    heapsort(roads, getRoadsSize(roads));

    // adding the weights to the adjacency matrix
    addEdges(roads, graph);

    // clears the paths.txt file
    clearPathsFile();

    //runs the dijkstra algorithm for the links specified in the citypairs file
    shortestPaths(graph, citypairs);

    // prints the path data
    printPaths();

    // attempting to free all memory associated with the data structure arrays 'roads' and 'citypairs'
    // however this is buggy, the memory is not freed correctly
    destroyCityPairs(citypairs);
    destroyRoads(roads);

    return 0;
}

