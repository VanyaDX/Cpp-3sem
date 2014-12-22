#include "graph.h"

#include <stack>
#include <algorithm>
#include <fstream>
#include <sstream>

template <typename NodePayload> 
Graph<NodePayload>::Graph() {}

template <typename NodePayload> 
Graph<NodePayload>::~Graph() {}

template <typename NodePayload>
void Graph<NodePayload>::clear() {
    vertex.clear();
    payloads.clear();
}

template <typename NodePayload> template <class Archive>
void Graph<NodePayload>::serialize(Archive &arg, const uint32_t version) {
    arg &vertex;
    arg &payloads;
}

template <typename NodePayload>
void Graph<NodePayload>::loadFromFile(std::string const &ss) {
    Graph g;
    std::ifstream ifs(ss);
    boost::archive::text_iarchive input(ifs);
    input >> g;
    vertex = g.vertex;
    payloads = g.payloads;
}

template <typename NodePayload>
void Graph<NodePayload>::saveToFile(std::string const &ss) {
    std::ofstream ofs(ss);
    boost::archive::text_oarchive output(ofs);
    output << *this;
}

template <typename NodePayload>
Graph<uint32_t>::NodeHandle Graph<NodePayload>::addNode() {
    vertex.push_back(std::vector<NodeHandle>());
    vertex.back().reserve(100);
    payloads.push_back(defaultPayload);
    return vertex.size() - 1;
}


template <typename NodePayload>
void Graph<NodePayload>::addEdge(NodeHandle const &u, NodeHandle const &v) {
    //it makes no sense to create cycles with one vertex
    if (u != v) {
        if (!std::count(vertex[u].begin(), vertex[u].end(), v)) { 
            vertex[u].push_back(v);
        }
        if (!std::count(vertex[v].begin(), vertex[v].end(), u)) {
            vertex[v].push_back(u);
        }
    }
}

template <typename NodePayload>
void Graph<NodePayload>::forEachNode(std::function<void(NodeHandle const &)> const &visitor) const {
    for (size_t it = 0; it < vertex.size(); it++) {
        visitor((NodeHandle) it);
    }
}

template <typename NodePayload>
void Graph<NodePayload>::forEachEdge(NodeHandle const &source, EdgeVisitor const &visitor) {
    if (source >= vertex.size() || source < 0) { //out of vector
        throw new std::exception();
    }

    for (auto it = vertex[source].begin(); it != vertex[source].end(); it++) {
        visitor((EdgeHandle) std::make_pair(source, *it));
    }
}

template <typename NodePayload>
size_t Graph<NodePayload>::getNodesCount() const {
    return vertex.size();
}

template <typename NodePayload>
Graph<uint32_t>::NodeHandle Graph<NodePayload>::move(const NodeHandle &source, const EdgeHandle &edge) {
    return source == edge.first ? edge.second : edge.first;
}

template <typename NodePayload>
NodePayload & Graph<NodePayload>::operator[](NodeHandle const &node) {
    if (node >= payloads.size() || node < 0) { //out of vector
        throw new std::exception();
    }
    return payloads[node];
}

template <typename NodePayload>
void Graph<NodePayload>::dfs(NodeVisitor const & startNode, NodeVisitor const & endNode, NodeVisitor const & discoverNode) {
    bool* used = new bool[vertex.size()]; //array shows used vertexes
    std::fill_n(used, vertex.size(), false); //any vertexes not used
    NodeHandle current;
    for (NodeHandle i = 0; i < vertex.size(); i++) {
        if (!used[i]) {
            std::stack<NodeHandle> st; //need for order of vertexes
            st.push(i);
            while (!st.empty()) {
                current = st.top();
                st.pop();
                startNode(current);

                for (auto it = vertex[current].begin(); it != vertex[current].end(); it++) {
                    discoverNode(*it);
                    if (!used[*it]) {
                        used[*it] = true;
                        st.push(*it);
                    }
                }

                endNode(current);
            }
        }
    }
    delete[] used;
}
