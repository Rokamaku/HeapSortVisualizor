#include "HeapLogger.h"

HeapLogger::HeapLogger(int childPos, int parentPos, std::vector<int> currHeap)
{
    this->childPos = childPos;
    this->parentPos = parentPos;
    this->currHeap = currHeap;
}

HeapLogger::HeapLogger(std::vector<int> currHeap) {
    this->currHeap = currHeap;
}

HeapLogger::~HeapLogger() {
    currHeap.clear();
    currHeap.shrink_to_fit();
}
