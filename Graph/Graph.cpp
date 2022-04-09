#include <iostream>
#include <vector>

#define LOG(msg) std::cout << msg << std::endl;
class Vertex {
private:
  unsigned int number;

public:
  Vertex(unsigned int n) { number = n; }
  int weight;
  std::string label;
  int Number() const { return number; }
};
class Edge {
protected:
  Vertex *v0;
  Vertex *v1;

public:
  Edge(Vertex *V0, Vertex *V1) {
    v0 = V0;
    v1 = V1;
  }
  int weight;
  std::string label;
  Vertex *V0() const { return v0; }
  Vertex *V1() const { return v1; }
  Vertex *Mate(Vertex *v) const {
    return v->Number() == v0->Number() ? v1 : v0;
  }
};

class GraphAsMatrix {
private:
  std::vector<Vertex *> vertices;
  std::vector<std::vector<Edge *>> adjacencyMatrix;
  bool isDirected;
  unsigned int numberOfVertices;
  unsigned int numberOfEdges{0};

public:
  GraphAsMatrix(unsigned int n, bool directed = false) {
    isDirected = directed;
    numberOfVertices = n;

    for (auto i = 0; i < n; i++) {
      vertices.push_back(new Vertex(i));
      adjacencyMatrix.push_back(std::vector<Edge *>(n, nullptr));
    }
  }
  int NumberOfVertices() { return numberOfVertices; }
  bool IsDirected() { return isDirected; }
  int NumberOfEdges() { return numberOfEdges; }
  const bool IsEdge(int u, int v) const {
    return adjacencyMatrix[u][v] != nullptr;
  };
  void MakeNull() {
    for (auto i = 0; i < numberOfVertices; i++) {
      for (auto j = 0; j < numberOfVertices; j++) {
        if (adjacencyMatrix[i][j])
          delete adjacencyMatrix[i][j];
      }
    }
    numberOfEdges = 0;
  }
  void AddEdge(int u, int v) {
    if (vertices[u] == nullptr) {
      vertices[u] = new Vertex(u);
      numberOfVertices++;
    }

    if (vertices[v] == nullptr) {
      vertices[v] = new Vertex(v);
      numberOfVertices++;
    }
    if (!adjacencyMatrix[u][v]) {
      adjacencyMatrix[u][v] = new Edge(vertices[u], vertices[v]);
      numberOfEdges++;
    }
    if (!isDirected && !adjacencyMatrix[v][u]) {
      adjacencyMatrix[v][u] = new Edge(vertices[v], vertices[u]);
    }
  };
  void AddEdge(Edge *edge) {
    if (!adjacencyMatrix[edge->V0()->Number()][edge->V1()->Number()]) {
      adjacencyMatrix[edge->V0()->Number()][edge->V1()->Number()] = edge;
      numberOfEdges++;
    }
    if (!isDirected &&
        adjacencyMatrix[edge->V1()->Number()][edge->V0()->Number()]) {
      adjacencyMatrix[edge->V1()->Number()][edge->V0()->Number()] = edge;
    }
  }

  Edge *SelectEdge(int u, int v) const { return adjacencyMatrix[u][v]; };
  Vertex *SelectVertex(int v) const { return vertices[v]; };
};

void edgeTest(GraphAsMatrix *graph, unsigned int v1, unsigned int v2) {
  auto e = graph->SelectEdge(v1, v2);
  LOG("e->V0: " << e->V0()->Number());
  LOG("e->V1: " << e->V1()->Number());
  LOG("Mate(v0): " << e->Mate(e->V0())->Number());
  LOG("Mate(v1): " << e->Mate(e->V1())->Number());
  e->weight = e->V0()->Number() + e->V1()->Number();
  LOG("Waga krawedzi: " << e->weight);
  delete e;
}

void test(bool isDirected) {
  LOG("===== Testing for isDirected : " << std::boolalpha << isDirected
                                        << " =====" << std::endl);
  const auto &graph = new GraphAsMatrix(10, isDirected);
  LOG("graph->IsDirected(): " << graph->IsDirected());
  LOG("Ilosc wierzcholkow: " << graph->NumberOfVertices());
  LOG("Ilosc krawedzi: " << graph->NumberOfEdges());
  const auto &v = graph->SelectVertex(2);
  LOG("v->Number(): " << v->Number());
  v->weight = v->Number() * v->Number();
  LOG("Waga wierzcholka: " << v->weight);

  graph->AddEdge(1, 2);
  graph->AddEdge(1, 2);
  graph->AddEdge(2, 3);
  graph->AddEdge(3, 4);
  graph->AddEdge(9, 9);

  LOG("Ilosc wierzcholkow: " << graph->NumberOfVertices());
  LOG("Ilosc krawedzi: " << graph->NumberOfEdges());
  LOG("IsEdge(1,1): " << graph->IsEdge(1, 1));
  LOG("IsEdge(1,2): " << graph->IsEdge(1, 2));
  LOG("IsEdge(2,1): " << graph->IsEdge(2, 1));

  edgeTest(graph, 1, 2);
  edgeTest(graph, 2, 3);
  edgeTest(graph, 3, 4);
  edgeTest(graph, 9, 9);

  delete graph;

  std::cout << std::endl << std::endl;
}

int main(int argc, char const *argv[]) {
  test(true);
  test(false);
  return 0;
}
