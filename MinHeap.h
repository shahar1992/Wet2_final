//
// Created by edri6 on 05/01/2018.
//

#ifndef WET2_FINAL_MINHEAP_H
#define WET2_FINAL_MINHEAP_H

#include <iostream>
#include <functional>
#include <new>

#define NULLPTR 0

class MinHeap {
    int *minHeap;
    int array_size; //number of cells in the array (used and unused).
    int heap_size; //number of elements in the heap.
public:
    MinHeap();

    MinHeap(int n, int* data);

    void insert(int x);

    void decKey(int p, int x);

    int findMIn() const;

    void delMin();

    ~MinHeap();

    //dont forget tyo delete!!!!
    int getValue(int i);
    int getHeapSize();
    int getArraySize();

};


#endif //WET2_FINAL_MINHEAP_H
