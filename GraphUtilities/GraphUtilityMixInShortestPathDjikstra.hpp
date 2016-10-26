#pragma once

#include <queue>
#include <limits>

#include "graph.hpp"


template< typename T >
class DjikstraShortestPathMixIn : public T
{
public:
    typedef struct
    {
        int idx_vertex;
        int total_dist;
    } djikstra_vertex_t;

    class compare1
    {
    public:
        bool operator()(djikstra_vertex_t left, djikstra_vertex_t right)
        {
            return left.total_dist < right.total_dist;
        }
    };

    // dJikstra's shortest path.
    // in:      oGraph
    // in:      from
    // in:      to
    // out:     path
    virtual void djikstraShortest(Graph& oGraph, int from, int to, vector<int>& path);
};


template <typename T>
__inline void DjikstraShortestPathMixIn<T>::djikstraShortest(Graph& oGraph, int from, int to, vector<int>& path)
{
    priority_queue<djikstra_vertex_t, vector<djikstra_vertex_t>, compare1> djikstra_pq;
    int* pred = new int[oGraph.n];
    int* dist = new int[oGraph.n];
    bool* isVisited = new bool[oGraph.n];

    int n = oGraph.n;

    std::fill(dist, dist + n, numeric_limits<int>::max());
    std::fill(pred, pred + n, -1);
    std::fill(isVisited, isVisited + n, false);

    djikstra_vertex_t node_0;
    node_0.total_dist = 0;
    node_0.idx_vertex = from;

    djikstra_pq.push(node_0);
    dist[from] = -1;

    while (!djikstra_pq.empty())
    {
        djikstra_vertex_t node = djikstra_pq.top();
        djikstra_pq.pop();

        for (vector<edge_t>::iterator it = oGraph.poAdjacencyVertexList[node.idx_vertex].begin();
            it != oGraph.poAdjacencyVertexList[node.idx_vertex].end();
            ++it)
        {
            int child_vertex = it->idx_vertex;
            int child_distance = it->distance;
            int current_distance = dist[node.idx_vertex];
            int total_distance = current_distance + child_distance;

            if (total_distance < dist[child_vertex])
            {
                dist[child_vertex] = total_distance;
                pred[child_vertex] = node.idx_vertex;
            }

            if (isVisited[node.idx_vertex] == false)
            {
                djikstra_vertex_t node_child;
                node_child.total_dist = total_distance;
                node_child.idx_vertex = child_vertex;
                djikstra_pq.push(node_child);
            }
        }
        isVisited[node.idx_vertex] = true;
    }
    
    stack<int> inverse_pred;
    
    int i = to;

    while ((i != -1)/* && (i != from)*/ )
    {
        inverse_pred.push(i);
        i = pred[i];
    }

    path.clear();
    while (!inverse_pred.empty())
    {
        i = inverse_pred.top();
        inverse_pred.pop();
        path.push_back(i);
    }


    delete[] isVisited;
    delete[] pred;
    delete[] dist;

}