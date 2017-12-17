#include "HeapSort.h"
#include "MaxHeap.h"
#include "MinHeap.h"

const std::string HeapSort::MAX_HEAP = "Max heap";
const std::string HeapSort::MIN_HEAP = "Min heap";


HeapSort::HeapSort(std::string heapType)
{
    if (heapType == HeapSort::MAX_HEAP)
        heap = new MaxHeap();
    if (heapType == HeapSort::MIN_HEAP)
        heap = new MinHeap();
}

HeapSort::~HeapSort() {
    delete heap;
}

void HeapSort::buildHeap(std::vector<int> unsortedList) {
    for (int idxList = 0; idxList < unsortedList.size(); idxList++) {
        heap->heapify(unsortedList[idxList]);
    }
    heap->setHeapSize();
    heap->cloneCurrHeap();
}

std::vector<int> HeapSort::getSortedList() {
    std::vector<int> sortedList;
    for (int idxHeap = 0; idxHeap < heap->getHeapSize(); idxHeap++) {
        sortedList.push_back(heap->popRootVal());
    }
    return sortedList;
}
