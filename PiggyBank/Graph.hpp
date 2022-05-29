#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <vector>

#define LOG(msg) std::cout << msg << std::endl;

template <typename T>
class Iterator
{
   public:
    Iterator(){};
    virtual ~Iterator(){};
    virtual bool IsDone() = 0;
    const virtual T& operator*() = 0;
    virtual void operator++() = 0;
};

template <typename T>
class Visitor
{
   public:
    virtual void Visit(T& v){};
    virtual bool IsDone() const { return false; }
};

class Vertex
{
   private:
    unsigned int number;

   public:
    Vertex(unsigned int n) { number = n; }
    int weight;
    bool visited{false};
    std::string label;
    int Number() const { return number; }
};

class CountingVisitor : Visitor<Vertex>
{
    int ctr{0};
    bool verbose{false};

   public:
    void Visit(Vertex& v)
    {
        ctr++;
        if (verbose)
            LOG("Visiting vertex: " << v.Number());
    }
    bool IsDone() { return false; }
    int GetCounter() { return ctr; }
    void reset() { ctr = 0; }
    void SetVerbosity(bool isVerbose) { verbose = isVerbose; }
};

class Edge
{
   protected:
    Vertex* v0;
    Vertex* v1;

   public:
    Edge(Vertex* V0, Vertex* V1)
    {
        v0 = V0;
        v1 = V1;
    }
    int weight;
    std::string label;
    Vertex* V0() const { return v0; }
    Vertex* V1() const { return v1; }
    Vertex* Mate(Vertex* v) const { return v->Number() == v0->Number() ? v1 : v0; }
};

class GraphAsMatrix
{
   private:
    std::vector<Vertex*> vertices;
    std::vector<std::vector<Edge*>> adjacencyMatrix;
    bool isDirected;
    unsigned int numberOfVertices;
    unsigned int numberOfEdges{0};

   public:
    GraphAsMatrix(unsigned int n, bool directed = false)
    {
        isDirected = directed;
        numberOfVertices = n;

        for (auto i = 0; i < n; i++)
        {
            vertices.push_back(new Vertex(i));
            adjacencyMatrix.push_back(std::vector<Edge*>(n, nullptr));
        }
    }

    void ShowVertices()
    {
        auto& allVerticesIter = *new AllVerticesIter(*this);
        while (!allVerticesIter.IsDone())
        {
            const auto& v = *allVerticesIter;
            LOG("allVerticesIter vertex number: " << v.Number() << " vertex weight: " << v.weight);
            ++allVerticesIter;
        }
    }

    void ShowEdges()
    {
        auto& allEdgesIter = *new AllEdgesIter(*this);
        while (!allEdgesIter.IsDone())
        {
            const auto& edge = *allEdgesIter;
            LOG("Edge vertices:   v0: " << edge.V0()->Number() << "    v1: " << edge.V1()->Number());
            ++allEdgesIter;
        }
    }

    void ShowEmamEdges(int v)
    {
        auto& emanEdgesIter = *new EmanEdgesIter(*this, v);
        while (!emanEdgesIter.IsDone())
        {
            const auto& edge = *emanEdgesIter;
            LOG("Eman edge vertices   v0: " << edge.V0()->Number() << "    v1: " << edge.V1()->Number());
            ++emanEdgesIter;
        }
    }

    void ShowInciEdges(int v)
    {
        auto& inciEdgesIter = *new InciEdgesIter(*this, v);
        while (!inciEdgesIter.IsDone())
        {
            const auto& edge = *inciEdgesIter;
            LOG("Inci edge vertices   v0: " << edge.V0()->Number() << "    v1: " << edge.V1()->Number());
            ++inciEdgesIter;
        }
    }

    void DFS(Vertex* v)
    {
        CountingVisitor cv;
        cv.SetVerbosity(true);
        std::vector<bool> visitedVertices;
        for (auto i = 0; i < numberOfVertices; i++)
            visitedVertices.push_back(false);
        DFS1(cv, v, visitedVertices);
        for (auto i = 0; i < numberOfVertices; i++)
            if (!visitedVertices[i])
                DFS1(cv, vertices[i], visitedVertices);
    }

    void DFS1(CountingVisitor& cv, Vertex* v, std::vector<bool>& visited)
    {
        cv.Visit(*v);
        visited[v->Number()] = true;
        auto& emanEdgesIter = *new EmanEdgesIter(*this, v->Number());
        while (!emanEdgesIter.IsDone())
        {
            const auto& edge = *emanEdgesIter;
            if (visited[edge.V1()->Number()] == false)
                DFS1(cv, edge.V1(), visited);
            ++emanEdgesIter;
        }
    }

    bool IsConnected()
    {
        CountingVisitor cv;
        if (!this->isDirected)
        {
            std::vector<bool> visited(this->numberOfVertices, false);
            DFS1(cv, vertices[0], visited);
            return cv.GetCounter() == this->numberOfVertices;
        }
        else
        {
            for (int i = 0; i < numberOfVertices; i++)
            {
                std::vector<bool> visited(this->numberOfVertices, false);
                DFS1(cv, vertices[i], visited);
                if (cv.GetCounter() != this->numberOfVertices)
                    return false;
                cv.reset();
            }
            return true;
        }
    }

    void DFSSpanningTree(Vertex* v)
    {
        if (IsConnected())
        {
            std::vector<bool> visited(numberOfVertices, false);
            std::vector<int> parent(numberOfVertices, -1);
            DFSSpanningTree1(v, visited, parent);
        }
        else
            LOG("Graph is not connected!");
    }

    void DFSSpanningTree1(Vertex* v, std::vector<bool>& visited, std::vector<int>& parent)
    {
        visited[v->Number()] = true;
        auto& emanEdgesIter = *new EmanEdgesIter(*this, v->Number());
        while (!emanEdgesIter.IsDone())
        {
            const auto& edge = *emanEdgesIter;
            if (visited[edge.V1()->Number()] == false)
            {
                parent[edge.V1()->Number()] = v->Number();
                LOG("Vertex: " << edge.V1()->Number() << " parent is: " << v->Number());
                DFSSpanningTree1(edge.V1(), visited, parent);
            }
            ++emanEdgesIter;
        }
    }

    unsigned int FindConnectedComponents(bool print = true)
    {
        unsigned int connectedComponents{0};
        CountingVisitor cv;
        std::vector<bool> visitedVertices(numberOfVertices, false);

        for (auto i = 0; i < numberOfVertices; i++)
            if (!visitedVertices[i])
            {
                DFS1(cv, vertices[i], visitedVertices);
                connectedComponents++;
            }
        if (print)
            LOG("Connected Components: " << connectedComponents);
        return connectedComponents;
    }

    class AllVerticesIter : public Iterator<Vertex>
    {
        GraphAsMatrix& owner;
        int current;

       public:
        ~AllVerticesIter() {}
        AllVerticesIter(GraphAsMatrix& owner) : owner(owner), current(0) {}
        bool IsDone() { return current >= owner.vertices.size() ? true : false; }
        Vertex& operator*() { return *owner.vertices[current]; }
        void operator++() { current++; }
    };
    class AllEdgesIter : public Iterator<Edge>
    {
        GraphAsMatrix& owner;
        int row{0};
        int col{0};
        bool done{false};

       public:
        void Next()
        {
            for (; row < owner.numberOfVertices; row++)
            {
                for (++col; col < owner.numberOfVertices; col++)
                {
                    if (owner.adjacencyMatrix[row][col])
                        return;
                }
                col = -1;
            }
            done = true;
        }
        AllEdgesIter(GraphAsMatrix& owner) : owner(owner) { Next(); }
        bool IsDone() { return done; }
        Edge& operator*() { return *owner.SelectEdge(row, col); }
        void operator++() { Next(); }
    };
    class EmanEdgesIter : public Iterator<Edge>
    {
        GraphAsMatrix& owner;
        int row;
        int col{-1};
        bool done{false};

       public:
        void Next()
        {
            for (++col; col < owner.numberOfVertices; col++)
            {
                if (owner.adjacencyMatrix[row][col])
                    return;
            }
            done = true;
        };
        EmanEdgesIter(GraphAsMatrix& owner, int v) : owner(owner), row(v) { Next(); }
        bool IsDone() { return done; }
        Edge& operator*() { return *owner.SelectEdge(row, col); }
        void operator++() { Next(); }
    };
    class InciEdgesIter : public Iterator<Edge>
    {
        GraphAsMatrix& owner;
        int row{-1};
        int col;
        bool done;

       public:
        void Next()
        {
            for (++row; row < owner.numberOfVertices; row++)
            {
                if (owner.adjacencyMatrix[row][col])
                    return;
            }
            done = true;
        }
        InciEdgesIter(GraphAsMatrix& owner, int v) : owner(owner), col(v) { Next(); }
        bool IsDone() { return done; }
        Edge& operator*() { return *owner.SelectEdge(row, col); }
        void operator++() { Next(); }
    };

    int NumberOfVertices() { return numberOfVertices; }
    bool IsDirected() { return isDirected; }
    int NumberOfEdges() { return numberOfEdges; }
    const bool IsEdge(int u, int v) const { return adjacencyMatrix[u][v] != nullptr; };
    void MakeNull()
    {
        for (auto i = 0; i < numberOfVertices; i++)
        {
            for (auto j = 0; j < numberOfVertices; j++)
            {
                if (adjacencyMatrix[i][j])
                    delete adjacencyMatrix[i][j];
            }
        }
        numberOfEdges = 0;
    }
    void AddEdge(int u, int v)
    {
        if (vertices[u] == nullptr)
        {
            vertices[u] = new Vertex(u);
            numberOfVertices++;
        }

        if (vertices[v] == nullptr)
        {
            vertices[v] = new Vertex(v);
            numberOfVertices++;
        }
        if (!adjacencyMatrix[u][v])
        {
            adjacencyMatrix[u][v] = new Edge(vertices[u], vertices[v]);
            numberOfEdges++;
        }
        if (!isDirected && !adjacencyMatrix[v][u])
        {
            adjacencyMatrix[v][u] = new Edge(vertices[v], vertices[u]);
        }
    };
    void AddEdge(Edge* edge)
    {
        if (!adjacencyMatrix[edge->V0()->Number()][edge->V1()->Number()])
        {
            adjacencyMatrix[edge->V0()->Number()][edge->V1()->Number()] = edge;
            numberOfEdges++;
        }
        if (!isDirected && adjacencyMatrix[edge->V1()->Number()][edge->V0()->Number()])
        {
            adjacencyMatrix[edge->V1()->Number()][edge->V0()->Number()] = edge;
        }
    }

    Edge* SelectEdge(int u, int v) const { return adjacencyMatrix[u][v]; };
    Vertex* SelectVertex(int v) const { return vertices[v]; };
};
