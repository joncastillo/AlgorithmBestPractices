#pragma once

#include <stack>

#include "graph.hpp"

template< class T >
class DepthFirstSearchMixIn : public T
{
public:
    typedef enum
    {
        en_nodecolor_white,
        en_nodecolor_black,
        en_nodecolor_grey
    } node_color_t;

    typedef struct
    {
        int parentnode;
        stack<int> children;
    } DFS_substack;

    typedef stack<DFS_substack> DfsStack;

    // Depth first search, also updates oGraph's EdgeTypeList
    // in/Out:  oGraph
    // Out:     pred, ensure that size >= n-1
    // Out:     dist, ensure that size >= n-1
    virtual void depthFirst(Graph& oGraph, int* pred, int* dist);
};

template <typename T>
__inline void DepthFirstSearchMixIn<T>::depthFirst(Graph& oGraph, int* pred, int* dist)
{
    int n = oGraph.n;

    node_color_t* poNodecolors = new node_color_t[n];
    std::fill(poNodecolors, poNodecolors + n, en_nodecolor_white);

    DfsStack oDfsStack;

    // starting point:
    pred[0] = -1;
    dist[0] = 0;
    DFS_substack node_0;
    node_0.parentnode = 0;
    oDfsStack.push(node_0);

    while (!oDfsStack.empty())
    {
        DFS_substack& substack = oDfsStack.top();
        int parent = substack.parentnode;

        // each child of vertex in adjacency list:
        if (poNodecolors[parent] == en_nodecolor_white)
        {
            for (
                edgelist_t::reverse_iterator it = oGraph.poAdjacencyVertexList[parent].rbegin();
                it != oGraph.poAdjacencyVertexList[parent].rend();
            ++it)
            {
                if (poNodecolors[it->idx_vertex] == en_nodecolor_white)
                {
                    it->edge_type = en_edgetype_tree;
                    pred[it->idx_vertex] = parent;
                    dist[it->idx_vertex] = it->distance;
                    substack.children.push(it->idx_vertex);
                }
                else if (poNodecolors[it->idx_vertex] == en_nodecolor_grey)
                {
                    it->edge_type = en_edgetype_back;
                }
                else if (poNodecolors[it->idx_vertex] == en_nodecolor_black)
                {
                    if (it->idx_vertex <= parent)
                        it->edge_type = en_edgetype_cross;
                    else
                        it->edge_type = en_edgetype_forward;
                }
                else
                {
                    it->edge_type = en_edgetype_invalid;
                }
            }
            poNodecolors[parent] = en_nodecolor_grey;
        }

        if (!substack.children.empty())
        {
            int child_vertex = substack.children.top();
            substack.children.pop();
            DFS_substack node_child;
            node_child.parentnode = child_vertex;
            oDfsStack.push(node_child);
        }
        else
        {
            parent = substack.parentnode;
            poNodecolors[parent] = en_nodecolor_black;
            oDfsStack.pop();
        }
    }

    delete[] poNodecolors;
    oGraph.isInitialized = true;
}
