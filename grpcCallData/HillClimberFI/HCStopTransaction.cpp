#include "HCStopTransaction.h"


HCStopTransaction::HCStopTransaction(HillClimberService::AsyncService* service, ServerCompletionQueue* cq) :
        CallData(service, cq), responder_(&ctx_) {
    service_->RequestStopTransaction(&ctx_, &request_, &responder_, cq_, cq_, this);
}

void HCStopTransaction::Process() {
    new HCStopTransaction(service_, cq_);

    reply_.set_id("id tes");
    reply_.set_solution("sol de test final");

    responder_.Finish(reply_, Status::OK, this);

}