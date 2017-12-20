#include "HeapLoggerTraverser.h"

HeapLoggerTraverser::HeapLoggerTraverser(std::vector<HeapLogger> buildLogger, std::vector<HeapLogger> popLogger) {
    this->logger = buildLogger;
    this->buildHeapCompletePos = buildLogger.size() - 1;
    this->logger.insert(std::end(logger), std::begin(popLogger), std::end(popLogger));
    index = 0;
}

bool HeapLoggerTraverser::hasNext() {
    if (index == logger.size() || logger.size() == 0)
        return false;
    return true;
}

bool HeapLoggerTraverser::hasPrev() {
    if (index == 0)
        return false;
    return true;
}

bool HeapLoggerTraverser::hasEndBuildHeap() {
    if (index < buildHeapCompletePos)
        return false;
    return true;
}

bool HeapLoggerTraverser::isEmpty() {
    if (logger.size() == 0)
        return true;
    return false;
}

HeapLogger HeapLoggerTraverser::next() {
    if (this->hasNext())
        return logger[index++];
}

HeapLogger HeapLoggerTraverser::prev() {
    if (this->hasPrev())
        return logger[index--];
}

HeapLogger HeapLoggerTraverser::curr() {
        return logger[index];
}

HeapLogger HeapLoggerTraverser::endBuild() {
    index = buildHeapCompletePos;
    return logger[index];

}

HeapLogger HeapLoggerTraverser::endPop() {
    index = logger.size() - 1;
    return logger[index];

}

HeapLoggerTraverser::~HeapLoggerTraverser() {
    logger.clear();
    logger.shrink_to_fit();
}
