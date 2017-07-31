//
// Created by geoffrey on 09/07/17.
//

#include "HCInitTransaction.h"
#include "../../libs/helper.h"

HCInitTransaction::HCInitTransaction(HillClimberService::AsyncService* service, ServerCompletionQueue* cq, mongocxx::database db) :
        HCBase(service, cq, db), responder_(&ctx_) {
service_->RequestInitTransaction(&ctx_, &request_, &responder_, cq_, cq_, this);
}

void HCInitTransaction::Process() {
    new HCInitTransaction(service_, cq_, db_);

    // save data in mongodb
    bsoncxx::builder::stream::document documentTransaction{};
    documentTransaction << "customer" << request_.customer();
    documentTransaction << "solution_initial" << request_.solution();
    documentTransaction << "solution_size" << request_.solutionsize();
    documentTransaction << "type" << request_.type();
    documentTransaction << "algorithm" << request_.algorithm();
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    documentTransaction << "created_at" << bsoncxx::types::b_date(now);
    bsoncxx::types::value  transactionId = transac_coll.insert_one(documentTransaction.view())->inserted_id();


    bsoncxx::builder::stream::document documentFitness{};
    documentFitness << "transaction_id" << transactionId;
    documentFitness << "solution" << request_.solution();
    documentFitness << "fitness" << request_.fitness();
    bsoncxx::types::value  fitnessId = fitness_coll.insert_one(documentFitness.view())->inserted_id();


    transac_coll.update_one(
            bsoncxx::builder::stream::document{} << "_id" << transactionId <<   bsoncxx::builder::stream::finalize,
            bsoncxx::builder::stream::document{} << "$set" <<  bsoncxx::builder::stream::open_document <<
                                                 "best_fitness_id" << fitnessId <<
                                                 bsoncxx::builder::stream::close_document <<  bsoncxx::builder::stream::finalize
    );


    // set the response
    reply_.set_id(transactionId.get_oid().value.to_string());
    reply_.set_solution(getNeighbourSolution(request_.solution()));


    responder_.Finish(reply_, Status::OK, this);
}