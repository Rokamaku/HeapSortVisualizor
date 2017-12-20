#ifndef BASEHEAP_H
#define BASEHEAP_H
#include <vector>
#include "HeapLogger.h"

class BaseHeap
{
protected:
    std::vector<int> heapArr;
    std::vector<int> cloneHeap;
    std::vector<HeapLogger> buildLogger;
    std::vector<HeapLogger> popLogger;
    int heapSize;

    virtual bool isFirstValBetter(int firstVal, int secondVal) = 0;

    bool doesSiftNeed(int childNode, int parentNode);
    void siftUp(int childPos);
    void siftDown(int parentPos);
    void siftDownLeftChild(int leftChildPos, int parentPos);
    void siftDownRightChild(int rightChildPos, int parentPos);

    void swapNode(int firstPos, int secondPos);
    void moveLastNode2Root();

public:
    ~BaseHeap();
    void heapify(int );
    int popRootVal();
    int getHeapSize() { return heapSize; }
    std::vector<int> getHeapArr() const { return cloneHeap; }
    std::vector<HeapLogger> getBuildLogger() { return buildLogger; }
    std::vector<HeapLogger> getPopLogger() { return popLogger; }

    void setHeapSize() { this->heapSize = heapArr.size(); }

    void cloneCurrHeap() { cloneHeap = heapArr; }

};

#endif // BASEHEAP_H
