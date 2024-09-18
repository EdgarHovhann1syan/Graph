#ifndef GRAPH_H
#define GRAPH_H
#include <vector>
#include <iostream>
#include <queue>
#include <algorithm>
#include <stdexcept>
class Graph 
{
public:
    Graph(std::size_t countOfVertices, bool isDirected);
    void addEdge(std::size_t u, std::size_t v); // add connection from u to v.
    void removeEdge(std::size_t u, std::size_t v); // remove connection from u to v.
    void printGraph();
    void dfs(std::size_t u);
    void bfs(std::size_t u);
    void transpose();
    std::vector<std::size_t> getShortestPath(std::size_t u, std::size_t v);
    std::size_t getCountNodesAtAGivenLevelBFS(std::size_t u, std::size_t level);
    std::size_t getCountNodesAtAGivenLevelDFS(std::size_t u, std::size_t level);
    std::size_t getCountOfAllPossiblePath(std::size_t u, std::size_t v);
    bool is_cycled();
    std::vector<std::size_t> topSort_dfs();
    std::vector<std::size_t> topSort_Kahn();
private:
    std::vector<std::vector<std::size_t>> m_adjMatrix;
    std::size_t m_countOfVertices;
    bool m_isDirected;
private: // helper functions
    void dfs_helper(std::size_t u, std::vector<bool>& visited); // helper function for dfs
    void dfs_helper_Count_Nodes_At_Given_Level(std::size_t node, std::size_t currentLevel, std::size_t targetLevel, std::vector<bool>& visited, std::size_t& count);
    std::size_t dfs_count_paths(std::size_t u, std::size_t v, std::vector<bool>& visited);
    void dfs_helper_topSort(std::size_t u, std::vector<std::size_t>& topOrder, std::vector<bool>& visited);
    bool dfs_helper_is_cycled_undirected(std::size_t u, std::vector<bool>& visited, std::size_t parent);
    bool dfs_helper_is_cycled_directed(std::size_t u, std::vector<bool>& visited, std::vector<bool>& recStack);
    bool is_cycled_directed();
    bool is_cycled_undirected();    
};
#endif //GRAPH_H