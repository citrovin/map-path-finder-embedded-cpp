#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <string>
#include <vector>
#include <set>
#include <queue>
#include <map>

using namespace std; //to be removed in the end

class Vertex{ //change to protected and use fucntions to access
    public:
        Vertex(){};
        Vertex(int id, double longitude, double latitude){
            id_ = id;
            longitude_ = longitude;
            latitude_ = latitude;
        }

        int getId() const { return id_; }
        double getLongitude() const { return longitude_; }
        double getLatitude() const { return latitude_; }
        const vector<int>& getAdjacencyList() const { return adjacency_list_; }

        void setId(int id) { id_ = id; }
        void setLongitude(double longitude) { longitude_ = longitude; }
        void setLatitude(double latitude) { latitude_ = latitude; }

        void const print_vertex(){
            
            cout    << "| ID: " << id_ 
                    << "\t| Long.: " << longitude_ 
                    << "\t| Lat.: " << latitude_
                    << "\t| Adjacency list: {";

            for(int i : adjacency_list_){
                cout << i << " ";
            }

            cout << "}" << endl;
        }
    protected:
        int id_;
        double longitude_;
        double latitude_;
        vector<int> adjacency_list_;
};

class Edge{
    public:
        Edge(int source_vid, int dest_vid, double length, string name){
            source_vid_ =source_vid;
            dest_vid_ = dest_vid;
            length_ = length;
            name_ = name;
        }

        int getSourceVid() const {
            return source_vid_;
        }

        int getDestVid() const {
            return dest_vid_;
        }

        double getLength() const {
            return length_;
        }

        string getName() const {
            return name_;
        }

        void setSourceVid(int source_vid){
            source_vid_ = source_vid;
        }

        void setDestVid(int dest_vid){
            dest_vid_ = dest_vid;
        }

        void setLength(double length){
            length_ = length;
        }

        void setName(string name){
            name_ = name;
        }

        void const print_edge(){
            cout    << "| Source ID: " << source_vid_ 
                    << "\t| Destination ID: " << dest_vid_
                    << "\t| Length: " << length_
                    << "\t| Name: " << name_
                    << "\n";
        }
        
    protected:
        int source_vid_;
        int dest_vid_;
        double length_;
        string name_;
};


class Graph{
    private:
        //vector<Vertex> verteces_;
        vector<Edge> edges_; //do we need this?
        map<int, Vertex> mapping_; //we can switch to unordered

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

                Vertex vertex = Vertex(id, longitude, lattitude);
                mapping_.emplace(id, vertex);     //or insert?
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

                mapping_[source_vid].adjacency_list_.emplace_back(dest_vid);
            }
            
            
        }

    }

    // vertices in the graph
    vector<Vertex> getVertices() const {
        vector<Vertex> vertices;
        for (const auto& p : mapping_) {
            vertices.push_back(p.second);
        }
        return vertices;
    }

    // adjacency list of a vertex given its ID
    vector<int> getAdjacencyList(int id) const {
        auto it = mapping_.find(id);
        if (it != mapping_.end()) {
            return it->second.adjacency_list_;
        }
        throw invalid_argument("Vertex not found");
    }

/*
    //previous version
    void bfs(uint32_t vstart) 
    {
        deque<uint32_t> active_queue; //maybe deque better?
        set<uint32_t> closed_set;
        vector<uint32_t> predecessor(mapping_.size(), -1);

        // ID of the start vertex
        active_queue.push_back(vstart);

        do {
            // from the current vertex in the front of the queue
            // compute all vertices reachable in 1 step
            uint32_t vcurrent = active_queue.front();
            active_queue.pop_front();

            closed_set.insert(vcurrent);
            for (auto& vnext : mapping_[vcurrent].adjacency_list_) {

                if (closed_set.find(vnext) != closed_set.end()){
                    continue;
                }
                   
                if (find(active_queue.begin(), active_queue.end(), vnext) == active_queue.end()) {
                    active_queue.push_back(vnext);
                }
            }
        } while (active_queue.size() != 0);

        //printing result ...
        cout << "\nPRINTING BFS..\n";
        for (const auto& el : closed_set) {
            auto ver = mapping_[el];
            ver.print_vertex();
        }
    }

*/
void bfs(uint32_t vstart, uint32_t vend) 
{
    deque<uint32_t> active_queue; //maybe deque better?
    set<uint32_t> closed_set;
    
    uint32_t vertex_count = 0;

    // ID of the start vertex
    active_queue.push_back(vstart);

    while (!active_queue.empty()) {
        // from the current vertex in the front of the queue
        // compute all vertices reachable in 1 step
        uint32_t vcurrent = active_queue.front();
        active_queue.pop_front();

        closed_set.insert(vcurrent);
        vertex_count++;

        if (vcurrent == vend) {
            break;
        }

        for (auto& vnext : mapping_[vcurrent].adjacency_list_) {

            if (closed_set.find(vnext) != closed_set.end()){
                continue;
            }
               
            if (find(active_queue.begin(), active_queue.end(), vnext) == active_queue.end()) {
                active_queue.push_back(vnext);
            }
        }
    }

    //printing result ...
    cout << "\nPRINTING BFS..\n";
    for (const auto& el : closed_set) {
        auto ver = mapping_[el];
        ver.print_vertex();
    }

    cout << "Number of vertices visited: " << vertex_count << endl;
}

    void const summary(){
        cout << "\nSummary of Graph:\n"
            << "--------------\n" 
            << "# Nodes: " << mapping_.size() << "\n"
            << "# Edges: " << edges_.size() << "\n"
            << "--------------\n";
    }

    void const print_verteces(){
        cout  << "Nodes\n" 
        << "---------------------------------------------------------\n";
        for (const auto& pair : mapping_) {
            auto ver = pair.second;
            ver.print_vertex();
        }
        cout << "---------------------------------------------------------\n"
        << "Number of Verteces: " << mapping_.size() << endl;
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