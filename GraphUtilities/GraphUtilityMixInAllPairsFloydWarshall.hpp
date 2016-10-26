#pragma once

#include <queue>
#include <limits>

#include "graph.hpp"


template< typename T >
class FloydWarshallAllPairsMixIn : public T
{
public:
    typedef struct
    {
        int idx_vertex;
        int total_dist;
    } floydwarshall_vertex_t;

    class compare1
    {
    public:
        bool operator()(floydwarshall_vertex_t left, floydwarshall_vertex_t right)
        {
            return left.total_dist < right.total_dist;
        }
    };

    // Bellman-Ford's shortest path. Detects negative cycles.
    // in:      oGraph
    // in:      from
    // in:      to
    // out:     path
    virtual void floydWarshallShortest(Graph& oGraph, int from, int to, vector<int>& path);
};


template <typename T>
__inline void FloydWarshallAllPairsMixIn<T>::floydWarshallShortest(Graph& oGraph, int from, int to, vector<int>& path)
{

}