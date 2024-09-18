#include "../include/graph.h"   
Graph::Graph(std::size_t countOfVertices, bool isDirected) : m_countOfVertices(countOfVertices), m_isDirected(isDirected)
{
    this->m_adjMatrix.resize(this->m_countOfVertices, std::vector<std::size_t>(this->m_countOfVertices, 0));
}

void Graph::addEdge(std::size_t u, std::size_t v)
{
    if(u >= 0 && v >= 0 && u < this->m_countOfVertices && v < this->m_countOfVertices)
    {
        this->m_adjMatrix[u][v] = 1;
        if(!this->m_isDirected)
        {
            this->m_adjMatrix[v][u] = 1; // for undirected graph
        }
    }
}

void Graph::removeEdge(std::size_t u, std::size_t v)
{
    if(u >= 0 && v >= 0 && u < this->m_countOfVertices && v < this->m_countOfVertices)
    {
        this->m_adjMatrix[u][v] = 0;
        if(!this->m_isDirected)
        {
            this->m_adjMatrix[v][u] = 0; // for undirected graph
        }
    }
}

void Graph::printGraph()
{
    for(int i = 0; i < this->m_countOfVertices; ++i)
    {
        for(int j = 0; j < this->m_countOfVertices; ++j)
        {
            std::cout << this->m_adjMatrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void Graph::dfs(std::size_t u)
{
    std::vector<bool> visited(this->m_countOfVertices, false);
    dfs_helper(u, visited);
    std::cout << std::endl;
}

void Graph::dfs_helper(std::size_t u, std::vector<bool>& visited)
{
    visited[u] = true;
    std::cout << u << " ";
    for(int v = 0; v < this->m_countOfVertices; ++v)
    {
        if(!visited[v] && this->m_adjMatrix[u][v] == 1)
        {
            dfs_helper(v, visited);
        }
    }
}

void Graph::bfs(std::size_t u)
{
    std::vector<bool> visited(this->m_countOfVertices, false);
    std::queue<std::size_t> q;
    q.push(u);
    visited[u] = true;
    while(!q.empty())
    {
        std::size_t vertex = q.front();
        std::cout << vertex << " ";
        q.pop();
        
        for(int i = 0; i < this->m_countOfVertices; ++i)
        {
            if(!visited[i] && this->m_adjMatrix[vertex][i] == 1)
            {
                q.push(i);
                visited[i] = true;
            }
        }   
    }
    std::cout << std::endl;
}

void Graph::transpose()
{
    std::vector<std::vector<std::size_t>> transposedGraph(this->m_countOfVertices, std::vector<std::size_t>(this->m_countOfVertices, 0));
    for(int u = 0; u < this->m_countOfVertices; ++u)
    {
        for(int v = 0; v < this->m_countOfVertices; ++v)
        {
            transposedGraph[v][u] = this->m_adjMatrix[u][v];
        }
    }
    this->m_adjMatrix = transposedGraph;
}

std::vector<std::size_t> Graph::getShortestPath(std::size_t u, std::size_t v)
{
    std::vector<bool> visited(this->m_countOfVertices, false);
    std::vector<int> parents(this->m_countOfVertices, -1);
    std::queue<std::size_t> q;
    q.push(u);
    visited[u] = true;
    while(!q.empty())
    {
        std::size_t current = q.front();
        q.pop();

        if(current == v) break;

        for(std::size_t i = 0; i < this->m_countOfVertices; ++i)
        {
            if(!visited[i] && this->m_adjMatrix[current][i] == 1)
            {
                q.push(i);
                visited[i] = true;
                parents[i] = current;
            }
        }
    }

    std::vector<std::size_t> path;
    if(!visited[v]) return path;

    for(std::size_t at = v; at != -1; at = parents[at])
    {
        path.push_back(at);
    }

    std::reverse(path.begin(), path.end());
    return path;
}

std::size_t Graph::getCountNodesAtAGivenLevelBFS(std::size_t u, std::size_t level)
{
    std::vector<bool> visited(this->m_countOfVertices, false);
    std::vector<std::size_t> levels(this->m_countOfVertices, 0);
    std::queue<std::size_t> q;
    q.push(u);
    visited[u] = true;
    
    while(!q.empty())
    {
        std::size_t current = q.front();
        q.pop();
        for(std::size_t i = 0; i < this->m_countOfVertices; ++i)
        {
            if(!visited[i] && this->m_adjMatrix[current][i] == 1)
            {
                visited[i] = true;
                q.push(i);
                levels[i] = levels[current] + 1;
            }
        }
    }

    std::size_t count = 0;
    for(int i = 0; i < levels.size(); ++i)
    {
        if(levels[i] == level)
        {
            ++count;
        }
    }

    return count;
}

std::size_t Graph::getCountNodesAtAGivenLevelDFS(std::size_t u, std::size_t level)
{
    std::vector<bool> visited(this->m_countOfVertices, false);
    std::size_t count = 0;
    this->dfs_helper_Count_Nodes_At_Given_Level(u, 0, level, visited, count);
    return count;
}

void Graph::dfs_helper_Count_Nodes_At_Given_Level(std::size_t node, std::size_t currentLevel, std::size_t targetLevel, std::vector<bool>& visited, std::size_t& count)
{
    visited[node] = true;

    if(currentLevel == targetLevel) ++count;

    for(std::size_t i = 0; i < this->m_countOfVertices; ++i)
    {
        if(!visited[i] && this->m_adjMatrix[node][i] == 1)
        {
            dfs_helper_Count_Nodes_At_Given_Level(i, currentLevel + 1, targetLevel, visited, count);    
        }
    }
    
}

std::size_t Graph::dfs_count_paths(std::size_t u, std::size_t v, std::vector<bool>& visited)
{
    if(u == v) return 1;

    visited[u] = true;

    std::size_t pathCount = 0;

    for(std::size_t i = 0; i < this->m_countOfVertices; ++i)
    {
        if(!visited[i] && this->m_adjMatrix[u][i] == 1)
        {
            pathCount += dfs_count_paths(i, v, visited);
        }
    }
    visited[u] = false;
    return pathCount;
}

std::size_t Graph::getCountOfAllPossiblePath(std::size_t u, std::size_t v)
{
    std::vector<bool> visited(this->m_countOfVertices, false);
    return dfs_count_paths(u, v, visited);
}

void Graph::dfs_helper_topSort(std::size_t u, std::vector<std::size_t>& topOrder, std::vector<bool>& visited)
{
    visited[u] = true;
    for(int v = 0; v < this->m_countOfVertices; ++v)
    {
        if(!visited[v] && this->m_adjMatrix[u][v] == 1)
        {
            dfs_helper_topSort(v, topOrder, visited);
        }
    }
    topOrder.push_back(u);
}

std::vector<std::size_t> Graph::topSort_dfs()
{
    std::vector<std::size_t> topOrder;
    std::vector<bool> visited(this->m_countOfVertices);
    for(int u = 0; u < this->m_countOfVertices; ++u)
    {
        dfs_helper_topSort(u, topOrder, visited);
    }
    
    if(this->m_countOfVertices != topOrder.size()) throw std::runtime_error("Graph contains cycle. TopSort is impossible");
    std::reverse(topOrder.begin(), topOrder.end());
    return topOrder;
}

std::vector<std::size_t> Graph::topSort_Kahn()
{
    std::vector<std::size_t> inDegree(this->m_countOfVertices, 0);
    for(int u = 0; u < this->m_countOfVertices; ++u)
    {
        for(int v = 0; v < this->m_countOfVertices; ++v)
        {
            if(this->m_adjMatrix[u][v] == 1)
            {
                ++inDegree[v];
            }
        }
    }

    std::queue<std::size_t> q;
    std::vector<std::size_t> topOrder;
    for(int i = 0; i < this->m_countOfVertices; ++i)
    {
        if(inDegree[i] == 0)
        {
            q.push(i);
        }
    }

    while(!q.empty())
    {
        std::size_t current = q.front();
        q.pop();
        topOrder.push_back(current);

        for(int v = 0; v < this->m_countOfVertices; ++v)
        {
            if(this->m_adjMatrix[current][v] == 1)
            {
                --inDegree[v];
                if(inDegree[v] == 0)
                {
                    q.push(v);
                }
            }
        }
    }

    if(this->m_countOfVertices == topOrder.size()) throw std::runtime_error("Graph contains cycle. TopSort is impossible");
    return topOrder;
}

bool Graph::dfs_helper_is_cycled_undirected(std::size_t u, std::vector<bool>& visited, std::size_t parent)
{
    visited[u] = true;
    for(int v = 0; v < this->m_countOfVertices; ++v)
    {
        if(v != parent)
        {
            if(visited[v]) return parent;
            if(dfs_helper_is_cycled_undirected(v, visited, parent)) return true;
        }
    }
    return false;
}

bool Graph::dfs_helper_is_cycled_directed(std::size_t u, std::vector<bool>& visited, std::vector<bool>& refStack)
{
    visited[u] = true;
    refStack[u] = true;

    for(int v = 0; v < this->m_countOfVertices; ++v)
    {
        if(!visited[v])
        {
            if(dfs_helper_is_cycled_directed(v, visited, refStack)) return true;
        } else if(refStack[v]) return true;
    }
    refStack[u] = false;
    return false;
}

bool Graph::is_cycled_directed()
{
    std::vector<bool> visited(this->m_countOfVertices, false);
    std::vector<bool> refStack(this->m_countOfVertices, false);
    for(int u = 0; u < this->m_countOfVertices; ++u)
    {
        if(!visited[u])
        {
            if(dfs_helper_is_cycled_directed(u, visited, refStack)) return true;
        }
    }
    return false;
}

bool Graph::is_cycled_undirected()
{
    std::vector<bool> visited(this->m_countOfVertices, false);
    for(int u = 0; u < this->m_countOfVertices; ++u)
    {
        if(!visited[u])
        {
            if(dfs_helper_is_cycled_undirected(u, visited, -1)) return true;
        }
    }
    return false;
}

bool Graph::is_cycled()
{
    return this->m_isDirected ? this->is_cycled_directed() : this->is_cycled_undirected();
}