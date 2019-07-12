


// this data structure is used to represent roads that connect two cities
struct intertown_distance;

// structure to represent a pair of cities to find the shortest path between
struct city_pairs;

// global array of strings to represent all the different city names in the graph
// only used to convert from node value to node name
// for example before being heapsorted, "York" has a node value of 0, because cities[0] is = "York"
char cities[100][256];

// this function generates a road, with a start, end, and a distance from one to the other
// implementation of the constructors adapted from Lab 2
// https://www.elec.york.ac.uk/internal_web/meng/yr2/modules/Algorithms_and_Numerical_Methods/DSA/Labs/Scripts/Lab2-ComplexNumbers.pdf
struct intertown_distance* intertownDistanceConstructor(char start[256], char end[256], int distance);

// implementation of the destructors adapted from Lab 2
// https://www.elec.york.ac.uk/internal_web/meng/yr2/modules/Algorithms_and_Numerical_Methods/DSA/Labs/Scripts/Lab2-ComplexNumbers.pdf
void intertownDistanceDestructor(struct intertown_distance* intertown_distance);

// function to free all memory associated with every structure in the array of structs
void destroyRoads(struct intertown_distance* roads[1024]);

// function which creates the nodes to find the shortest path between
// implementation of the constructors adapted from Lab 2
// https://www.elec.york.ac.uk/internal_web/meng/yr2/modules/Algorithms_and_Numerical_Methods/DSA/Labs/Scripts/Lab2-ComplexNumbers.pdf
struct city_pairs* cityPairsConstructor(char start[256], char end[256]);

// frees all memory associated with the structure passed as the argument
// implementation of the destructors adapted from Lab 2
// https://www.elec.york.ac.uk/internal_web/meng/yr2/modules/Algorithms_and_Numerical_Methods/DSA/Labs/Scripts/Lab2-ComplexNumbers.pdf
void cityPairsDestructor(struct city_pairs* citypairs);

// destroy all memory associated with every structure in the array of structures
void destroyCityPairs(struct city_pairs* citypairs[100]);


// this function returns the length of the road
int getDistanceBetween(struct intertown_distance* intertown_distance);


// this function returns the endpoint of the road
// the explanation and implementation of returning char arrays can be found on tutorialspoint
// https://www.tutorialspoint.com/cprogramming/c_return_arrays_from_function.htm
char *getEndLocation(struct intertown_distance* intertown_distance);

// this function returns the start of the road
// the explanation and implementation of returning char arrays can be found on tutorialspoint
// https://www.tutorialspoint.com/cprogramming/c_return_arrays_from_function.htm
char *getStartLocation(struct intertown_distance* intertown_distance);

// return the starting node to be used for the shortest path algorithm
char *cityPairsStart(struct city_pairs* citypairs);

// return the end node to be used for the shortest path algorithm
char *cityPairsEnd(struct city_pairs* citypairs);

// scans through the ukcities.txt file, storing contents into the array of intertown_distance structures
// this code was adapted for my purposes from tutorialspoint
// https://www.tutorialspoint.com/cprogramming/c_file_io.htm
// storing information from the text file implementation found at overiq.com
// https://overiq.com/c-programming-101/fscanf-function-in-c/
void storeRoads(struct intertown_distance* roads[1024]);

// function to pass the value of the global variable numberOfRoads into the main function
int getRoadsSize(struct intertown_distance* roads[1024]);

// scans through the citypairs.txt file, storing contents into the array of citypairs structures
// this code was adapted for my purposes from tutorialspoint
// https://www.tutorialspoint.com/cprogramming/c_file_io.htm
// storing information from the text file implementation found at overiq.com
// https://overiq.com/c-programming-101/fscanf-function-in-c/
void storeCityPairs(struct city_pairs* citypairs[3]);

// returns the number of paths
int getCityPairsSize(struct city_pairs* citypairs[100]);

// initialising the adjacency matrix, setting all edge weights to 0 initially
// this is done because 0 implies no edge between vertices on the graph, therefore when adding edges,
// theres no need to worry about adding edges of weight 0 for every other node
// implementation from https://www.log2base2.com/data-structures/graph/adjacency-matrix-representation-of-graph.html
void initialiseGraph(int cost[MAX][MAX]);

// used for testing to see if the adjacency matrix has been initialised and updated correctly
// iterates through the matrix printing all elements
// implementation adapted from https://www.log2base2.com/data-structures/graph/adjacency-matrix-representation-of-graph.html
void printGraph(int adjacency[MAX][MAX]);

// adding weighted edges to the adjacency matrix
// adapted implementation from https://www.log2base2.com/data-structures/graph/adjacency-matrix-representation-of-graph.html
// this function takes the arguments of the node values of the cities
// eg the node value of York would be 0, Leeds would be 1, etc, depending on when they first appear in the ukcities text file
void addEdge(int adjacency[MAX][MAX], int source, int destination, int distance);

// iterates through the roads[] array and adds an edge for every item
void addEdges(struct intertown_distance* roads[1024], int adjacency[MAX][MAX]);

// function that takes the arguments of the node value of two cities, and finds the distance between them
// iterates through the roads array until it finds the correct distance value, then returns it
int findDistanceBetween(struct intertown_distance* roads[1024], int start, int end);

// takes a char array as an argument and then appends the char array to the paths file
// adaptation from https://www.programiz.com/c-programming/examples/write-file
void writeToPaths(char route[256]);

// empties the paths file
void clearPathsFile();

// prints the paths file to the console
// code adapted from a StackOverflow comment by 'Alok Singhai'
// https://stackoverflow.com/questions/3463426/in-c-how-should-i-read-a-text-file-and-print-all-strings
void printPaths();

// calculates the shortest path between a given start node and end node
// the path data is then stored in the paths.txt file
// implementation of dijkstras algorithm adapted from
//https://www.thecrazyprogrammer.com/2014/03/dijkstra-algorithm-for-finding-shortest-path-of-a-graph.html
void dijkstra(int G[MAX][MAX],int n,int startnode, int endNode);

// function to initiate reading the citypairs text file and executing dijkstras algorithm on all three
void shortestPaths(int adjacency[MAX][MAX], struct city_pairs* citypairs[100]);

// function which loads the global cities array with names of the different cities
// file input from https://www.tutorialspoint.com/cprogramming/c_file_io.htm
void storeCities();

// returns the string name of the node
char *getNodeName(int nodeValue);

// returns the node value of a city
int getNodeValue(char city[256]);

// sorts the array of intertown_distance structs in ascending order of distance
// adapted from the implementation shown on https://scanftree.com/programs/c/c-program-to-implement-heap-sort/
void heapsort(struct intertown_distance* roads[1024],int vertices);

// a heap needs to be a full binary tree, or a binary tree where the parent nodes are all larger than the children
// therefore heapify transforms roads into a heap
// adapted from the implementation shown on https://scanftree.com/programs/c/c-program-to-implement-heap-sort/
void heapify(struct intertown_distance* roads[1024],int vertices);

// returns the binary tree into regular array format
// adapted from the implementation shown on https://scanftree.com/programs/c/c-program-to-implement-heap-sort/
void adjust(struct intertown_distance* roads[1024],int vertices);

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









