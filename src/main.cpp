#include <iostream>
#include <fstream>
#include <sstream>
#include "headers/graph.hpp"

int main(int argc, char *argv[]){
    string file_name{argv[1]};

    Graph g = Graph(file_name);

    // g.print_verteces();
    // g.print_edges();

    // g.print_adjacent_list();
    g.summary();
}