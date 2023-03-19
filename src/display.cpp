#include <iostream>

#include "headers/display.h"

void displayMessage(const char* message) {
    std::cout << message << std::endl;
}

Graph loadGraph(std::string filename) {
    Graph g = Graph();
    g.loadFromFileForDisplay(filename);
    return g;
}