#ifndef DISPLAY_H
#define DISPLAY_H

#include "graph.hpp"

void displayMessage(const char* message);
std::vector<double, double> transformToMercator(std::vector<Vertex> vertices);

#endif // DISPLAY_H