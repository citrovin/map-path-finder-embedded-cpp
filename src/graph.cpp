#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class Vertex{
    private:
        int id_;
        double longitude_;
        double lattitude_;

    public:
    Vertex(int id, double longitude, double lattitude){
        id_ = id;
        longitude_ = longitude;
        lattitude_ = lattitude;
    }

    void const print_vertex(){
        cout    << "| ID: " << id_ 
                << "| Long.: " << longitude_ 
                << "| Lat.: " << lattitude_
                << "\n";
    }
};

class Edge{
    private:
        int id_;
        int source_vid_;
        int dest_vid_;
        double length_;
        string name_;

    public:
    Edge(int id, int source_vid, int dest_vid, double length, string name){
        id_ = id;
        source_vid_ =source_vid;
        dest_vid_ = dest_vid;
        length_ = length;
        name_ = name;
    }

    void const print_edge(){
        cout    << "| Source ID: " << source_vid_ 
                << "| Destination ID: " << dest_vid_
                << "| Length: " << length_
                << "| Name: " << name_
                << "\n";
    }
};


class Graph{
    private:
        vector<Vertex> verteces_;
        vector<Edge> edges_;

    public:
    Graph(vector<Vertex> verteces, vector<Edge> edges){
        verteces_ = verteces;
        edges_ = edges;
    }

    void const print_verteces(){
        cout
        << "Nodes:\n" 
        << "-------------------------------------------------------------------------------\n";
        for(Vertex v : verteces_) v.print_vertex();
        cout
        << "-------------------------------------------------------------------------------\n";
    }


    void const print_edges(){
        cout
        << "\nEdges:\n"
        << "-------------------------------------------------------------------------------\n";
        for(Edge e : edges_) e.print_edge();
        cout
        << "-------------------------------------------------------------------------------\n";
    }


        
};

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

            edges.emplace_back(Edge(id, source_vid, dest_vid, length, name));
        }
        
        
    }

    Graph g = Graph(nodes, edges);

    g.print_verteces();
    g.print_edges();
    
}