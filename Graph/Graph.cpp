#include <iostream>
#include <vector>

#define LOG(msg) std::cout << msg << std::endl;

template <typename T> class Iterator {
public:
  Iterator(){};
  virtual ~Iterator(){};
  virtual bool IsDone() = 0;
  const virtual T &operator*() = 0;
  virtual void operator++() = 0;
};
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

  void ShowVertices() {
    auto &allVerticesIter = *new AllVerticesIter(*this);
    while (!allVerticesIter.IsDone()) {
      const auto &v = *allVerticesIter;
      LOG("allVerticesIter vertex number: " << v.Number()
                                            << " vertex weight: " << v.weight);
      ++allVerticesIter;
    }
  }

  void ShowEdges() {
    auto &allEdgesIter = *new AllEdgesIter(*this);
    while (!allEdgesIter.IsDone()) {
      const auto &edge = *allEdgesIter;
      LOG("Edge vertices:   v0: " << edge.V0()->Number()
                                  << "    v1: " << edge.V1()->Number());
      ++allEdgesIter;
    }
  }

  void ShowEmamEdges(int v) {
    auto &emanEdgesIter = *new EmanEdgesIter(*this, v);
    while (!emanEdgesIter.IsDone()) {
      const auto &edge = *emanEdgesIter;
      LOG("Eman edge vertices   v0: " << edge.V0()->Number()
                                      << "    v1: " << edge.V1()->Number());
      ++emanEdgesIter;
    }
  }

  void ShowInciEdges(int v) {
    auto &inciEdgesIter = *new InciEdgesIter(*this, v);
    while (!inciEdgesIter.IsDone()) {
      const auto &edge = *inciEdgesIter;
      LOG("Inci edge vertices   v0: " << edge.V0()->Number()
                                      << "    v1: " << edge.V1()->Number());
      ++inciEdgesIter;
    }
  }

  class AllVerticesIter : public Iterator<Vertex> {
    GraphAsMatrix &owner;
    int current;

  public:
    ~AllVerticesIter() {}
    AllVerticesIter(GraphAsMatrix &owner) : owner(owner), current(0) {}
    bool IsDone() { return current >= owner.vertices.size() ? true : false; }
    Vertex &operator*() { return *owner.vertices[current]; }
    void operator++() { current++; }
  };
  class AllEdgesIter : public Iterator<Edge> {
    GraphAsMatrix &owner;
    int row{0};
    int col{0};
    bool done{false};

  public:
    void Next() {
      for (; row < owner.numberOfVertices; row++) {
        for (++col; col < owner.numberOfVertices; col++) {
          if (owner.adjacencyMatrix[row][col])
            return;
        }
        col = -1;
      }
      done = true;
    }
    AllEdgesIter(GraphAsMatrix &owner) : owner(owner) { Next(); }
    bool IsDone() { return done; }
    Edge &operator*() { return *owner.SelectEdge(row, col); }
    void operator++() { Next(); }
  };
  class EmanEdgesIter : public Iterator<Edge> {
    GraphAsMatrix &owner;
    int row;
    int col{-1};
    bool done{false};

  public:
    void Next() {
      for (++col; col < owner.numberOfVertices; col++) {
        if (owner.adjacencyMatrix[row][col])
          return;
      }
      done = true;
    };
    EmanEdgesIter(GraphAsMatrix &owner, int v) : owner(owner), row(v) {
      Next();
    }
    bool IsDone() { return done; }
    Edge &operator*() { return *owner.SelectEdge(row, col); }
    void operator++() { Next(); }
  };
  class InciEdgesIter : public Iterator<Edge> {
    GraphAsMatrix &owner;
    int row{-1};
    int col;
    bool done;

  public:
    void Next() {
      for (++row; row < owner.numberOfVertices; row++) {
        if (owner.adjacencyMatrix[row][col])
          return;
      }
      done = true;
    }
    InciEdgesIter(GraphAsMatrix &owner, int v) : owner(owner), col(v) {
      Next();
    }
    bool IsDone() { return done; }
    Edge &operator*() { return *owner.SelectEdge(row, col); }
    void operator++() { Next(); }
  };

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

  LOG("\n===Testing iterators===");

  graph->ShowVertices();

  graph->AddEdge(3, 5);
  graph->AddEdge(8, 3);
  graph->AddEdge(5, 2);

  graph->ShowEdges();
  graph->ShowEmamEdges(3);
  graph->ShowInciEdges(2);

  delete graph;

  std::cout << std::endl << std::endl;
}

int main(int argc, char const *argv[]) {
  test(true);
  test(false);
  return 0;
}
