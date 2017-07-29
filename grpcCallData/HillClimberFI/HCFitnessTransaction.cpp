#include "HCFitnessTransaction.h"

HCFitnessTransaction::HCFitnessTransaction(HillClimberService::AsyncService *service, ServerCompletionQueue *cq) :
        CallData(service, cq), responder_(&ctx_) {
service_->RequestSendFitness(&ctx_, &request_, &responder_, cq_, cq_, this);
}

void HCFitnessTransaction::Process() {
    new HCFitnessTransaction(service_, cq_);

    reply_.set_id("id test fitness");
    reply_.set_solution("sol de test fitness");

    responder_.Finish(reply_, Status::OK, this);
}