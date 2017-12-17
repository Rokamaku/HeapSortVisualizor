#include "HeapArrayUtility.h"
#include <math.h>

HeapArrayUtility::HeapArrayUtility()
{

}


bool HeapArrayUtility::isPosOverHeapSize(int heapSize, int position) {
    if (position >= heapSize)
        return true;
    return false;
}

int HeapArrayUtility::getLeftChildPos(int parentPos) {
    return parentPos * 2 + 1;
}

int HeapArrayUtility::getRightChildPos(int parentPos) {
    return parentPos * 2 + 2;
}

int HeapArrayUtility::getParentPos(int childPos) {
    int parentPos;
    if (childPos % 2 == 0)
        parentPos = (childPos - 2) / 2;
    else
        parentPos = (childPos - 1) / 2;
    return parentPos;
}

int HeapArrayUtility::getHeapHeight(int heapSize) {
    return floor(std::log2(heapSize)) + 1;
}
