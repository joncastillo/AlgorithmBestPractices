#pragma once

#include <iostream>
#include "graph.hpp"

template< class T >
class DumpGraphMixIn : public T
{
public:
    void dumpGraph(int* pred, int* dist, int n);
    void dumpGraph(vector<int>& path);
};

template <typename T>
void DumpGraphMixIn<T>::dumpGraph(int* pred, int* dist, int n)
{
    for (int j = n - 1; j > 0; j--)
    {
        int i = j;
        while (i != -1)
        {
            cout << '(' << i << ')';
            int dist_temp = dist[i];
            i = pred[i];
            if (i != -1)
                cout << " <--" << dist_temp << "-- ";
        }
        cout << endl;
    }
}

template <typename T>
void DumpGraphMixIn<T>::dumpGraph(vector<int>& path)
{
    for (vector<int>::iterator it = path.begin();
        it != path.end();
        ++it )
    {
        cout << '(' << *it << ')';
        if (it + 1 != path.end())
            cout << " ---> " ;
    }
    cout << endl;
}

