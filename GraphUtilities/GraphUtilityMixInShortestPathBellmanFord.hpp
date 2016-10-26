#pragma once

#include <queue>
#include <limits>

#include "graph.hpp"


template< typename T >
class BellmanFordShortestPathMixIn : public T
{
public:
    typedef struct
    {
        int idx_vertex;
        int total_dist;
    } bellmanford_vertex_t;

    class compare1
    {
    public:
        bool operator()(bellmanford_vertex_t left, bellmanford_vertex_t right)
        {
            return left.total_dist < right.total_dist;
        }
    };

    // Bellman-Ford's shortest path. Detects negative cycles.
    // in:      oGraph
    // in:      from
    // in:      to
    // out:     path
    virtual void bellmanFordShortest(Graph& oGraph, int from, int to, vector<int>& path);
};


template <typename T>
__inline void BellmanFordShortestPathMixIn<T>::bellmanFordShortest(Graph& oGraph, int from, int to, vector<int>& path)
{
	path.clear();

	// initialize dist pred
	int* dist = new int[oGraph.n];
	int* pred = new int[oGraph.n];

	std::fill(dist, dist + oGraph.n, numeric_limits<int>::max());
	std::fill(pred, pred + oGraph.n, -1);

	dist[from] = 0;
	pred[from] = -1;
	
	for (int i = 0; i <= oGraph.n; i++)
	{
		bool leaveEarly = true;

		for (int j = from; j < oGraph.n; j++)
		{
			for (vector<edge_t>::iterator it = oGraph.poAdjacencyVertexList[j].begin();
				it != oGraph.poAdjacencyVertexList[j].end();
				++it)
			{
				long int newdist = dist[j] + it->distance;
				if (newdist < dist[it->idx_vertex])
				{
					if (i == oGraph.n)
					{
						cout << "NEGATIVE CYCLE!" << endl;
						throw;
					}
					dist[it->idx_vertex] = newdist;
					pred[it->idx_vertex] = j;
					leaveEarly = false;
				}
			}
		}
		if (leaveEarly == true)
			break;
	}

	stack<int> inverse_pred;

	int i = to;

	while ((i != -1)/* && (i != from)*/)
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
    
	delete[] dist;
	delete[] pred;
}