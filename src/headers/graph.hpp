#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

class Vertex{
    public:
        int id_;
        double longitude_;
        double lattitude_;
        vector<int> adjacency_list_;

    Vertex(){};
    Vertex(int id, double longitude, double lattitude){
        id_ = id;
        longitude_ = longitude;
        lattitude_ = lattitude;
    }

    void const print_vertex(){
        
        cout    << "| ID: " << id_ 
                << "\t| Long.: " << longitude_ 
                << "\t| Lat.: " << lattitude_
                << "\t| Adjacency list: {";

        for(int i : adjacency_list_){
            cout << i << " ";
        }

        cout << "}" << endl;
    }
};

class Edge{
    public:
        int source_vid_;
        int dest_vid_;
        double length_;
        string name_;

    Edge(int source_vid, int dest_vid, double length, string name){
        source_vid_ =source_vid;
        dest_vid_ = dest_vid;
        length_ = length;
        name_ = name;
    }

    void const print_edge(){
        cout    << "| Source ID: " << source_vid_ 
                << "\t| Destination ID: " << dest_vid_
                << "\t| Length: " << length_
                << "\t| Name: " << name_
                << "\n";
    }
};


class Graph{
    private:
        vector<Vertex> verteces_;
        vector<Edge> edges_;

    public:
    Graph(string file_name){

        ifstream file_stream;
        file_stream.open(file_name, ios::in);
        string line;

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

                verteces_.emplace_back(Vertex(id, longitude, lattitude));
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

                Edge edge = Edge(source_vid, dest_vid, length, name);

                edges_.emplace_back(edge);

                // does not work!!!
                for(Vertex& v : verteces_){
                    if(v.id_==edge.source_vid_){
                        v.adjacency_list_.emplace_back(edge.dest_vid_);
                    }
                }
            }
            
            
        }

    }

    void const summary(){
        cout << "\nSummary of Graph:\n"
            << "--------------\n" 
            << "# Nodes: " << verteces_.size() << "\n"
            << "# Edges: " << edges_.size() << "\n"
            << "--------------\n";
    }

    void const print_verteces(){
        cout
        << "Nodes\n" 
        << "---------------------------------------------------------\n";
        int count=0;
        for(Vertex v : verteces_){
            v.print_vertex();
            count++;
            }
        cout
        << "---------------------------------------------------------\n"
        << "Number of Verteces: " << count << endl;
    }


    void const print_edges(){
        cout
        << "\nEdges\n"
        << "-------------------------------------------------------------------------------------------------\n";
        int count = 0;
        for(Edge e : edges_){
            e.print_edge();
            count++;
        } 
        cout
        << "-------------------------------------------------------------------------------------------------\n"
        << "Number of Edges: " << count << endl;
    }      
};