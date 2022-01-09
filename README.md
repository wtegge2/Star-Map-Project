
## File Description

Below is a list of all the functions/files and a description of what they do:

● dijkstra : Implementation of Dijkstra’s Algorithm to find the shortest path between two
stars.

● draw_map : The draw_map file outputs our map to several svg files.

● kruskal : Implementation of Kruskal’s Algorithm. Also included are methods to help with
disjoint sets, such as addElements(), find(), and compare().

● star_list : The implementation of a list of Stars. Some methods include, insertStar(Star
star) and insertNeighbor(std::string s1, std::string s2) to allow for the list to function. The
traversals we used in this project utilize the star_list to perform.

● stars : This is the basic class that represents a Star object and its member variables
such as a list of Neighbors as information such as its location and name. It also
contains the struct for Neighbors.

● traversals : Implementation of a breadth first search traversal to traverse through the
whole graph.

● test_main.cpp : This file contains the tests we created to make sure that our code is
running properly.


## Building and Running

In order to run main.cpp, cd into the src folder and then run `./stars`.

In order to run test_main.cpp, cd into the src folder and run `./test`.

To run the test cases I made, cd into the src folder. Then run `make test` first followed by
`./test`.

To use the code, go into the main.cpp file and use the various functions to implement and edit
the star map. For example, you can use methods like insertStar() to add a star to the list of
stars or insertNeighbor() to add a star at a certain place in the graph.

Hope you enjoy making your own star map!







