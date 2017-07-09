//
// Created by geoffrey on 09/07/17.
//

#include "HCInitTransaction.h"

HCInitTransaction::HCInitTransaction(HillClimberService::AsyncService* service, ServerCompletionQueue* cq) :
        CallData(service, cq), responder_(&ctx_) {
service_->RequestInitTransaction(&ctx_, &request_, &responder_, cq_, cq_, this);
}

void HCInitTransaction::Process() {
    new HCInitTransaction(service_, cq_);

    reply_.set_id("id tes");
    reply_.set_solution("sol de test");

    responder_.Finish(reply_, Status::OK, this);
}