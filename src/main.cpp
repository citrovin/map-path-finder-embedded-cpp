#include <iostream>
#include <fstream>
#include <sstream>

#include "headers/graph.hpp"

int main(int argc, char *argv[]){
    ifstream file_stream;
    string file_name{argv[1]};

    file_stream.open(file_name, ios::in);
    string line;

    vector<Vertex> nodes;
    vector<Edge> edges;

    while (getline(file_stream, line)) {
        if(line[0]=='#') continue;
        std::istringstream stream(line);

        char type='#';
        int id=-1;

        if(line[0]=='V'){
            // load vertices (nodes)
            double longitude;
            double lattitude;
            
            line.erase(0, line.find(',')+1);

            id = stoi(line.substr(0, line.find(',')));
            line.erase(0, line.find(',')+1);

            longitude = stod(line.substr(0, line.find(',')));
            line.erase(0, line.find(',')+1);

            lattitude = stod(line.substr(0, line.find(',')));
            line.erase(0, line.find(',')+1);

            nodes.emplace_back(Vertex(id, longitude, lattitude));
        }

        
        if(line[0]=='E'){
            // load edges
            string name;
            int source_vid;
            int dest_vid;
            double length;

            line.erase(0, line.find(',')+1);

            source_vid = stoi(line.substr(0, line.find(',')));
            line.erase(0, line.find(',')+1);

            dest_vid = stoi(line.substr(0, line.find(',')));
            line.erase(0, line.find(',')+1);

            length = stod(line.substr(0, line.find(',')));
            line.erase(0, line.find(',')+1);

            name = line.substr(0, line.find(','));
            line.erase(0, line.find(',')+1);

            edges.emplace_back(Edge(source_vid, dest_vid, length, name));
        }
        
        
    }

    Graph g = Graph(nodes, edges);

    // g.print_verteces();
    // g.print_edges();

    g.print_adjacent_list();
    // g.summary();
    
}