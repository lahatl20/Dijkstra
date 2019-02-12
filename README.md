# Dijkstra

- Project Name: Dijkstra's Algorithm

- Project Summary: A client file is implemented using the operations of the Graph class to produce a summary table of the shortest
paths from a vertex using Dijkstra's Algorithm. (Optional: Check for any cycles that may exist in the graph and print out a 
cyclic path if there is one)

- Input File and User Input: 
	1. The input file is provided in the command line. Flag an incorrect command line input or an invalid file name
and exit. The input file contains two or more different route possibilities. Each line of input will be in the following format:
Origin;Destination;Trip-Length. 
Assume the origin and destination cities are strings of maximum length 30 which are delimited by a semicolon. Trip-Length is an 
integer representing the weight of the edge between the two cities.
	2. The user will be inputting the starting vertex at the keyboard. If they enter the name of a vertex which is not
available, inform them, and allow them to re-enter the value.

- Dijkstra's Algorithm:
	1. Determine how many vertices have been input. Assign this to an integer
	2. Declare and initialize a structure that can support each of the following components. You could use a series of four
parallel arrays or a single array of structs:
		A. The string representing the different vertices
		B. The booleans to "mark" a vertex once the weight of a vertex has been chosen as the smallest among the current
unmarked ones; All values in this array should start out as false
		C. The integers representing the total distance used in reaching this vertex. All values in this array should 
probably start out with a value like INT_MAX, so they will not be considered among the current smallest of those already 
initialized
		D. String representing the previous vertex visited beofre reaching a vertex
	3. Determine the index within the local container of vertices where the starting vertex is located. Mark it as visited
and flush its distance to 0. Print out the data corresponding to this index with "N/A" used as the previous vertex
	4. Determine the vertices which are adjacent to the current vertex using the GetToVertices operation
	5. For each vertex that is adjacent to the  current vertex, determine the weight value that exists between each one and
the current vertex. If an adjacent vertex is currently unmarked and its distance value in the table is greater than the sum of
the weight value plus the distance of the last marked vertex (the current vertex), reset its distance value to this smaller sum.
Store the name of the current vertex as the previous vertex of each adjacent vertex.
	6. Find the minimum distance value among all unmarked vertices, and set the vertex that corresponds to this minimum
distance as the new current vertex. Mark this vertex
	7. Print out the data corresponding to the current marked vertex
	8. Repeat the previous four steps above until all of the vertices have been marked

- Classes:
	1. Graph Class: Builds a graph that implements dijkstra's algorithm. Builds graph using the HashTable  class
	2. LinkedList Class: Builds a linked list of objects
	3. HashTable Class: Builds a hash table of linked lists using the LinkedList class
	4. Queue Class: Builds a queus of graph objects usng the Graph class as the graph is being printed
