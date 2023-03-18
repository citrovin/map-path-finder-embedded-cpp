/*
The main reads a file and constructs a grpah from it. Using different search algorithms,
you can compute the shortest path between verteces, by passing the corresponding arguments.

Arguments:
    --file data file path
    --start staring vertex of the search algorithm
    --end ending vertex of the search algorithm
    --algorithm algorithm used for search the graph

*/


#include <iostream>
#include <string>
#include <algorithm>

#include "headers/graph.hpp"

// ---- arg parsing --------
#include "headers/argparser.h"
// -------------------------
// ---- DISPLAY MODULE -----
#include "headers/display.h"
// -------------------------

int main(int argc, char *argv[]){
    // instantiate argparser object
    ArgParser ap(argc, argv);

    // set default options
    std::string file_name = "data/test_data.txt"; // file
    int vstart = 1; // start node
    int vend = 100; // end node
    std::string algorithm = "bfs"; // algorithm used

    // ignore other args if display is present
    if(ap.cmdOptionExists("--display")) {
        displayMessage("Display module properly linked.\n");

        return 0;
    }

    // print help and exit
    if(ap.cmdOptionExists("--help") || ap.cmdOptionExists("-h")) {
        std::cout << "4 arguments may be passed with following options: \n" 
                << "\t--filename specifies the data file. DEFAULT = 'data/test_data.txt'\n"
                << "\t--start defines the starting node. DEFAULT = '1'\n"
                << "\t--end defines the ending node. DEFAULT = '5'\n"
                << "\t--algorithm defines the preferred search algorithm. DEFAULT = 'bfs'" 
                << std::endl;
        
        return 0;
    }

    // check defined arg options
    if(ap.cmdOptionExists("--file")) {
        file_name = ap.getCmdOption("--file");
    }

    if(ap.cmdOptionExists("--start")) {
        vstart = stoi(ap.getCmdOption("--start"));
    }

    if(ap.cmdOptionExists("--end")) {
        vend = stoi(ap.getCmdOption("--end"));
    }

    if(ap.cmdOptionExists("--algorithm")) {
        algorithm = ap.getCmdOption("--algorithm");
    }

    // resume main execution path
    file_name = file_name.c_str();
    Graph g = Graph(file_name);

    // TODO: more algos
    if(algorithm == "bfs") {
        g.bfs(vstart, vend);
    }

    // g.print_verteces();
    // g.print_edges();
    // g.summary();
}