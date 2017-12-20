#ifndef HEAPLOGGER_H
#define HEAPLOGGER_H
#include <vector>

class HeapLogger
{
private:
    int childPos;
    int parentPos;
    std::vector<int> currHeap;
public:
    HeapLogger(int, int, std::vector<int>);
    HeapLogger(std::vector<int>);
    ~HeapLogger();
    int getChildPos() { return childPos; }
    int getParentPos() { return parentPos; }
    std::vector<int> getCurrentHeap() { return currHeap; }
};

#endif // HEAPLOGGER_H
