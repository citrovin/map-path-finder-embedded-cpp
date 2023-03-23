#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <string>
#include <vector>
#include <set>
#include <queue>
#include <iomanip>
#include <map>
#include <cmath>
#include <iomanip>
#include <limits>
#include <cmath>

using namespace std; //to be removed in the end

class Vertex{ //change to protected and use fucntions to access
    public:
        Vertex(){};
        Vertex(int id, double longitude, double latitude){
            id_ = id;
            longitude_ = longitude;
            latitude_ = latitude;
        }

        // constructor for display
        Vertex(int id, double x_, double y_, const std::vector<int>& adjacencyList) 
        : id_(id), x(x_), y(y_), adjacency_list_(adjacencyList) {}

        int getId() const { 
            return id_; 
        }
        double getLongitude() const { 
            return longitude_; 
        }
        double getLatitude() const { 
            return latitude_; 
        }
        double getX() const {
            return x;
        }
        double getY() const {
            return y;
        }
        int getParent() {
            return parent_;
        }
        double getWeight() {
            return weigth_;
        }

        const vector<int>& getAdjacencyList() const { 
            return adjacency_list_; 
        }

        void setId(int id) { 
            id_ = id; 
        }
        void setX(double _x) {
            x = _x;
        }
        void setY(double _y) {
            y = _y;
        }
        void setLongitude(double longitude) { 
            longitude_ = longitude; 
        }
        void setLatitude(double latitude) { 
            latitude_ = latitude; 
        }
        void setParent(int parent) {
            parent_= parent;
        }        
        void setWeight(float weigth) {
            weigth_= weigth;
        }
        void appendAdjacencyList(int i) {
            adjacency_list_.emplace_back(i);
        }

        void const print_vertex(){
            
            cout    << "| ID: " << id_ 
                    << "\t| Long.: " << longitude_ 
                    << "\t| X: " << x
                    << "\t| Lat.: " << latitude_
                    << "\t| Y: " << y
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
        double x;
        double y;
        int parent_; //only used in the cases of path tracing (good idea to have it here or not?)
        double weigth_;
        vector<int> adjacency_list_;
};

class Edge{
    public:
        Edge() : source_vid_(0), dest_vid_(0), length_(0), name_("") {} //default constructor
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
        
        vector<Edge> edges_; //do we need this? - christian says yes -> No use only the mapping!! rember filippo remove this!!
        map<int, Vertex> mapping_; //we can switch to unordered
        map<pair<uint32_t, uint32_t>, Edge> edge_weights;
        
        // earth radius
        int R = 6371009;
        double l0 = 0;

        // compute longitudinal center
        double computeLongitudinalCenter() {
            double sum = 0.0;
            int num = 0;
            for (const auto& vertex : getVertices()) {
                sum += vertex.getLongitude();
                num++;
            }
            return sum / num;
        }

        // compute mercator x
        double computeMercatorX(double longitude) {
            return R * (longitude - l0);
        }

        // compute mercator y
        double computeMercatorY(double latitude) {
            return R * log(tan(M_PI/4 + latitude/2));
        }

        // min and max
        double maxX, maxY, minX, minY;

        // compute min max
        void computeBoundaries() {
            vector<Vertex> v = getVertices();

            // max x
            auto maxXVertexIt = std::max_element(v.begin(), v.end(), 
                [](const Vertex& a, const Vertex& b) { return a.getX() < b.getX(); });
            
            // max y
            auto maxYVertexIt = std::max_element(v.begin(), v.end(), 
                [](const Vertex& a, const Vertex& b) { return a.getY() < b.getY(); });

            // min x
            auto minXVertexIt = std::min_element(v.begin(), v.end(), 
                [](const Vertex& a, const Vertex& b) { return a.getX() < b.getX(); });
            
            // min y
            auto minYVertexIt = std::min_element(v.begin(), v.end(), 
                [](const Vertex& a, const Vertex& b) { return a.getY() < b.getY(); });
            
            maxX = maxXVertexIt -> getX();
            maxY = maxYVertexIt -> getY();
            minX = minXVertexIt -> getX();
            minY = minYVertexIt -> getY();
        }

    public:
    Graph() {
        // load an empty graph for display purposes
    }
    Graph(string file_name){
        ifstream file_stream;
        file_stream.open(file_name, ios::in);
        string line;

        // graph loading
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

                try {
                    length = stod(line.substr(0, line.find(',')));
                }catch(invalid_argument) {
                    //to be converted in mercator!!
                        double lats = (mapping_[source_vid].getLatitude()-mapping_[dest_vid].getLatitude());
                        double longs = (mapping_[source_vid].getLongitude()-mapping_[dest_vid].getLongitude());
                        length = sqrt(lats*lats+longs*longs);
                }
                line.erase(0, line.find(',')+1);

                name = line.substr(0, line.find(','));
                line.erase(0, line.find(',')+1);

                Edge edge(source_vid, dest_vid, length, name);

                edges_.emplace_back(edge);

                mapping_[source_vid].appendAdjacencyList(dest_vid);
                edge_weights.insert(make_pair(make_pair(source_vid, dest_vid),edge));
            }
            
            
        }

        file_stream.close(); // dalim you never closed your file stream :)
    }

    // vertices in the graph
    vector<Vertex> getVertices() const {
        vector<Vertex> vertices;
        for (const auto& p : mapping_) {
            vertices.push_back(p.second);
        }
        return vertices;
    }

    // edges in the graph
    vector<Edge> getEdges() const {
        return edges_;
    }

    // adjacency list of a vertex given its ID
    vector<int> getAdjacencyList(int id) const {
        auto it = mapping_.find(id);
        if (it != mapping_.end()) {
            return it->second.getAdjacencyList();
        }
        throw invalid_argument("Vertex not found");
    }

    // get vertex by id
    Vertex getVertexById(int id) const {
        auto it = mapping_.find(id);
        if (it == mapping_.end()) {
            throw std::runtime_error("Vertex with ID " + std::to_string(id) + " not found.");
        }
        return it->second;
    }

    double getMinX() const {
        return minX;
    }

    double getMinY() const {
        return minY;
    }

    double getMaxX() const {
        return maxX;
    }

    double getMaxY() const {
        return maxY;
    }

    int bfs(uint32_t vstart, uint32_t vend)  //returns 0 in case of values not found
    {
        deque<uint32_t> active_queue;
        set<uint32_t> closed_set;
        
        //checking if both are in the mapping first
        if(mapping_.find(vstart) == mapping_.end() || mapping_.find(vend) == mapping_.end()){
            cout << "Error: values not in the map! " << endl;
            return 0;
        }

        // ID of the start vertex
        active_queue.push_back(vstart);

        while (!active_queue.empty()) {
            // from the current vertex in the front of the queue
            // compute all vertices reachable in 1 step
            uint32_t vcurrent = active_queue.front();
            active_queue.pop_front();

            closed_set.insert(vcurrent);


            if (vcurrent == vend) {
                break;
            }

        for (auto& vnext : mapping_[vcurrent].getAdjacencyList()) {

                if (closed_set.find(vnext) != closed_set.end()){
                    continue;
                }
                
                if (find(active_queue.begin(), active_queue.end(), vnext) == active_queue.end()) {
                    active_queue.push_back(vnext);
                    mapping_[vnext].setParent(vcurrent); // Set parent for vnext (can be overwritten but is fine)
                }
            }
        }
   
        vector<uint32_t> path;
        vector<Edge> edges_crossed;
        uint32_t v = vend;
        while (v != vstart) {       
            int vOld = v;
            path.push_back(v);
            v = mapping_[v].getParent();
            edges_crossed.push_back(edge_weights[make_pair(v,vOld)]);
        }

        path.push_back(vstart);
        reverse(path.begin(), path.end());
        reverse(edges_crossed.begin(), edges_crossed.end());

        cout << "Number of vertices visited: " << closed_set.size() << endl;
        cout << "Number of vertex on path from start to end: " << path.size() << endl;

        // Print out the path
        double total_length = 0;
        for (int i=0; i<path.size(); i++) {
            cout << "Vertex[\t" << i << "] = " << path[i] 
                 << ", length =\t" << total_length << endl;
            total_length += edges_crossed[i].getLength();
        }
        
        cout << endl;
        return 1;
    }

    double getEdgeWeight(uint32_t v1, uint32_t v2){
        return edge_weights[make_pair(v1,v2)].getLength();
    }

    void dijkstra(uint32_t vstart, uint32_t vend) {
        std::deque<uint32_t> active_queue;
        std::set<uint32_t> closed_set;

        for (auto it = mapping_.begin(); it != mapping_.end(); it++)
            {
                it->second.setWeight(std::numeric_limits<double>::max());
            }

        // Set the weight of the start vertex to 0
        mapping_[vstart].setWeight(0);

        active_queue.push_back(vstart);

        do {
            // Get the current vertex from the front of the queue
            auto vcurrent = active_queue.front();
            active_queue.pop_front();

            // Stop if we have reached the end vertex
            if (vcurrent == vend) {
                break;
            }

            // Add the current vertex to the closed set
            closed_set.insert(vcurrent);

            // For each neighbor of the current vertex
            for (auto vnext : mapping_[vcurrent].getAdjacencyList()) {
                // Skip if the neighbor is already in the closed set
                if (closed_set.find(vnext) != closed_set.end()) {
                    continue;
                }

                // Calculate the weight of the neighbor
                auto w = mapping_[vcurrent].getWeight() + getEdgeWeight(vcurrent, vnext);

                // If the neighbor is not in the active queue, add it
                if (std::find(active_queue.begin(), active_queue.end(), vnext) == active_queue.end()) {
                    mapping_[vnext].setWeight(w);
                    mapping_[vnext].setParent(vcurrent);
                    active_queue.push_back(vnext);
                }
                // If the weight of the neighbor is less than the current weight, update it
                else if (w < mapping_[vnext].getWeight()) {
                    mapping_[vnext].setWeight(w);
                    mapping_[vnext].setParent(vcurrent);
                }
            }

            // Sort the active queue based on the weights of the vertices
            std::sort(active_queue.begin(), active_queue.end(),
                [&](uint32_t v1, uint32_t v2) { return mapping_[v1].getWeight() < mapping_[v2].getWeight(); });
        } while (!active_queue.empty());

        vector<uint32_t> path;
        vector<Edge> edges_crossed;
        uint32_t v = vend;
        while (v != vstart) {       
            int vOld = v;
            path.push_back(v);
            v = mapping_[v].getParent();
            edges_crossed.push_back(edge_weights[make_pair(v,vOld)]);
        }

        path.push_back(vstart);
        reverse(path.begin(), path.end());
        reverse(edges_crossed.begin(), edges_crossed.end());

        cout << "Number of vertices visited: " << closed_set.size() << endl;
        cout << "Number of vertex on path from start to end: " << path.size() << endl;

        // Print out the path
        double total_length = 0;
        for (int i=0; i<path.size(); i++) {
            cout << "Vertex[\t" << i << "] = " << path[i] 
                 << ", length =\t" << total_length << endl;
            total_length += edges_crossed[i].getLength();
        }
        
        cout << endl;
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
            return it->second.getAdjacencyList();
        }
        throw invalid_argument("Vertex not found");
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
        << "Number of Verteces: " << mapping_.size() << " MinX: " << getMinX() << " MinY: " << getMinY() << " MaxX: " << getMaxX() << " MaxY: " << getMaxY() << endl;
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

    void saveToFileForDisplay(const std::string& filename) const {
        std::ofstream outfile(filename);

        // identify as VERTEX
        outfile << "V" << endl;
        // write each vertex to the file
        for (const auto& vertex : getVertices()) {
            outfile << vertex.getId() << std::setprecision(std::numeric_limits<double>::max_digits10) << "," << vertex.getX() << "," << vertex.getY() << " ";

            // write the adjacency list
            std::vector<int> v = vertex.getAdjacencyList();
            for (int i = 0; i < v.size(); i++) {
                // write the current element to file
                outfile << v[i];

                // if not last write a comma
                if (i != v.size() - 1) {
                    outfile << ",";
                }
            }

            outfile << std::endl;
        }

        // identify as EDGE
        outfile << "E" << endl;
        // write each edge
        for (const auto& edge : getEdges()) {
            outfile << edge.getSourceVid() << ","
                    << edge.getDestVid() << ","
                    << edge.getLength() << ","
                    << edge.getName() << endl;
        }

        outfile.close();
    }

    void loadFromFileForDisplay(const std::string& filename) {
        std::ifstream infile(filename);
        if (!infile.is_open()) {
            std::cerr << "Failed to open file " << filename << std::endl;
            return;
        } else {
            std::cout << "File opened successfully." << std::endl;
            infile.sync();
        }

        std::string line;
        bool loadingVertices = false;
        bool loadingEdges = false;

        while (std::getline(infile, line)) {
            std::stringstream ss(line);
            if (line[0] == 'V') {
                std::cout<<"FOUND V: " << line << endl;
                loadingVertices = true;
                loadingEdges = false;
                continue;
            }
            // check if we are starting to load edges
            else if (line[0] == 'E') {
                std::cout<<"FOUND E: " << line << endl;
                loadingVertices = false;
                loadingEdges = true;
                continue;
            }

            // load vertices
            if (loadingVertices) {
                int id;
                double x,y;
                std::vector<int> adjList;

                std::vector<std::string> values;
                std::string item;
                while (std::getline(ss, item, ',')) {
                    values.push_back(item);
                }

                // for (auto& value : values) {
                //     cout << value << " ";
                // }

                try {
                    id = stoi(values[0]);
                } catch(std::exception e) {
                    cout<<"Error at id"<<endl;
                    cout << "id: " << id << endl;
                }
                x = stod(values[1]);
                // cout << "x: " << setprecision(std::numeric_limits<double>::max_digits10) << x << endl;
                y = stod(values[2]);
                // cout << "y: " << setprecision(std::numeric_limits<double>::max_digits10) << y << endl;

                values.erase(values.begin(), values.begin() +3);

                for (auto& value : values) {
                    try {
                        adjList.emplace_back(stoi(value));
                    } catch(std::exception e) {
                        cout<<"Error at adjlist"<<endl;
                        cout << "adjListId: " << value;

                    }
                }

                // std::cout << "id: " << id << " x: " << x << " y: " << y << " adj nr.: " << adjList.size() << " line: " << line << endl;
                // Create a new vertex and add it to the graph
                addVertex(Vertex(id, x, y, adjList));
            }
            // Load edges
            else if (loadingEdges) {
                std::istringstream iss(line);
                int sourceVid, destVid, length;
                std::string name;

                // Read the source vertex id, destination vertex id, length, and name
                std::getline(iss, name, ',');
                iss >> sourceVid >> destVid >> length >> name;

                // Create a new edge and add it to the graph
                addEdge(Edge(sourceVid, destVid, length, name));
            }
        }

        computeBoundaries();

        std::cout<<"File parsed."<<std::endl;
        infile.close();
    }

    void addVertex(Vertex v) {
        mapping_.emplace(v.getId(),v);
    }

    void addEdge(Edge e) {
        edges_.emplace_back(e);
    }

    // compute only when needed
    void computeMercator() {
        // mercator
        l0 = computeLongitudinalCenter();

        for (auto& m : mapping_) {
            m.second.setX(computeMercatorX(m.second.getLongitude()));
            m.second.setY(computeMercatorY(m.second.getLatitude()));
        }

        // compute min max
        computeBoundaries();
    }
};

#endif // GRAPH_HPP