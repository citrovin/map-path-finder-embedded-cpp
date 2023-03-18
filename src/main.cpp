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

    // ignore other args if display is present
    if(ap.cmdOptionExists("--display")) {
        displayMessage("Display module properly linked.\n");

        return 0;
    }

    // TODO: modify arg parsing structure to allow mixing and matching arguments i.e. also display at the end if parameter is present
    // TODO: better arg parsing
    // TODO: set default pre-runtime args for fast debugging
    if(ap.cmdOptionExists("--file") && 
        ap.cmdOptionExists("--start") &&
        ap.cmdOptionExists("--end") &&
        ap.cmdOptionExists("--algorithm")
    ) {
        string file_name = ap.getCmdOption("--file");
        try{
            int vstart = stoi(ap.getCmdOption("--start"));
            int vend = stoi(ap.getCmdOption("--end"));

            string algorithm = ap.getCmdOption("--algorithm");

            //  create graph and choose search algorithm
            Graph g = Graph(file_name);
            g.bfs(vstart, vend);
            // g.print_verteces();
            // g.print_edges();
            // g.summary();

        }catch (const invalid_argument e) {
            std::cout << "Problem while parsing arguments:" <<std::endl;
            std::cout << e.what() << endl;
            return 0;
        }
        
        

    }else{
        std::cout << "Not enough arguments passed. 4 arguments needed with following mandatory options: \n" 
        << "\t--filename specifies the data file\n"
        << "\t--start defines the starting node\n"
        << "\t--end defines the ending node\n"
        << "\t--algorithm defines the preferred search algorithm" 
        << std::endl;
    }
}