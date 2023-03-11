# Map Path Finder

# Instatiating the Graph using the Boost Graph Library (BGL)
Properties of our Graph:
- directed graph
- Verteces (nodes) have following attributes: ID (int), Longitude (double), Lattitude (double)
- Arcs (edges) have the following attributes: source ID (int), destination ID (int), length (double), name (string)

## BGL

Instantiating the Graph:
```
typedef adjacency_list<vecS, vecS, bidirectionalS> Graph;
```

- ```vecS```: vector as a datatype for the out-edges and the set of verteces (nodes)

- ```bidirectionalS```: defines, that the graph is bidirectional (other options: ```undirectedS```, ```directedS```)

Documentation of the BGL: https://www.boost.org/doc/libs/1_81_0/libs/graph/doc/table_of_contents.html


# Team
Filippo Zeggio
- GitHub: curcuman

Christian Siman-Chereches
- GitHub: callmechristian

Dalim Wahby
- GitHub: citrovin