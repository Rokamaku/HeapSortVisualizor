#ifndef BUILDHEAPITERATOR_H
#define BUILDHEAPITERATOR_H
#include "HeapLogger.h"

#include <vector>

class HeapLoggerTraverser
{
private:
    std::vector<HeapLogger> logger;
    int index;
    int buildHeapCompletePos;
public:
    HeapLoggerTraverser(std::vector<HeapLogger>, std::vector<HeapLogger>);
    ~HeapLoggerTraverser();
    bool hasPrev();
    bool hasNext();
    bool hasEndBuildHeap();
    bool isEmpty();
    HeapLogger next();
    HeapLogger prev();
    HeapLogger curr();
    HeapLogger endBuild();
    HeapLogger endPop();
};

#endif // BUILDHEAPITERATOR_H
