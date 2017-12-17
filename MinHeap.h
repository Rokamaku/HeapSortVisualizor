#ifndef MINHEAP_H
#define MINHEAP_H
#include "BaseHeap.h"

class MinHeap : public BaseHeap
{
protected:
    bool isFirstValBetter(int childNode, int parentNode) override;
public:
    MinHeap();
};

#endif // MINHEAP_H
