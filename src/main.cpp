#include <iostream>
#include "headers/graph.hpp"

int main(int argc, char *argv[]){
    Graph g = Graph(argv[1]);
    //g.print_verteces();
    g.bfs(86771, 110636);

    // g.print_edges();
    g.summary();
}