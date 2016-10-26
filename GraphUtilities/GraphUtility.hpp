#pragma once


//#include "Graph.hpp"
#include "GraphUtilityMixinDumpGraph.hpp"
#include "GraphUtilityMixinSearchDepthFirst.hpp"
#include "GraphUtilityMixinSearchBreadthFirst.hpp"
#include "GraphUtilityMixInShortestPathDjikstra.hpp"
#include "GraphUtilityMixInShortestPathBellmanFord.hpp"
#include "GraphUtilityMixInAllPairsFloydWarshall.hpp"
#include "GraphUtilityMixInMinimumSpanningPrim.hpp"

using namespace std;

class MixinBase
{
};


template< class T >
class GraphUtilityMixIn : public T
{
public:
    static GraphUtilityMixIn& getInstance()
	{
        static GraphUtilityMixIn singleton;
		return singleton;
	}

private:
    GraphUtilityMixIn() {};
};

typedef GraphUtilityMixIn<
    DumpGraphMixIn<
    DepthFirstSearchMixIn<
    BreadthFirstSearchMixIn<
    DjikstraShortestPathMixIn<
	BellmanFordShortestPathMixIn<
	FloydWarshallAllPairsMixIn<
    PrimMinimumSpanningTreeMixIn<
    MixinBase>>>>>>>> GraphUtility;


