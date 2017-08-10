#include "CallData.h"

CallData::CallData(ServerCompletionQueue* cq)
: cq_(cq), status_(PROCESS) {}

void CallData:: proceed() {
    if (status_ == PROCESS) {
        Process();
        status_ = FINISH;
    } else {
        GPR_ASSERT(status_ == FINISH);
        delete this;
    }
}