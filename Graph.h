//
// Created by Hamad on 27/12/2024.
//

#ifndef GRAPH_H
#define GRAPH_H
#include <algorithm>
#include <queue>
#include <utility>
#include <vector>
#include "UnionFind.h"
using namespace std;
typedef pair<int, int> costToNode_t;
typedef pair<int, int> edge_t;
typedef vector<vector<costToNode_t>> adjacencyList_t;
typedef vector<pair<int,edge_t>> weightedEdgesList_t;

class Graph
{
public:
    static int MSTCost(const weightedEdgesList_t &graph, int numberOfNodes);
    static int MSTCost(int startNode, const adjacencyList_t &graph);
    static int findShortestPath(int startNode , const adjacencyList_t &graph );
    static int findShortestPath(int startNode , vector<vector<int> > &input, int n);

private:
    static adjacencyList_t buildAdjacencyListGraph(vector<vector<int> > &input, int n);
    static int prim(int startNode, const adjacencyList_t &graph);
    static int dijkstra(int start, const vector<vector<pair<int, int>>> &graph);
    static int kruskal(const weightedEdgesList_t &graph, int numberOfNodes);
};

/////////////////////////////////////////////////////////////////////////////////////////

int Graph:: MSTCost(const weightedEdgesList_t &graph, const int numberOfNodes)
{
    return kruskal(graph, numberOfNodes);
}

int Graph:: MSTCost(const int startNode, const adjacencyList_t &graph)
{
    return prim(startNode, graph);
}

inline int Graph::findShortestPath(int startNode, const adjacencyList_t &graph)
{
    return dijkstra(startNode,graph);
}

inline int Graph::findShortestPath(int startNode, vector<vector<int>> &input, int n)
{
    return dijkstra(startNode,buildAdjacencyListGraph(input,n));
}

//////////////////////////////////////////////////////////////////////////////////////////

adjacencyList_t Graph:: buildAdjacencyListGraph(vector<vector<int> > &input, int n)
{
    adjacencyList_t graph(n + 1);
    for (const auto &element: input)
    {
        int src = element.at(0);
        int dst = element.at(1);
        int cost = element.at(2);
        graph[src].emplace_back(dst, cost); // Correctly store as {neighbor, weight}
    }
    return graph;
}

int Graph:: prim(int startNode, const adjacencyList_t &graph)
{
    priority_queue<costToNode_t, vector<costToNode_t>, greater<> > pq; // Min-heap for {cost, node}
    pq.emplace(0, startNode);

    vector<bool> added(graph.size(), false); // To check if a node is added to MST
    int mstCost = 0;

    while (!pq.empty())
    {
        // Select the item <cost, node> with minimum cost
        auto [currentCost , currentNode] = pq.top();
        pq.pop();

        // If the node is already added, skip it
        if (added[currentNode])
            continue;

        mstCost += currentCost; // Add cost to MST
        added[currentNode] = true; // Mark node as added

        // Add all adjacent nodes to the priority queue
        for (const auto &[adjCost , adjNode]: graph[currentNode])
        {
            if (!added[adjNode])
                pq.emplace(adjCost, adjNode);
        }
    }

    return mstCost;
}

int Graph:: dijkstra(int start, const vector<vector<pair<int, int> > > &graph)
{
    vector<int> dist(graph.size(), INT_MAX);
    dist[start] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<> > pq;
    pq.emplace(0, start);

    while (!pq.empty())
    {
        auto [current_dist, current_node] = pq.top();
        pq.pop();

        if (current_dist > dist[current_node])
            continue;

        for (const auto &[neighbor, weight]: graph[current_node])
        {
            if (dist[current_node] + weight < dist[neighbor])
            {
                dist[neighbor] = dist[current_node] + weight;
                pq.emplace(dist[neighbor], neighbor);
            }
        }
    }

    // Find the maximum distance
    int maxDistance = *max_element(dist.begin() + 1, dist.end()); // Exclude index 0
    return maxDistance == INT_MAX ? -1 : maxDistance; // Return -1 if any node is unreachable
}

int Graph:: kruskal(const weightedEdgesList_t &graph, const int numberOfNodes)
{
    sort(graph.begin(), graph.end());
    UnionFind uf(numberOfNodes + 1);
    int mstCost = 0;
    for (const auto &[cost , endPoints]: graph)
    {
        auto [u , v] = endPoints;
        if (!uf.isConnected(u, v))
        {
            uf.unite(u, v);
            mstCost += cost;
        }
    }
    return mstCost;
}
#endif