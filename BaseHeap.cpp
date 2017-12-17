#include "BaseHeap.h"
#include "HeapArrayUtility.h"

#define ROOT_POSITION 0


void BaseHeap::heapify(int newVal) {
    heapArr.push_back(newVal);
    siftUp(heapArr.size() - 1);
}

int BaseHeap::popRootVal() {
    int rootPopedVal = heapArr[ROOT_POSITION];
    moveLastNode2Root();
    siftDown(ROOT_POSITION);
    return rootPopedVal;
}

void BaseHeap::moveLastNode2Root() {
    heapArr[ROOT_POSITION] = heapArr[heapArr.size() - 1];
    heapArr.pop_back();
}

void BaseHeap::siftDown(int parentPos) {
    int leftChildPos = HeapArrayUtility::getLeftChildPos(parentPos);
    int rightChildPos = HeapArrayUtility::getRightChildPos(parentPos);

    if (HeapArrayUtility::isPosOverHeapSize(heapArr.size(), leftChildPos)
            && HeapArrayUtility::isPosOverHeapSize(heapArr.size(), rightChildPos))
        return;
    else {
        if (isFirstValBetter(heapArr[leftChildPos], heapArr[rightChildPos])
                && doesSiftNeed(heapArr[leftChildPos], heapArr[parentPos])) {
            siftDownLeftChild(leftChildPos, parentPos);
            return;
        }
        if (isFirstValBetter(heapArr[rightChildPos], heapArr[leftChildPos])
                && doesSiftNeed(heapArr[rightChildPos], heapArr[parentPos])) {
            siftDownRightChild(rightChildPos, parentPos);
            return;
        }
        if (heapArr[leftChildPos] == heapArr[rightChildPos]
                && doesSiftNeed(heapArr[leftChildPos], heapArr[parentPos])) {
            siftDownLeftChild(leftChildPos, parentPos);
            return;
        }
    }

    if (HeapArrayUtility::isPosOverHeapSize(heapArr.size(), rightChildPos)
            && !HeapArrayUtility::isPosOverHeapSize(heapArr.size(), leftChildPos)
            && doesSiftNeed(heapArr[leftChildPos], heapArr[parentPos])) {
        swapNode(parentPos, leftChildPos);
        siftDownLeftChild(leftChildPos, parentPos);
        return;
    }

    if (HeapArrayUtility::isPosOverHeapSize(heapArr.size(), leftChildPos)
            && !HeapArrayUtility::isPosOverHeapSize(heapArr.size(), rightChildPos)
            && doesSiftNeed(heapArr[rightChildPos], heapArr[parentPos])) {
        siftDownRightChild(rightChildPos, parentPos);

    }
}

void BaseHeap::siftDownLeftChild(int leftChildPos, int parentPos) {
    swapNode(parentPos, leftChildPos);
    siftDown(leftChildPos);
}

void BaseHeap::siftDownRightChild(int rightChildPos, int parentPos) {
    swapNode(parentPos, rightChildPos);
    siftDown(rightChildPos);
}

void BaseHeap::siftUp(int childPos) {
    int parentPos = HeapArrayUtility::getParentPos(childPos);
    if (!doesSiftNeed(heapArr[childPos], heapArr[parentPos])
            || childPos == ROOT_POSITION)
        return;
    swapNode(childPos, parentPos);
    siftUp(parentPos);
}

bool BaseHeap::doesSiftNeed(int childNode, int parentNode) {
    if (isFirstValBetter(childNode, parentNode))
        return true;
    return false;
}


void BaseHeap::swapNode(int firstPos, int secondPos) {
    int tmpVal = heapArr[firstPos];
    heapArr[firstPos] = heapArr[secondPos];
    heapArr[secondPos] = tmpVal;
}

BaseHeap::~BaseHeap() {
    heapArr.clear();
    heapArr.shrink_to_fit();
}
