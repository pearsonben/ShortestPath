#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX 50
#define INFINITY 9999
#include "shortestPath.h"

// this data structure is used to represent roads that connect two cities
struct intertown_distance{
    char start[256];
    char end[256];
    int distance;
};

// structure to represent a pair of cities to find the shortest path between
struct city_pairs{
    char start[256];
    char end[256];
};

// global variables to keep track of the size of the array of structures
// the arrays being: intertown_distance* roads[1024] and citypairs* citypairs[100]
int numberOfPaths;
int numberOfRoads;

// global array of strings to represent all the different city names in the graph
// only used to convert from node value to node name
// for example before being heapsorted, "York" has a node value of 0, because cities[0] is = "York"
char cities[100][256];

// this function generates a road, with a start, end, and a distance from one to the other
// implementation of the constructors adapted from Lab 2
// https://www.elec.york.ac.uk/internal_web/meng/yr2/modules/Algorithms_and_Numerical_Methods/DSA/Labs/Scripts/Lab2-ComplexNumbers.pdf
struct intertown_distance* intertownDistanceConstructor(char start[256], char end[256], int distance){
    // creating an instance of the struct
    struct intertown_distance* intertown_distance;
    // allocating memory equal to the size of the structure
    intertown_distance = malloc(sizeof(struct intertown_distance));
    // copying the functions arguments values into the structures elements
    intertown_distance->distance = distance;

    // copying the functions arguments values into the structures elements
    // strcpy explanation and implementation from https://www.tutorialspoint.com/c_standard_library/c_function_strcpy.htm
    strcpy(intertown_distance->start, start);
    strcpy(intertown_distance->end, end);

    return intertown_distance;
}

// implementation of the destructors adapted from Lab 2
// https://www.elec.york.ac.uk/internal_web/meng/yr2/modules/Algorithms_and_Numerical_Methods/DSA/Labs/Scripts/Lab2-ComplexNumbers.pdf
void intertownDistanceDestructor(struct intertown_distance* intertown_distance){
    // theoretically supposed to free all memory associated with the struct passed as an argument
    // however this function is buggy, and the memory does not get freed correctly
    free(intertown_distance);
}

// function to free all memory associated with every structure in the array of structs
void destroyRoads(struct intertown_distance* roads[1024]){
    int i;
    for(i = 0;i < getRoadsSize(roads); i++){
       intertownDistanceDestructor(roads[i]);
    }
}

// function which creates the nodes to find the shortest path between
// implementation of the constructors adapted from Lab 2
// https://www.elec.york.ac.uk/internal_web/meng/yr2/modules/Algorithms_and_Numerical_Methods/DSA/Labs/Scripts/Lab2-ComplexNumbers.pdf
struct city_pairs* cityPairsConstructor(char start[256], char end[256]){
    // creating an instance of the data structure
    struct city_pairs* cityPairs;

    // allocating memory equal to the size of the structure
    cityPairs = malloc(sizeof(struct city_pairs));

    // copying the functions arguments values into the structures elements
    // strcpy explanation and implementation from https://www.tutorialspoint.com/c_standard_library/c_function_strcpy.htm
    strcpy(cityPairs->start, start);
    strcpy(cityPairs->end, end);

    return cityPairs;
};

// frees all memory associated with the structure passed as the argument
// implementation of the destructors adapted from Lab 2
// https://www.elec.york.ac.uk/internal_web/meng/yr2/modules/Algorithms_and_Numerical_Methods/DSA/Labs/Scripts/Lab2-ComplexNumbers.pdf
void cityPairsDestructor(struct city_pairs* citypairs){
    free(citypairs);
}

// destroy all memory associated with every structure in the array of structures
void destroyCityPairs(struct city_pairs* citypairs[100]){
    int i;
    for(i = 0; i < getCityPairsSize(citypairs); i++){
        cityPairsDestructor(citypairs[i]);
    }
}

// this function returns the length of the road
int getDistanceBetween(struct intertown_distance* intertown_distance){
    return intertown_distance->distance;
}

// this function returns the endpoint of the road
// the explanation and implementation of returning char arrays can be found on tutorialspoint
// https://www.tutorialspoint.com/cprogramming/c_return_arrays_from_function.htm
char *getEndLocation(struct intertown_distance* intertown_distance){
    return intertown_distance->end;
}

// this function returns the start of the road
// the explanation and implementation of returning char arrays can be found on tutorialspoint
// https://www.tutorialspoint.com/cprogramming/c_return_arrays_from_function.htm
char *getStartLocation(struct intertown_distance* intertown_distance){
    return intertown_distance->start;
}

// return the starting node to be used for the shortest path algorithm
char *cityPairsStart(struct city_pairs* citypairs){
    return citypairs->start;
}

// return the end node to be used for the shortest path algorithm
char *cityPairsEnd(struct city_pairs* citypairs){
    return citypairs->end;
}

// scans through the ukcities.txt file, storing contents into the array of intertown_distance structures
// this code was adapted for my purposes from tutorialspoint
// https://www.tutorialspoint.com/cprogramming/c_file_io.htm
// storing information from the text file implementation found at overiq.com
// https://overiq.com/c-programming-101/fscanf-function-in-c/
void storeRoads(struct intertown_distance* roads[1024]){
    // defining a pointer to a text file, in read mode
    FILE *ukcities;
    ukcities = fopen("ukcities.txt","r");

    // definind variables to temporarily store each value
    char start[256];
    char end[256];
    int distance;

    int i = 0;

    // while loop iterates through every line in the ukcities file
    // each line of the file gets stored in an one element of the intertown_distances data structure array
    // fscanf functionality and usage for storing values from a file implementation adapted from overiq.com
    // != fscanf returns -1 when it has reached the end of the file, so != -1 means: while(not reached end of file)
    while(fscanf(ukcities,"%s %s %d", start, end, &distance) != -1){
        // creates a new instance of intertown_distance
        roads[i] = intertownDistanceConstructor(strdup(start),strdup(end),distance);

        // for each road that gets added, the global variable road counter increments by 1
        numberOfRoads++;
        i++;
    }
}

// function to pass the value of the global variable numberOfRoads into the main function
int getRoadsSize(struct intertown_distance* roads[1024]){
   return numberOfRoads;
}

// scans through the citypairs.txt file, storing contents into the array of citypairs structures
// this code was adapted for my purposes from tutorialspoint
// https://www.tutorialspoint.com/cprogramming/c_file_io.htm
// storing information from the text file implementation found at overiq.com
// https://overiq.com/c-programming-101/fscanf-function-in-c/
void storeCityPairs(struct city_pairs* citypairs[100]){
    // instantiating a pointer to a text file in read mode
    FILE *cityPairs;
    cityPairs = fopen("citypairs.txt", "r");
    int i;

    // temporary variables to store the contents of each line of the file
    char start[256];
    char end[256];

    // while file has not reached the end, create instances of citypairs
    while(fscanf(cityPairs, "%s %s", start, end) != -1){
        citypairs[i] = cityPairsConstructor(strdup(start), strdup(end));

        // for each path that gets added, the global variable counter increases
        numberOfPaths++;
        i++;
    }
    return citypairs;
};

// returns the number of paths
int getCityPairsSize(struct city_pairs* citypairs[100]){
    return numberOfPaths;
}

// initialising the adjacency matrix, setting all edge weights to 0 initially
// this is done because 0 implies no edge between vertices on the graph, therefore when adding edges,
// theres no need to worry about adding edges of weight 0 for every other node
// implementation from https://www.log2base2.com/data-structures/graph/adjacency-matrix-representation-of-graph.html
void initialiseGraph(int graph[MAX][MAX]){
    int i,j;
    // iterate through every element in the array
    for(i = 0; i < MAX; i++)
        for(j = 0; j < MAX; j++)
            // set every node value to 0
            graph[i][j] = 0;
}

// used for testing to see if the adjacency matrix has been initialised and updated correctly
// iterates through the matrix printing all elements
// implementation adapted from https://www.log2base2.com/data-structures/graph/adjacency-matrix-representation-of-graph.html
void printGraph(int adjacency[MAX][MAX]){
    printf("\n\nAdjacency Matrix: \n");
    int i,j;
    // iterates over every element of the array
    for(i = 0; i < numberOfRoads; i++){
        for(j = 0; j < numberOfRoads; j++){
            // prints each element
            printf("%d ", adjacency[i][j]);
        }
        printf("\n");
    }
    printf("\n\n");
}

// adding weighted edges to the adjacency matrix
// adapted implementation from https://www.log2base2.com/data-structures/graph/adjacency-matrix-representation-of-graph.html
// this function takes the arguments of the node values of the cities
// eg the node value of York would be 0, Leeds would be 1, etc, depending on when they first appear in the ukcities text file
void addEdge(int graph[MAX][MAX], int source, int destination, int distance){
    // as the graph is undirected, meaning roads can go both ways, you need to set the weights equal on each side of the matrix
    graph[source][destination] = distance;
    graph[destination][source] = distance;
}

// iterates through the roads[] array and adds an edge for every item
void addEdges(struct intertown_distance* roads[1024], int adjacency[MAX][MAX]){
    int i;
    for(i = 0; i < numberOfRoads; i++){
        // adds 40 edges, 40 being the number of roads currently in the roads array
        addEdge(adjacency, getNodeValue(getStartLocation(roads[i])),getNodeValue(getEndLocation(roads[i])),
    findDistanceBetween(roads, getNodeValue(getStartLocation(roads[i])),getNodeValue(getEndLocation(roads[i]))));
    }
}

// function that takes the arguments of the node value of two cities, and finds the distance between them
// iterates through the roads array until it finds the correct distance value, then returns it
int findDistanceBetween(struct intertown_distance* roads[1024], int start, int end){
    int i;
    // loop between 0 to numberOfRoads
    // if the node value of the starting city and end city are the same as the node values passed as arguments of the function:
    // returns the distance between the two nodes
    for (i = 0; i < numberOfRoads; i++){
        if((getNodeValue(getStartLocation(roads[i])) == start) && (getNodeValue(getEndLocation(roads[i])) == end)){
            return getDistanceBetween(roads[i]);
        }
        // the same process in reverse, essentially checking both the start location and end location of the ukcities file
        // this is because the roads are bi-directional, so you have to check all fields
        else if((getNodeValue(getEndLocation(roads[i])) == start) && (getNodeValue(getStartLocation(roads[i])) == end)){
            return getDistanceBetween(roads[i]);
        }
    }
}



// takes a char array as an argument and then appends the char array to the paths file
// adaptation from https://www.programiz.com/c-programming/examples/write-file
void writeToPaths(char route[256]){
    // initialises path as a pointer to a file in append mode
    FILE *path = fopen("paths.txt", "a");
    // pastes the char array into the file
    // fprintf explanation and implementation adapted from https://www.programiz.com/c-programming/examples/write-file
    fprintf(path, "%s", route);
    fclose(path);
}

// empties the paths file
void clearPathsFile(){
    FILE *path = fopen("paths.txt","w");
    fclose(path);
}

// prints the paths file to the console
// code adapted from a StackOverflow comment by 'Alok Singhai'
// https://stackoverflow.com/questions/3463426/in-c-how-should-i-read-a-text-file-and-print-all-strings
printPaths(){
    FILE *path = fopen("paths.txt", "r");
    int text;
    if (path) {
        // iterates through every line printing contents
        // fgetc implementation https://www.tutorialspoint.com/c_standard_library/c_function_fgetc.htm
        while ((text = getc(path)) != -1){
            // prints the text
            // putchar implementation adapted from https://www.tutorialspoint.com/c_standard_library/c_function_putchar.htm
            putchar(text);
        }
    }
    fclose(path);
}

// calculates the shortest path between a given start node and end node
// the path data is then stored in the paths.txt file
// implementation of dijkstras algorithm adapted from
//https://www.thecrazyprogrammer.com/2014/03/dijkstra-algorithm-for-finding-shortest-path-of-a-graph.html
void dijkstra(int graph[MAX][MAX],int vertices,int startnode, int endNode){

    // cost matrix elements are the distances from going from vertex i to vertex j, for cost[i][j]
	int cost[MAX][MAX];

	// distance array which stores the cumulative distances of the path
	int distance[MAX];

    // array to store the previous value of each node
	int prev[MAX];

	// stores the node value of all the vertices that have been visited by the algorithm
	// contains the node value of all visited nodes
	int visited[MAX];

	int count;
	int mindistance;
	int nextnode;
	int i,j;

	// for every edge of adjacency matrix with weight 0 (meaning no direct link) set the distance to infinity
	for( i=0; i < vertices; i++)
		for( j=0; j < vertices; j++)
			if(graph[i][j] == 0)
				cost[i][j] = INFINITY;
			else
                // if there is a weighted edge in the adjacency matrix, copy the value into the cost matrix
				cost[i][j] = graph[i][j];


    // setting the initial value of visited array to 0
	for(i = 0; i < vertices; i++)
	{
		distance[i] = cost[startnode][i];
		prev[i] = startnode;
		visited[i]=0;
	}

	distance[startnode] = 0;
	// visit the start node first, so set that value to 1, meaning visited
	visited[startnode] = 1;

	count = 0;
    // loops between 0 and the number of vertices
	while(count < vertices)
	{
	    // sets the initial minimum distance to infinity
		mindistance=INFINITY;

        // looks for all links that are adjacent to the currentNode
		for(i = 0; i < vertices; i++)
            // if there is a link, set the distance to the link as the new minDistance
			if(distance[i] < mindistance && !visited[i])
			{
				mindistance = distance[i];
				nextnode = i;
			}

            // defining the visited node as visited
			visited[nextnode] = 1;

			// updating the total distance array
			for(i=0; i < vertices; i++)
				if(!visited[i])
					if(mindistance + cost[nextnode][i] < distance[i])
					{
						distance[i] = mindistance + cost[nextnode][i];
						prev[i] = nextnode;
					}
		count++;
	}

    char stringDistance[4];
    // function turns an integer value into a char array
    // implementation adapted from https://www.ibm.com/support/knowledgecenter/en/ssw_ibm_i_73/rtref/snprintf.htm
    snprintf(stringDistance, sizeof(stringDistance), "%d", distance[endNode]);

    // writes text to the paths file
    writeToPaths("Distance between ");
    writeToPaths(getNodeName(startnode));
    writeToPaths(" and ");
    writeToPaths(getNodeName(endNode));
    writeToPaths(" is ");
    writeToPaths(stringDistance);
    writeToPaths("\n Path = ");
    writeToPaths(getNodeName(endNode));

    j = endNode;
    do
    {
        j = prev[j];
        writeToPaths(" <- ");
        writeToPaths(getNodeName(j));

    }while(j != startnode);
    writeToPaths("\n\n");
    // print the entire path to the paths.txt file
}

// function to initiate reading the citypairs text file and executing dijkstras algorithm on all three
void shortestPaths(int adjacency[MAX][MAX], struct city_pairs* citypairs[100]){
    int i;
    int vertices = numberOfRoads;
    // for each element in citypairs, perform dijkstra's algorithm
    for(i = 0; i < getCityPairsSize(citypairs); i++){
        dijkstra(adjacency, vertices, getNodeValue(cityPairsStart(citypairs[i])), getNodeValue(cityPairsEnd(citypairs[i])));
    }
}

// function which loads the global cities array with names of the different cities
// file input from https://www.tutorialspoint.com/cprogramming/c_file_io.htm
void storeCities(){
    // initialising a pointer to the ukcities file in read mode
    FILE *ukcities;
    ukcities = fopen("ukcities.txt","r");

    int numElements = 0;

    char start[256];
    char end[256];

    int distance;
    int i = 0;
    int j = 0;

    // stores each city name from the file in the cities array
    while(fscanf(ukcities,"%s %s %d", start, end, &distance) != -1){
                    if(i == 0){
                strcpy(cities[i], start);
                numElements++;
            }

            for(j = 0; j < numElements; j++){
                    // strcmp compared the string values of two char arrays
                    // if they are the same, return 0
                    // https://www.tutorialspoint.com/c_standard_library/c_function_strcmp.htm
                if(strcmp(start, cities[j])!= 0){
                    strcpy(cities[i], start);
                    // increment the number of elements
                    numElements++;

                }
                else{
                    // break out of the foor loop
                    j = numElements;
                }
            }
        i++;
    }
}

// returns the string name of the node
char *getNodeName(int nodeValue){
    return cities[nodeValue];
}

// returns the node value of a city
int getNodeValue(char city[256]){
    int i;
    for(i = 0; i < 50; i++){
        // stricmp compares char arrays with no regards to case
        // https://www.ibm.com/support/knowledgecenter/en/ssw_ibm_i_71/rtref/stricmp.htm
        if(stricmp(cities[i], city) == 0){
            return i;
        }
    }
}

// sorts the array of intertown_distance structs in ascending order of distance
// adapted from the implementation shown on https://scanftree.com/programs/c/c-program-to-implement-heap-sort/
void heapsort(struct intertown_distance* roads[1024],int vertices) {
	int i;

	// variables to temporarily store the values in the structures
	int tempDistance;
	char tempStart[256];
	char tempEnd[256];

    // a heap needs to be a full binary tree, or a binary tree where the parent nodes are all larger than the children
    // therefore heapify transforms roads into a heap
	heapify(roads, vertices);

	for (i = vertices - 1; i > 0; i--) {
        // copying all values from roads[0] into the three variables
		tempDistance = getDistanceBetween(roads[0]);
		strcpy(tempStart, getStartLocation(roads[0]));
		strcpy(tempEnd, getEndLocation(roads[0]));

		// placing the contents of roads[i] into roads[0]
		roads[0]->distance = getDistanceBetween(roads[i]);
		strcpy(roads[0]->start, getStartLocation(roads[i]));
		strcpy(roads[0]->end, getEndLocation(roads[i]));

        // placing the contents of the temporary variables into roads[i]
		roads[i]->distance = tempDistance;
		strcpy(roads[i]->start, tempStart);
		strcpy(roads[i]->end, tempEnd);

        // turning the binary tree back into a regular array
		adjust(roads,i);
	}
}



// a heap needs to be a full binary tree, or a binary tree where the parent nodes are all larger than the children
// therefore heapify transforms roads into a heap
// adapted from the implementation shown on https://scanftree.com/programs/c/c-program-to-implement-heap-sort/
void heapify(struct intertown_distance* roads[1024],int vertices) {
	int k,i,j;
	// setting temporary variables for the structures
	int tempDistance;
	char tempStart[256], tempEnd[256];

	for (k = 1; k < vertices; k++) {
        // copying the values from roads[k] into the temporary variables
		tempDistance = getDistanceBetween(roads[k]);
		strcpy(tempStart, getStartLocation(roads[k]));
		strcpy(tempEnd, getEndLocation(roads[k]));
		i = k;
		// j is the parent of node i
		j = (i-1) / 2;

		// while the temporarydistance is more than the distance of roads[j]
		while( (i > 0) && (tempDistance > getDistanceBetween(roads[j]))) {
            // copy values from roads[j] into roads[i]
			roads[i]->distance = getDistanceBetween(roads[j]);
			strcpy(roads[i]->start, getStartLocation(roads[j]));
			strcpy(roads[i]->end, getEndLocation(roads[j]));
			i = j;
			// j is the parent of node i
			j = (i-1) / 2;
		}
		// copy values from the temporary varibles into roads[i]
		roads[i]->distance = tempDistance;
		strcpy(roads[i]->start, tempStart);
		strcpy(roads[i]->end, tempEnd);

	}
}

// returns the binary tree into regular array format
// adapted from the implementation shown on https://scanftree.com/programs/c/c-program-to-implement-heap-sort/
void adjust(struct intertown_distance* roads[1024],int vertices) {
	int i,j,tempDistance;
	char tempStart[256], tempEnd[256];
	j = 0;

	tempDistance = getDistanceBetween(roads[j]);
	strcpy(tempStart, getStartLocation(roads[j]));
	strcpy(tempEnd, getEndLocation(roads[j]));

    // i is the left child of node j
	i = 2 * j + 1;
    // while left child is <= edges - 1
	while(i <= vertices-1) {
		if(i + 1 <= vertices-1)
		   if(getDistanceBetween(roads[i]) < getDistanceBetween(roads[i + 1]))
		    i++;
		if(tempDistance < getDistanceBetween(roads[i])) {
            //copy values from roads[i] into roads[j]
			roads[j]->distance = getDistanceBetween(roads[i]);
            strcpy(roads[j]->start, getStartLocation(roads[i]));
            strcpy(roads[j]->end, getEndLocation(roads[i]));
			j = i;
            // i is the left child of node j
			i = 2 * j + 1;
		} else
		   break;
	}
	// lastly copy the values of the temporary variables into roads[j]
	roads[j]->distance = tempDistance;
	strcpy(roads[j]->start, tempStart);
	strcpy(roads[j]->end, tempEnd);
}

/*
    All References:
    https://www.elec.york.ac.uk/internal_web/meng/yr2/modules/Algorithms_and_Numerical_Methods/DSA/Labs/Scripts/Lab2-ComplexNumbers.pdf
    https://www.tutorialspoint.com/c_standard_library/c_function_strcpy.htm
    https://www.tutorialspoint.com/cprogramming/c_return_arrays_from_function.htm
    https://www.tutorialspoint.com/cprogramming/c_file_io.htm
    https://overiq.com/c-programming-101/fscanf-function-in-c/
    https://www.log2base2.com/data-structures/graph/adjacency-matrix-representation-of-graph.html
    https://www.thecrazyprogrammer.com/2014/03/dijkstra-algorithm-for-finding-shortest-path-of-a-graph.html
    https://www.ibm.com/support/knowledgecenter/en/ssw_ibm_i_73/rtref/snprintf.htm
    https://www.tutorialspoint.com/c_standard_library/c_function_fprintf.htm
    https://www.programiz.com/c-programming/examples/write-file
    https://stackoverflow.com/questions/3463426/in-c-how-should-i-read-a-text-file-and-print-all-strings
    https://www.tutorialspoint.com/c_standard_library/c_function_fgetc.htm
    https://www.tutorialspoint.com/c_standard_library/c_function_putchar.htm
    https://www.tutorialspoint.com/c_standard_library/c_function_strcmp.htm
    https://www.ibm.com/support/knowledgecenter/en/ssw_ibm_i_71/rtref/stricmp.htm
    https://scanftree.com/programs/c/c-program-to-implement-heap-sort/
*/






