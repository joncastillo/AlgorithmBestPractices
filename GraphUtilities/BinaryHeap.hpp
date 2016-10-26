#pragma once

#include <vector>

using namespace std;

template <typename T>
class binaryheap
{
private:
    vector<T> heap;
public:

    binaryheap() {};
    void buildHeap(){};
    void insertelement();
    void heapify();
};

