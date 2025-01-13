//
// Created by Hamad on 10/1/2025.
//

#ifndef UNIONFIND_H
#define UNIONFIND_H
#include <vector>
using namespace std;
class UnionFind
{
public:
    explicit UnionFind(int n);
    int find(int x);
    void unite(int x, int y);
    int getRank(int x);
    bool isConnected(int x , int y);

private:
    vector<int> parent;
    vector<int> rank;
    void unionByRank(int rootX, int rootY);
};

UnionFind :: UnionFind(int n) : parent(n), rank(n, 0)
{
    for (int i = 0; i < n; ++i)
        parent[i] = i;
}
int UnionFind :: find(int x)
{
    if (parent[x] != x)
        parent[x] = find(parent[x]); // Path compression

    return parent[x];
}

void UnionFind :: unite(int x, int y)
{
    int rootX = find(x);
    int rootY = find(y);

    if (rootX != rootY)
        unionByRank(rootX, rootY);
}

void UnionFind :: unionByRank(int rootX, int rootY)
{
    if (rank[rootX] < rank[rootY])
        parent[rootX] = rootY;
    else
    {
        parent[rootY] = rootX;
        if (rank[rootX] == rank[rootY])
            rank[rootX]++;
    }
}

int UnionFind :: getRank(int x)
{
    return rank[x];
}

inline bool UnionFind::isConnected(int x, int y)
{
    return find(x) == find(y);
}
#endif //UNIONFIND_H
