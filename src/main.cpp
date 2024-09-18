#include "../include/graph.h"
#include <iostream>
int main()
{
    Graph g(6, true);
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(2, 3);
    g.addEdge(3, 4);
    g.addEdge(0, 5);
    g.addEdge(5, 4);
    g.printGraph();
    std::cout << g.getCountOfAllPossiblePath(0, 4);
    return 0;
}