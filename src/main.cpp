#include <iostream>
#include "headers/graph.hpp"

int main(int argc, char *argv[]){
    Graph g = Graph(argv[1]);

    // g.print_verteces();
    // g.print_edges();

    // g.print_adjacent_list();
    g.summary();
}