#include <boost/test/unit_test.hpp>

#include "GraphVisitor.hpp"

#include <iostream>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/adjacency_matrix.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/graph_utility.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

BOOST_AUTO_TEST_SUITE(SomeTest)

BOOST_AUTO_TEST_CASE(TestOne) {
  using Graph =
      boost::adjacency_list<boost::vecS, boost::vecS, boost::bidirectionalS>;
  using Edge = std::pair<int, int>;

  enum { A, B, C, D, E, N };
  const int num_vertices = N;

  Edge edge_array[] = {Edge(A, B), Edge(A, D), Edge(C, A), Edge(D, C),
                       Edge(C, E), Edge(B, D), Edge(D, E)};

  const int num_edges = sizeof(edge_array) / sizeof(edge_array[0]);

  {
    Graph g(num_vertices);

    for (int i = 0; i < num_edges; ++i)
      add_edge(edge_array[i].first, edge_array[i].second, g);
  }
  {
    Graph g(edge_array, edge_array + sizeof(edge_array) / sizeof(Edge),
            num_vertices);
  }
}

BOOST_AUTO_TEST_CASE(TestTwo) {
  enum { A, B, C, D, E, F, N };
  std::vector<std::string> names{
    "Aloha", "Bob", "Call", "Dir", "Echo", "Frame",
  };

  typedef boost::adjacency_matrix<boost::undirectedS> Graph;
  Graph g(N);

  add_edge(B, C, g);
  add_edge(B, F, g);
  add_edge(C, A, g);
  add_edge(C, C, g);
  add_edge(D, E, g);
  add_edge(E, D, g);
  add_edge(F, A, g);
  add_edge(F, A, g);
  add_edge(F, A, g);

  std::cout << "vertex set: ";
  boost::print_vertices(g, names.data());
  std::cout << std::endl;

  std::cout << "edge set: ";
  boost::print_edges(g, names.data());
  std::cout << std::endl;

  std::cout << "out-edges: " << std::endl;
  boost::print_graph(g, names.data());
  std::cout << std::endl;

  // vertices:
  std::cout << "vertices(g) = ";
  const auto& index = get(boost::vertex_index, g);
  for (auto vp = boost::vertices(g); vp.first != vp.second; ++vp.first) {
    auto v = *vp.first;
    std::cout << index[v] <<  " ";
  }
  std::cout << std::endl;

  // edges:
  std::cout << "edges(g) = ";
  for (auto ep = boost::edges(g); ep.first != ep.second; ++ep.first) {
    std::cout << "(" << index[boost::source(*ep.first, g)]
              << "," << index[boost::target(*ep.first, g)] << ") ";
  }
  std::cout << std::endl;
}

BOOST_AUTO_TEST_CASE(TestThree) {
  struct Content {
    Content(const char *s) : name(s){};
    std::string name;
  };

  // Vertex content
  using VertexContent = std::vector<Content>;
  enum { Aloha, Bob, Call, Dir, Echo, Frame, N };
  VertexContent vertex_content{
      "Aloha", "Bob", "Call", "Dir", "Echo", "Frame",
  };

  using Graph = boost::adjacency_matrix<boost::directedS,   // undirectedS
                                        boost::no_property, // Vertex property
                                        boost::property<boost::edge_index_t, std::size_t>>;
  Graph g(N);
  std::size_t edge_counter = 0;

  add_edge(Bob, Call, edge_counter++, g);
  add_edge(Bob, Frame, edge_counter++, g);
  add_edge(Call, Aloha, edge_counter++, g);
  add_edge(Call, Call, edge_counter++, g);
  add_edge(Dir, Echo, edge_counter++, g);
  add_edge(Echo, Dir, edge_counter++, g);
  add_edge(Frame, Aloha, edge_counter++, g);

  // if same - not increment
  {
    std::cout << edge_counter << "\n";
    auto ret = add_edge(Frame, Aloha, edge_counter, g);
    if (ret.second)
      edge_counter++;
    std::cout << edge_counter << "\n";
  }

  // differ by direction not same for directedS
  {
    std::cout << edge_counter << "\n";
    auto ret = add_edge(Aloha, Frame, edge_counter, g);
    if (ret.second)
      edge_counter++;
    std::cout << edge_counter << "\n";
  }

  // Edges content
  using EdgesContent = std::vector<std::string>;
  EdgesContent edge_content;
  edge_content.reserve(edge_counter);
  for (std::size_t i = 0; i < edge_counter; i++)
    edge_content.push_back("counter_" + std::to_string(i));

  std::for_each(boost::vertices(g).first,
                boost::vertices(g).second,
                GraphVisitor<Graph, VertexContent, EdgesContent>(g, vertex_content, edge_content));
}

BOOST_AUTO_TEST_CASE(TestUniqueEdges) {
  struct VertexContent {
    std::string name = "";
  };

  struct vertex_property_t {
    using kind = boost::vertex_property_tag;
  };

  struct EdgeContent {
    std::string name1 = "";
    std::string name2 = "";
  };

  struct edge_property_t {
    using kind = boost::edge_property_tag;
  };

  // <tag, type>
  using VertexProperty = boost::property<vertex_property_t, VertexContent>;
  using EdgeProperty = boost::property<edge_property_t, EdgeContent>;

  // template <class OutEdgeListS = vecS,
  //           class VertexListS = vecS,
  //           class DirectedS = directedS,
  //           class VertexProperty = no_property,
  //           class EdgeProperty = no_property,
  //           class GraphProperty = no_property,
  //           class EdgeListS = listS>
  using Graph =
      boost::adjacency_list<boost::hash_setS, boost::vecS, boost::directedS,
                            VertexProperty, EdgeProperty>;
  Graph g;

  // get property maps
  const auto &vertices = boost::get(vertex_property_t(), g);
  const auto &edges = boost::get(edge_property_t(), g);

  using Vertex = boost::graph_traits<Graph>::vertex_descriptor;
  using Edge = boost::graph_traits<Graph>::edge_descriptor;

  auto v = boost::add_vertex(g);
  auto u = boost::add_vertex(g);
  vertices[v].name = "1";
  vertices[u].name = "2";

  bool inserted;
  Edge edge;

  std::tie(edge, inserted) = add_edge(v, u, g);
  if (inserted) {
    edges[edge].name1 = vertices[boost::source(edge, g)].name;
    edges[edge].name2 = vertices[boost::target(edge, g)].name;
  } else
    std::cout << "* Cannot add ununique\n";

  // add ununique
  std::tie(edge, inserted) = add_edge(v, u, g);
  BOOST_ASSERT(not inserted);

  // add inverted direction
  std::tie(edge, inserted) = add_edge(u, v, g);
  BOOST_ASSERT(inserted);
  edges[edge].name1 = vertices[boost::source(edge, g)].name;
  edges[edge].name2 = vertices[boost::target(edge, g)].name;

  BOOST_ASSERT(boost::num_vertices(g) == 2);
  BOOST_ASSERT(boost::num_edges(g) == 2);

  std::cout << "Vertices:\n";
  std::for_each(
      boost::vertices(g).first, boost::vertices(g).second,
      [&](const Vertex &d) { std::cout << "-" << vertices[d].name << "\n"; });

  std::cout << "Edges:\n";
  std::for_each(
      boost::edges(g).first, boost::edges(g).second, [&](const Edge &d) {
        std::cout << "- (" << edges[d].name1 << ", " << edges[d].name2 << ")\n";
      });
}

BOOST_AUTO_TEST_SUITE_END()

