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

// ---- DISPLAY MODULE -----
#include "display/display.h"
// -------------------------

char* getCmdOption(char ** begin, char ** end, const std::string & option);
bool cmdOptionExists(char** begin, char** end, const std::string& option);


int main(int argc, char *argv[]){
    // ignore other args if display is present
    if(cmdOptionExists(argv, argv+argc, "--display")) {
        displayMessage("Display module properly linked.\n");

        return 0;
    }

    // TODO: modify arg parsing structure to allow mixing and matching arguments i.e. also display at the end if parameter is present
    // TODO: better arg parsing
    // TODO: set default pre-runtime args for fast debugging
    if(cmdOptionExists(argv, argv+argc, "--file") && 
        cmdOptionExists(argv, argv+argc, "--start") &&
        cmdOptionExists(argv, argv+argc, "--end") &&
        cmdOptionExists(argv, argv+argc, "--algorithm")
    ) {
        string file_name = getCmdOption(argv, argv + argc, "--file");
        try{
            int vstart = stoi(getCmdOption(argv, argv + argc, "--start"));
            int vend = stoi(getCmdOption(argv, argv + argc, "--end"));

            string algorithm = getCmdOption(argv, argv + argc, "--algorithm");

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




char* getCmdOption(char ** begin, char ** end, const std::string & option)
{
    char ** itr = std::find(begin, end, option);
    if (itr != end && ++itr != end)
    {
        return *itr;
    }
    return 0;
}

bool cmdOptionExists(char** begin, char** end, const std::string& option)
{
    return std::find(begin, end, option) != end;
}