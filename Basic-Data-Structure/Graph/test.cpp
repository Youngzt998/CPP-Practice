# include <iostream>
# include "graph.hpp"

using namespace std;

int main()
{
    
    UndirGraph<double, int> graph;
    for (int i = 1; i <= 6; ++ i)
        graph.addNode(i, i);

    graph.addEdge(1, 2, 7);
    graph.addEdge(1, 3, 9);
    graph.addEdge(1, 6, 14);
    graph.addEdge(2, 3, 10);
    graph.addEdge(2, 4, 15);
    graph.addEdge(3, 4, 11);
    graph.addEdge(3, 6, 2);
    graph.addEdge(4, 5, 6);
    graph.addEdge(5, 6, 9);

    graph.printGraph();

    int i = 1;

    vector<pair<int, double>> result = graph.runDijkstra(i);
    cout << i << ":\n";
    for (int j = 0; j < result.size(); ++ j )
        cout << '(' << result[j].first << ", " << result[j].second << ")\n";
    return 0;
}