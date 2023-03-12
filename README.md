# Map Path Finder

## Instatiating the Graph using the Boost Graph Library (BGL)
Properties of our Graph:
- directed graph
- Verteces (nodes) have following attributes: ID (int), Longitude (double), Lattitude (double)
- Arcs (edges) have the following attributes: source ID (int), destination ID (int), length (double), name (string)

### BGL

Instantiating the Graph:
```
typedef adjacency_list<vecS, vecS, bidirectionalS> Graph;
```

- ```vecS```: vector as a datatype for the out-edges and the set of verteces (nodes)

- ```bidirectionalS```: defines, that the graph is bidirectional (other options: ```undirectedS```, ```directedS```)

Documentation of the BGL: https://www.boost.org/doc/libs/1_81_0/libs/graph/doc/table_of_contents.html


### Custom Graph Library

Graph = (V,E)
- V: set of verteces
- E: set of edges
- Adjacency list: lists adjacent verteces

```
Graph:
- All verteces in the graph (verteces_: vector<Vertex>)
- All edges in the graph (edges_: vector<Edges>)
- Map that stores a list with adjacent vertices, through the ID and an adjacent element (adjacency_list_: unordered_map<int, AdjacencyElement>)
```

By instantiating a graph, we pass a vector of verteces and a vector of edges to the constructor. A undirected graph is then created, with the list of vertices and edges as a member. Furthermore, the graph creates an adjacency list based on the veteces and edges. They are saved in a an ```unordered_map<int, AdjacentElement>```, that can publicly be accessed.





Helper classes for the Graph data structure:
```
Vertex:
- ID (id_: int)
- Longitude (longitude_: double)
- Lattitude (lattitude_: double)
```

```
Edge:
- Source ID (source_vid_: int)
- Destination ID (dest_vid_: int)
- Length (length_: double)
- Name (name_: string)
```

```
AdjacencyElement:
- Source vertex (v_: Vertex)
- Adjacent Elements (adjacent_elements_: vector<int>)
```

## Team
Filippo Zeggio
- GitHub: curcuman
- LinkedIn: https://www.linkedin.com/in/filippo-zeggio/

Christian Siman-Chereches
- GitHub: callmechristian
- LinkedIn: https://www.linkedin.com/in/christian-simăn-cherecheș-a0195022a/

Dalim Wahby
- GitHub: citrovin
- LinkedIn: https://www.linkedin.com/in/dalim-wahby/