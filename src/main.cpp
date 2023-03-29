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

int main(int argc, char *argv[]){
    // instantiate argparser object
    ArgParser ap(argc, argv);

    // set default options
    std::string file_name = "data/test_data.txt"; // file
    int vstart = 2; // start node
    int vend = 500; // end node
    std::string algorithm = "none"; // algorithm used
    bool print_vertices = false, print_edges = false, save_to_file = false, load_display_debug = false;

    // ignore other args if display is present
    if(ap.cmdOptionExists("--display")) {
        std::cout<<"Display module properly linked."<<std::endl;
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
    
    if(ap.cmdOptionExists("--vertices")) {
        print_vertices = true;
    }

    if(ap.cmdOptionExists("--edges")) {
        print_edges = true;
    }

    if(ap.cmdOptionExists("--save")) {
        save_to_file = true;
    }

    if(ap.cmdOptionExists("--display-debug")){
        load_display_debug = true;
    }

    // resume main execution path
    file_name = file_name.c_str();
    Graph g = Graph(file_name);

    // TODO: more algos
    if(algorithm == "bfs") {
        g.bfs(vstart, vend);
    } else if(algorithm == "dijkstra") {
        g.dijkstra(vstart, vend);
    } else if(algorithm == "astar"){
        g.astar(vstart, vend);
    }
    else {
        cout << "Not running a search algorithm." << endl;
    }

    if(print_vertices) {
        g.print_verteces();
    }

    if(print_edges) {
        g.print_edges();
    }
}