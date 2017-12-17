#ifndef HEAPARRAYUTILITY_H
#define HEAPARRAYUTILITY_H


class HeapArrayUtility
{
private:
    HeapArrayUtility();
public:

    static bool isPosOverHeapSize(int heapSize, int position);

    static int getLeftChildPos(int parentPos);

    static int getRightChildPos(int parentPos);

    static int getParentPos(int childPos);

    static int getHeapHeight(int heapSize);
};

#endif // HEAPARRAYUTILITY_H
