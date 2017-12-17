#ifndef HEAPSORT_H
#define HEAPSORT_H
#include "BaseHeap.h"
#include <string>
#include <vector>

class HeapSort
{
private:
    BaseHeap* heap;
public:
    static const std::string MAX_HEAP;
    static const std::string MIN_HEAP;

    HeapSort(std::string );
    ~HeapSort();
    void buildHeap(std::vector<int> );
    std::vector<int> getSortedList();
    BaseHeap* getHeap() const { return heap; }
};

#endif // HEAPSORT_H
