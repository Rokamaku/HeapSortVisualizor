#include "MinHeap.h"

MinHeap::MinHeap()
{

}

bool MinHeap::isFirstValBetter(int fistVal, int secondVal) {
    if (fistVal < secondVal)
        return true;
    return false;
}
