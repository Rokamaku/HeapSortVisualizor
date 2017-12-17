#include "MaxHeap.h"

MaxHeap::MaxHeap()
{

}


bool MaxHeap::isFirstValBetter(int firstVal, int secondVal) {
    if (firstVal > secondVal)
        return true;
    return false;
}
