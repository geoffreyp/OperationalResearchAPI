#include "HCStopTransaction.h"


HCStopTransaction::HCStopTransaction(hcfi::HillClimberService::AsyncService* service, ServerCompletionQueue* cq, mongocxx::database db) :
        HCBase(service, cq, db), responder_(&ctx_) {
    service_->RequestStopTransaction(&ctx_, &request_, &responder_, cq_, cq_, this);
}

void HCStopTransaction::Process() {
    new HCStopTransaction(service_, cq_, db_);

    if(request_.message() == "done"){
        auto filterTransactionId = bsoncxx::builder::stream::document{} ;
        filterTransactionId << "_id" <<  bsoncxx::oid(request_.id());

        auto documentTransaction = transac_coll.find_one(filterTransactionId.view());

        bsoncxx::document::view vtmp = *documentTransaction;
        bsoncxx::document::element elt= vtmp["best_fitness_id"];
        std::string idBestFitness = elt.get_oid().value.to_string();

        auto filterId = bsoncxx::builder::stream::document{} ;
        filterId << "_id" << elt.get_oid();

        auto documentFitness = fitness_coll.find_one(filterId.view());
        bsoncxx::document::view viewFitness = *documentFitness;


        reply_.set_id(request_.id());
        reply_.set_solution(viewFitness["solution"].get_utf8().value.to_string());
        reply_.set_fitness(viewFitness["fitness"].get_double());

    }


    responder_.Finish(reply_, Status::OK, this);

}