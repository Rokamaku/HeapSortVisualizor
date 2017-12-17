#ifndef MAXHEAP_H
#define MAXHEAP_H
#include "BaseHeap.h"

class MaxHeap : public BaseHeap
{
protected:
    bool isFirstValBetter(int firstVal, int secondVal) override;
public:
    MaxHeap();
};

#endif // MAXHEAP_H
