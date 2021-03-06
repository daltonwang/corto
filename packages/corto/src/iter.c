
#include "corto/corto.h"

void corto_iterMoveFirst(corto_iter* iter) {
    iter->moveFirst(iter);
}

void* corto_iterMove(corto_iter* iter, unsigned int index) {
    return iter->move(iter, index);
}

int corto_iterHasNext(corto_iter* iter) {
    if (iter->hasNext) {
        if (!iter->hasNext(iter)) {
            corto_iterRelease(iter);
            iter->hasNext = NULL;
            return 0;
        } else {
            return 1;
        }
    } else {
        return 0;
    }
}

void* corto_iterNext(corto_iter* iter) {
    return iter->next(iter);
}

void* corto_iterNextPtr(corto_iter* iter) {
    return iter->nextPtr(iter);
}

void* corto_iterRemove(corto_iter* iter) {
    return iter->remove(iter);
}

void corto_iterInsert(corto_iter* iter, void* o) {
    iter->insert(iter, o);
}

void corto_iterSet(corto_iter* iter, void* o) {
    iter->set(iter, o);
}

void corto_iterRelease(corto_iter* iter) {
    if (iter->release) {
        iter->release(iter);
        iter->release = NULL;
    }
}
