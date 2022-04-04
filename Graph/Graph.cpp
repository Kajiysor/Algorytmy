#include <iostream>
#include <memory>
#include <vector>

class Vertex {
  unsigned int number;

public:
  Vertex(unsigned int n) { number = n; }
  int weight;
  std::string label;
  int Number() const { return number; }
};

class GraphAsMatrix {
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
    Vertex *V0() { return v0; }
    Vertex *V1() { return v1; }
    Vertex *Mate(Vertex *v);
  };

  std::vector<Vertex *> vertices;
  std::vector<std::vector<Edge *>> adjacencyMatrix;
  bool isDirected;
  int numberOfVertices;
  int numberOfEdges = 0;
  unsigned int size;

public:
  GraphAsMatrix(unsigned int n, bool directed = false) {
    size = n;
    isDirected = directed;
    adjacencyMatrix.resize(n);
    vertices.resize(n);
    numberOfVertices++;
    for (auto i = 0; i < size; i++) {
      vertices.push_back(new Vertex(i));
      adjacencyMatrix[i].resize(size);
    }

    for (auto i = 0; i < size; i++) {
      for (auto j = 0; j < size; j++) {
        adjacencyMatrix[i][j] = nullptr;
      }
    }
  }
  int NumberOfVertices() { return numberOfVertices; }
  bool IsDirected() { return isDirected; }
  int NumberOfEdges() { return numberOfEdges; }
  const bool IsEdge(int u, int v) {
    if (!isDirected) {
      if (adjacencyMatrix[u][v] || adjacencyMatrix[u][v])
        return true;
      else
        return false;
    } else {
      if (adjacencyMatrix[u][v])
        return true;
      else
        return false;
    }
  };
  void MakeNull() {
    for (auto i = 0; i < size; i++) {
      adjacencyMatrix[i].resize(size);
    }

    for (auto i = 0; i < size; i++) {
      for (auto j = 0; j < size; j++) {
        adjacencyMatrix[i][j] = nullptr;
      }
    }
  }
  void AddEdge(int u, int v) {
    if (adjacencyMatrix[u][v] == nullptr) {
      adjacencyMatrix[u][v] = new Edge(vertices[u], vertices[v]);
      numberOfEdges++;
      if (!isDirected)
        adjacencyMatrix[v][u] = adjacencyMatrix[u][v];
    }
  };
  void AddEdge(Edge *edge);
  Edge *SelectEdge(int u, int v) {
    if (IsEdge(u, v))
      return adjacencyMatrix[u][v];
    else
      return nullptr;
  };
  Vertex *SelectVertex(int v) { return vertices[v]; };
};

int main(int argc, char const *argv[]) { return 0; }
