#pragma once

#include <queue>
#include <limits>

#include "graph.hpp"

typedef struct
{
	int vertex;
	int key;
} PrimBinaryHeapNode_t;

template< typename T >
class PrimMinimumSpanningTreeMixIn : public T
{
public:
    // Prim's minimum spanning tree.
    // in:      oGraph
    // out:     pq{node,dist}
    // in:      to
    // out:     path
    virtual void primMinimumSpanningTree(Graph& oGraph, vector<int>& pred, vector<int>& prim_dist);

	class cmpless
	{
	public:
		bool operator()(PrimBinaryHeapNode_t above, PrimBinaryHeapNode_t below)
		{
			return above.key > below.key;
		}
	};
};


template <typename T>
__inline void PrimMinimumSpanningTreeMixIn<T>::primMinimumSpanningTree(Graph& oGraph, vector<int>& prim_pred, vector<int>& prim_dist)
{
	int n = oGraph.n;
	priority_queue<PrimBinaryHeapNode_t,vector<PrimBinaryHeapNode_t>,cmpless> pq;

	prim_pred.assign(n, -1);
	prim_dist.assign(n, numeric_limits<int>::max());


	////////////////decreasekeypoorimplementation/////
	PrimBinaryHeapNode_t node;
	node.key = 0;
	node.vertex = 0;
	pq.push(node);
	///////////////////////////////////////////////////

	for (int i = 1; i < oGraph.n; i++)
	{
		PrimBinaryHeapNode_t node;
		node.key = numeric_limits<int>::max();
		node.vertex = i;
		pq.push(node);
	}

	prim_dist.at(0) = 0;


	while (!pq.empty())
	{
		PrimBinaryHeapNode_t node = pq.top();
		pq.pop();



		for (vector<edge_t>::iterator it = oGraph.poAdjacencyVertexList[node.vertex].begin();
			it != oGraph.poAdjacencyVertexList[node.vertex].end();
			++it)
		{
			if (it->distance < prim_dist[it->idx_vertex])
			{
				if (prim_pred.at(node.vertex) != it->idx_vertex)
				{
					////////////////decreasekeypoorimplementation/////
					stack<PrimBinaryHeapNode_t> mystack;
					while (!pq.empty())
					{
						PrimBinaryHeapNode_t nodetemp = pq.top();
						pq.pop();
						if (nodetemp.vertex == it->idx_vertex)
						{
							nodetemp.key = it->distance;
						}
						mystack.push(nodetemp);
					}

					while (!mystack.empty())
					{
						PrimBinaryHeapNode_t nodetemp = mystack.top();
						mystack.pop();
						pq.push(nodetemp);
					}
					///////////////////////////////////////////////////

					prim_dist.at(it->idx_vertex) = it->distance;
					prim_pred.at(it->idx_vertex) = node.vertex;
				}
			}
		}
	}
}