
#include "MinHeap.h"

void swap(int *, int *);

void decreaseSize(int, int **);

void increaseSize(int, int **);

void siftDown(int *, int, int);

void siftUp(int *, int);

MinHeap::MinHeap() : minHeap(NULLPTR), array_size(0), heap_size(0) {}

MinHeap::MinHeap(int n, int *data) {
    array_size = 2 * n + 1;
    heap_size = n;
    minHeap = new int[array_size];
    for (int i = 1; i <= n; ++i) {
        minHeap[i] = data[i - 1];
    }
    for (int i = (heap_size / 2); i > 0; --i)
        siftDown(minHeap, i, heap_size);
}

void siftDown(int *heap, int i, int heap_size) {
    while (2 * i < heap_size) {
        if ((heap[i] > heap[2 * i]) || (heap[i] > heap[2 * i + 1])) {
            if (heap[2 * i] < heap[2 * i + 1]) {
                swap(heap + i, heap + 2 * i);
                i = 2 * i;
            } else {
                swap(heap + i, heap + 2 * i + 1);
                i = 2 * i + 1;
            }
        } else break;
    }
    if ((2 * i == heap_size) && (heap[i] > heap[2 * i]))
        swap(heap + i, heap + 2 * i);
    return;
}

void siftUp(int *heap, int i) {
    while (i > 1) {
        if (heap[i] < heap[i / 2]) {
            swap(heap + i, heap + (i / 2));
            i = i / 2;
        } else break;
    }
}

void MinHeap::insert(int x) {
    minHeap[heap_size + 1] = x;
    heap_size++;
    if (heap_size == array_size - 1) {
        increaseSize(heap_size, &minHeap);
        array_size = 2 * heap_size + 1;
    }
    siftUp(minHeap, heap_size);
}

/**
 * Resize an array to half size.
 * @param n size of current array.
 * @param arr the array to resize.
 */
void decreaseSize(int n, int **arr) {
    int *new_size_arr = new int[n * 2 + 1];
    for (int i = 0; i < n +1 ; i++) {
        new_size_arr[i] = (*arr)[i];
    }
    delete[](*arr);
    *arr = new_size_arr;
}

/**
 * Double the size of an array.
 * @param n size of current array.
 * @param arr the array to resize.
 */
void increaseSize(int n, int **arr) {
    int *new_size_arr = new int[2 * n + 1];
    for (int i = 0; i < n + 1; i++) {
        new_size_arr[i] = (*arr)[i];
    }
    delete[](*arr);
    *arr = new_size_arr;
}


MinHeap::~MinHeap() {
    delete[](minHeap);
}

void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}


void MinHeap::decKey(int p, int x) {
    if (minHeap[p + 1] > x) {
        minHeap[p + 1] = x;
        siftUp(minHeap, p + 1);
    }
    return;
}

int MinHeap::findMIn() const {
    return minHeap[1];
}

void MinHeap::delMin() {
    swap(minHeap + 1, minHeap + heap_size);
    heap_size--;
    if(heap_size == array_size/4){
        decreaseSize(heap_size,&minHeap);
        array_size = 2*heap_size +1;
    }
    siftDown(minHeap, 1, heap_size);
}


int MinHeap::getValue(int i) {
    return this->minHeap[i];
}

int MinHeap::getHeapSize() {
    return heap_size;
}

int MinHeap::getArraySize() {
    return array_size;
}