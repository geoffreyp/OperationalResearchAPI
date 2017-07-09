#include "CallData.h"

CallData::CallData(HillClimberService::AsyncService* service, ServerCompletionQueue* cq)
: service_(service), cq_(cq), status_(PROCESS) {}

void CallData:: proceed() {
    if (status_ == PROCESS) {
        Process();
        status_ = FINISH;
    } else {
        GPR_ASSERT(status_ == FINISH);
        delete this;
    }
}