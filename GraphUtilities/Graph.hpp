#pragma once

#include <vector>

using namespace std;

typedef enum
{
	en_edgetype_tree,
	en_edgetype_cross,
	en_edgetype_back,
	en_edgetype_forward,
	en_edgetype_invalid
} edgeType_t;

typedef struct
{
	int idx_vertex;
	int distance;
	edgeType_t edge_type;
} edge_t;

typedef vector<edge_t> edgelist_t;

class Graph
{
public:
	edgelist_t* poAdjacencyVertexList;
	bool isDirected;
	bool isInitialized;
	int n;

public:
	Graph(int n, bool isDirected);
	virtual ~Graph();

	virtual void addVertex();
	virtual void deleteVertex(int idx_vertex);

	virtual bool isEdge(int idx_vertex1, int idx_vertex2);
	virtual bool isEdge(int idx_vertex1, int idx_vertex2, int distance);
	virtual bool isCyclic();
	edgeType_t getEdgeType(int idx_vertex1, int idx_vertex2);

	virtual void addEdge(int idx_vertex1, int idx_vertex2, int distance = 0);
	virtual void removeEdge(int idx_vertex1, int idx_vertex2);


	edgelist_t::const_iterator& begin();
	edgelist_t::const_iterator& end();
};


__inline Graph::Graph(int n, bool isDirected)
{
	this->isDirected = isDirected;
	this->n = n;
	if (n != 0)
		poAdjacencyVertexList = new edgelist_t[n];
}

__inline Graph::~Graph()
{
	delete[] poAdjacencyVertexList;
}


__inline void Graph::addVertex()
{
	//create new array 
	edgelist_t* poNewVertexList = new edgelist_t[n + 1];

	for (int i = 0; i < n; i++)
	{
		poNewVertexList[i] = poAdjacencyVertexList[i];
	}

	//destroy old array
	if (n != 0)
		delete[] poAdjacencyVertexList;

	poAdjacencyVertexList = poNewVertexList;
	// and adjust n
	n++;

}

__inline void Graph::deleteVertex(int idx_vertex)
{
	poAdjacencyVertexList[idx_vertex].clear();
	if (idx_vertex == n - 1)
	{
		delete &(poAdjacencyVertexList[idx_vertex]);
		n--;

	}
}

__inline bool Graph::isEdge(int idx_vertex1, int idx_vertex2)
{
	for (edgelist_t::iterator it = poAdjacencyVertexList[idx_vertex1].begin();
		it != poAdjacencyVertexList[idx_vertex1].end();
		++it)
	{
		if (it->idx_vertex == idx_vertex2)
			return true;
	}
	return false;
}

__inline bool Graph::isEdge(int idx_vertex1, int idx_vertex2, int distance)
{
	for (edgelist_t::iterator it = poAdjacencyVertexList[idx_vertex1].begin();
		it != poAdjacencyVertexList[idx_vertex1].end();
		++it)
	{
		if (it->idx_vertex == idx_vertex2 && it->distance == distance)
			return true;
	}
	return false;
}

__inline edgeType_t Graph::getEdgeType(int idx_vertex1, int idx_vertex2)
{
	for (edgelist_t::iterator it = poAdjacencyVertexList[idx_vertex1].begin();
		it != poAdjacencyVertexList[idx_vertex1].end();
		++it)
	{
		if (it->idx_vertex == idx_vertex2)
			return it->edge_type;
	}
	return en_edgetype_invalid;
}

__inline void Graph::addEdge(int idx_vertex1, int idx_vertex2, int distance)
{
	if (idx_vertex1 >= n || idx_vertex2 >= n)
		return;

	edge_t newConnection;
	newConnection.idx_vertex = idx_vertex2;
	newConnection.distance = distance;
	newConnection.edge_type = en_edgetype_invalid;

	poAdjacencyVertexList[idx_vertex1].push_back(newConnection);

	if (!isDirected)
	{
		newConnection.idx_vertex = idx_vertex1;
		newConnection.distance = distance;
		poAdjacencyVertexList[idx_vertex2].push_back(newConnection);
	}
}

__inline void Graph::removeEdge(int idx_vertex1, int idx_vertex2)
{
	for (edgelist_t::iterator it = poAdjacencyVertexList[idx_vertex1].begin();
		it != poAdjacencyVertexList[idx_vertex1].end();
		)
	{
		if (it->idx_vertex == idx_vertex2)
			it = poAdjacencyVertexList[idx_vertex1].erase(it);
		else
			++it;
	}
}

__inline bool Graph::isCyclic()
{
	if (isInitialized == false)
	{
		cout << "please run dfs first!" << endl;
		return false;
	}

	for (int idx_vertex1 = n - 1; idx_vertex1 >= 0; idx_vertex1--)
	{
		for (edgelist_t::iterator it = poAdjacencyVertexList[idx_vertex1].begin();
			it != poAdjacencyVertexList[idx_vertex1].end();
			++it )
		{
			if (it->edge_type == en_edgetype_back)
				return true;
		}
	}
	return false;
}
