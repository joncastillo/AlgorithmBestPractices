// ConsoleApplication4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

#include "GraphUtility.hpp"


#include <thread>
#include <mutex>

using namespace std;

std::mutex mymutex;


void thread1()
{
	std::lock_guard<std::mutex>(mymutex);

}

int _tmain(int argc, _TCHAR* argv[])
{
	//////////////////////////
	//
    //            (0)
    //          2/   \3
    //         |/_ 1 _\|
    //        (1)<----(2)
    //         |\     /|
    //         | \3 6/ |
	//         |  \ /  |
    //        4|   X   |7
	//         |  / \  |
    //         | /   \ |
    //        \|/_   _\|/
    //        (3)<----(4)
    //          \1   2/
    //          _\   /_ 
    //            (5)
	//
	//////////////////////////

    Graph newGraph(0, true);
    newGraph.addVertex();
    newGraph.addVertex();
    newGraph.addVertex();
    newGraph.addVertex();
    newGraph.addVertex();
	newGraph.addVertex();

    newGraph.addEdge(0, 1, 2);
    newGraph.addEdge(0, 2, 3);
    newGraph.addEdge(1, 3, 4);
    newGraph.addEdge(1, 4, 2);
    newGraph.addEdge(2, 3, 6);
    newGraph.addEdge(2, 4, 7);
    newGraph.addEdge(2, 1, 1);
    newGraph.addEdge(4, 5, 2);
    newGraph.addEdge(3, 5, 1);
	newGraph.addEdge(4, 3, 1);
	newGraph.addEdge(5, 0, 4); // back, enable for cyclic graph

    int size = newGraph.n;

	//////////////////////////
    int* dfs_pred = new int[size];
	int* dfs_dist = new int[size];

    GraphUtility::getInstance().depthFirst(newGraph, dfs_pred, dfs_dist);
	cout << "DFS results:" << endl;
	GraphUtility::getInstance().dumpGraph(dfs_pred, dfs_dist, size);
  	cout << (newGraph.isCyclic()?"Cyclic!":"Not Cyclic.") << endl;
    cout << endl;

	delete[] dfs_pred;
	delete[] dfs_dist;
	//////////////////////////
    int* bfs_pred = new int[size];
    int* bfs_dist = new int[size];

    GraphUtility::getInstance().breadthFirst(newGraph, bfs_pred, bfs_dist);
    cout << "BFS results:" << endl;
    GraphUtility::getInstance().dumpGraph(bfs_pred, bfs_dist, size);
    cout << endl;

	delete[] bfs_pred;
	delete[] bfs_dist;
    //////////////////////////
    vector<int> shortestPath;
	cout << "Djikstra results:" << endl;
    GraphUtility::getInstance().djikstraShortest(newGraph, 0, 5, shortestPath);
    GraphUtility::getInstance().dumpGraph(shortestPath);
    GraphUtility::getInstance().djikstraShortest(newGraph, 1, 5, shortestPath);
    GraphUtility::getInstance().dumpGraph(shortestPath);
    GraphUtility::getInstance().djikstraShortest(newGraph, 2, 5, shortestPath);
    GraphUtility::getInstance().dumpGraph(shortestPath);
    GraphUtility::getInstance().djikstraShortest(newGraph, 3, 5, shortestPath);
    GraphUtility::getInstance().dumpGraph(shortestPath);
    GraphUtility::getInstance().djikstraShortest(newGraph, 4, 5, shortestPath);
    GraphUtility::getInstance().dumpGraph(shortestPath);
    GraphUtility::getInstance().djikstraShortest(newGraph, 5, 5, shortestPath);
    GraphUtility::getInstance().dumpGraph(shortestPath);
	cout << endl;

	cout << "BellmanFord results:" << endl;
	//	newGraph.addEdge(5, 1, -5); // back, enable for negative cycle (will crash djikstra)
	GraphUtility::getInstance().bellmanFordShortest(newGraph, 0, 5, shortestPath);
	GraphUtility::getInstance().dumpGraph(shortestPath);

	// undirected big graph
#if 0
	int* prim_pred = new int[size];
	int* prim_dist = new int[size];
#else
	vector<int> prim_pred;
	vector<int> prim_dist;
#endif
	
	Graph bigGraph(9, false);
	bigGraph.addEdge(0, 2, 1);
	bigGraph.addEdge(1, 2, 1);
	bigGraph.addEdge(1, 4, 3);
	bigGraph.addEdge(1, 5, 1);
	bigGraph.addEdge(2, 3, 3);
	bigGraph.addEdge(2, 6, 3);
	bigGraph.addEdge(2, 5, 3);
	bigGraph.addEdge(3, 6, 1);
	bigGraph.addEdge(3, 7, 1);
	bigGraph.addEdge(5, 4, 3);
	bigGraph.addEdge(5, 6, 1);
	bigGraph.addEdge(4, 8, 1);
	bigGraph.addEdge(6, 8, 3);
	bigGraph.addEdge(6, 7, 3);
	bigGraph.addEdge(7, 8, 1);

	GraphUtility::getInstance().primMinimumSpanningTree(bigGraph, prim_pred, prim_dist);








    return 0;
}


