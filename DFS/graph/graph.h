#ifndef _H_GRAPH_
#define _H_GRAPH_

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <functional>

template<typename NodePayload>
class Graph {
public:
    typedef uint32_t NodeHandle;
    typedef std::pair<NodeHandle, NodeHandle> EdgeHandle;
    typedef std::function<void(NodeHandle const &)> NodeVisitor;
    typedef std::function<void(EdgeHandle const &)> EdgeVisitor;
public:    
    Graph();
    ~Graph();
    void loadFromFile(std::string const & filename);
    void saveToFile(std::string const & filename);
    NodeHandle addNode();
    void addEdge(NodeHandle const & a, NodeHandle const & b);
    void forEachNode(std::function<void(NodeHandle const &)> const & visitor) const;
    size_t getNodesCount() const;
    void forEachEdge(NodeHandle const & source, EdgeVisitor const & visitor);
    NodeHandle move(NodeHandle const & origin, EdgeHandle const & edge);
    NodePayload & operator[](NodeHandle const & node);
    void dfs(NodeVisitor const & startNode, NodeVisitor const & endNode, NodeVisitor const & discoverNode);
private:
    friend class boost::serialization::access;

    //clear the vectors of vertex and payloads
    void clear();
    //vector of vertex
    std::vector < std::vector <NodeHandle> > vertex;
    //vector of payloads 
    std::vector <NodePayload> payloads;
    template <class Archive>
    void serialize(Archive & ar, uint32_t version);
    NodePayload defaultPayload;
};


#endif // _H_GRAPH_
