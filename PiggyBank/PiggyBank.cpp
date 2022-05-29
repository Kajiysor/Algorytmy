#include "Graph.hpp"

int main()
{
    int lineInput;
    std::vector<unsigned int> input;
    while (std::cin >> lineInput)
    {
        input.push_back(lineInput);
    }
    if (input.empty())
        LOG("Empty input!")
    else
    {
        const auto& graph = new GraphAsMatrix(input[0], false);
        for (auto i = 1; i < input.size(); i++)
        {
            graph->AddEdge(i - 1, input[i] - 1);
        }
        LOG("Minimum amount of piggy banks to break: " << graph->FindConnectedComponents(false));
        delete graph;
    }
    return 0;
}
