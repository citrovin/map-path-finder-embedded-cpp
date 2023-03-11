#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct Vertex{
    char type_;
    int id_;
    double longitude_;
    double lattitude_;

    Vertex(char type, int id, double longitude, double lattitude){
        type_ = type;
        id_ = id;
        longitude_ = longitude;
        lattitude_ = lattitude;
    }
};

struct Edge{
    char type_;
    int id_;
    int source_vid_;
    int dest_vid_;
    double length_;
    string name_;

    Edge(char type, int id, int source_vid, int dest_vid, double length, string name){
        type_ = type;
        id_ = id;
        source_vid_ =source_vid;
        dest_vid_ = dest_vid;
        length_ = length;
        name_ = name;
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
            
            type = line[0];
            line.erase(0, line.find(',')+1);

            id = stoi(line.substr(0, line.find(',')));
            line.erase(0, line.find(',')+1);

            longitude = stod(line.substr(0, line.find(',')));
            line.erase(0, line.find(',')+1);

            lattitude = stod(line.substr(0, line.find(',')));
            line.erase(0, line.find(',')+1);

            nodes.emplace_back(Vertex(type, id, longitude, lattitude));
        }

        
        if(line[0]=='E'){
            // load edges
            string name;
            int source_vid;
            int dest_vid;
            double length;

            type = line[0];
            line.erase(0, line.find(',')+1);

            source_vid = stoi(line.substr(0, line.find(',')));
            line.erase(0, line.find(',')+1);

            dest_vid = stoi(line.substr(0, line.find(',')));
            line.erase(0, line.find(',')+1);

            length = stod(line.substr(0, line.find(',')));
            line.erase(0, line.find(',')+1);

            name = line.substr(0, line.find(','));
            line.erase(0, line.find(',')+1);

            edges.emplace_back(Edge(type, id, source_vid, dest_vid, length, name));
        }
        
        
    }

    cout << "------------------------------------------------------------------\n";
    for(Vertex ver : nodes){
            cout << "Type: " << ver.type_ 
                            << "| ID: " << ver.id_ 
                            << "| Long.: " << ver.longitude_ 
                            << "| Lat.: " << ver.lattitude_
                            << "\n";
        }

    cout << "------------------------------------------------------------------\n";
    for(Edge edge : edges){
        cout << "Type: " << edge.type_ 
                        << "| Source ID: " << edge.source_vid_ 
                        << "| Destination ID: " << edge.dest_vid_
                        << "| Length: " << edge.length_
                        << "| Name: " << edge.name_
                        << "\n";
    }
    cout << "------------------------------------------------------------------\n";
    
}