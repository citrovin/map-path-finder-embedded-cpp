#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

class Vertex{
    public:
        int id_;
        double longitude_;
        double lattitude_;

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
                << "\n";
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


class AdjacencyElement{
    public:
        Vertex v_;
        vector<int> adjacent_elements_;

        AdjacencyElement(Vertex v, vector<int> adjacent_elements){
            v_=v;
            adjacent_elements_=adjacent_elements;
        }
        AdjacencyElement(){};

        void const print_adjacent_elements(){
            cout << "Source Node: "<< v_.id_
            << "\t | Destination Nodes: {";
            for(int i : adjacent_elements_){
                cout << i << " ";
            }
            cout << "}\n";
        }
};


class Graph{
    private:
        vector<Vertex> verteces_;
        vector<Edge> edges_;
        

    public:
    unordered_map<int, AdjacencyElement> adjacent_list_;

    Graph(vector<Vertex> verteces, vector<Edge> edges){
        verteces_ = verteces;
        edges_ = edges;

        // create adjaceny list
        for(Edge e : edges){
            if(auto it = adjacent_list_.find(e.source_vid_); it!=adjacent_list_.end()){
                // if node is already in the list, insert the destination node to adjacency list of corresponding node
                it->second.adjacent_elements_.emplace_back(e.dest_vid_);
                
            }else{
                // if node is not yet in the list, create new entry
                vector<int> dest_nodes {e.dest_vid_};
                AdjacencyElement adjacent;
                
                for(Vertex v : verteces){
                    if(v.id_==e.source_vid_){
                        adjacent = AdjacencyElement(v, dest_nodes);
                    }
                }

                adjacent_list_.insert({e.source_vid_, adjacent});
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

    void const print_adjacent_list(){
        cout << "\nAdjacent list: \n"
        << "---------------------------------------------------------" << endl;
        for(auto it : adjacent_list_){
            it.second.print_adjacent_elements();
        }
        cout << "---------------------------------------------------------" << endl;
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