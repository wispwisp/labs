#ifndef MY_GRAPH_VISITOR_HPP
#define MY_GRAPH_VISITOR_HPP

#include <boost/graph/adjacency_matrix.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/graph_utility.hpp>

template <class Graph, class VertexesContent, class EdgesContent>
struct GraphVisitor {
  using Vertex = typename boost::graph_traits<Graph>::vertex_descriptor;

  GraphVisitor(const Graph &g, const VertexesContent &c, const EdgesContent &e)
      : graph(g), vertexes_content(c), edges_content(e){};

  void operator()(const Vertex &v) {
    // indexes of inserted vertex
    const auto &vertex_indexes = boost::get(boost::vertex_index, graph);

    // indexes of edges
    const auto &edge_indexes = boost::get(boost::edge_index, graph);

    // iterators to all out-edges of vertex (begin, end]
    // change to:
    // - boost::out_edges
    // - boost::in_edges
    // - boost::adjacent_vertices
    const auto &c = vertexes_content[vertex_indexes[v]];
    std::cout << "'" << c.name << "' out-edges: ";

    for (auto p = boost::out_edges(v, graph); p.first != p.second; ++p.first) {
      auto edge = *p.first;

      Vertex source = boost::source(edge, graph);
      Vertex target = boost::target(edge, graph);
      std::cout << "(" << vertex_indexes[source] << ", " << vertex_indexes[target] << " ["
                << edges_content[edge_indexes[edge]] << "]) ";
    }
    std::cout << std::endl;
  }

private:
  const Graph &graph;
  const VertexesContent &vertexes_content;
  const EdgesContent &edges_content;
};

#endif // MY_GRAPH_VISITOR_HPP

