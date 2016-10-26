#pragma once

#include <queue>
#include "Graph.hpp"

using namespace std;

template< class T >
class BreadthFirstSearchMixIn : public T
{
public:
    typedef enum
    {
        en_nodecolor_white,
        en_nodecolor_black,
        en_nodecolor_grey
    } node_color_t;

    // Beadth first search
    // in:      oGraph
    // out:     pred, ensure that size >= n-1
    // out:     dist, ensure that size >= n-1
    virtual void breadthFirst(Graph& oGraph, int* pred, int* dist);
};

template <typename T>
__inline void BreadthFirstSearchMixIn<T>::breadthFirst(Graph& oGraph, int* pred, int* dist)
{
    queue<int> bfs_queue;
    int n = oGraph.n;


    node_color_t* poNodecolors = new node_color_t[n];
    std::fill(poNodecolors, poNodecolors + n, en_nodecolor_white);
    bfs_queue.push(0);
    pred[0] = -1;
    dist[0] = 0;
    poNodecolors[0] = en_nodecolor_grey;

    while (!bfs_queue.empty())
    {
        int parent = bfs_queue.front();
        bfs_queue.pop();

        for (
            edgelist_t::iterator it = oGraph.poAdjacencyVertexList[parent].begin();
            it != oGraph.poAdjacencyVertexList[parent].end();
            ++it)
        {
            int child = it->idx_vertex;
            int child_dist = it->distance;

            if (poNodecolors[it->idx_vertex] == en_nodecolor_white)
            {
                bfs_queue.push(child);
                pred[child] = parent;
                dist[child] = child_dist;
                poNodecolors[child] = en_nodecolor_grey;
            }
        }
        poNodecolors[parent] = en_nodecolor_black;
    }
}
