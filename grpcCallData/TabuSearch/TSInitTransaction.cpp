#include "TSInitTransaction.h"

TSInitTransaction::TSInitTransaction(ts::TabouSearchService::AsyncService* service, ServerCompletionQueue* cq, mongocxx::database db) :
        TSBase(service, cq, db), responder_(&ctx_) {
service_->RequestInitTransaction(&ctx_, &request_, &responder_, cq_, cq_, this);
}

void TSInitTransaction::Process() {
    new TSInitTransaction(service_, cq_, db_);



    // set the response
    reply_.set_id("id test tabou search init");
    reply_.set_solution("solution test tabou search init");


    responder_.Finish(reply_, Status::OK, this);
}