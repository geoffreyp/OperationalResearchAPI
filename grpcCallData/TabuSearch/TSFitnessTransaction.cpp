#include "TSFitnessTransaction.h"
#include "../../libs/helper.h"

TSFitnessTransaction::TSFitnessTransaction(ts::TabouSearchService::AsyncService *service, ServerCompletionQueue *cq,  mongocxx::database db) :
        TSBase(service, cq, db), responder_(&ctx_) {
    service_->RequestSendFitness(&ctx_, &request_, &responder_, cq_, cq_, this);
}

void TSFitnessTransaction::Process() {
    new TSFitnessTransaction(service_, cq_, db_);

    /*
     * set the response
     */

    reply_.set_id(request_.id());
    reply_.set_solution("solution test TS fitness transaction");


    responder_.Finish(reply_, Status::OK, this);
}