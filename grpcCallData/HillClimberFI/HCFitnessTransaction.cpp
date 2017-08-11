#include "HCFitnessTransaction.h"
#include "../../libs/helper.h"

HCFitnessTransaction::HCFitnessTransaction(hcfi::HillClimberService::AsyncService *service, ServerCompletionQueue *cq,  mongocxx::database db) :
        HCBase(service, cq, db), responder_(&ctx_) {
    service_->RequestSendFitness(&ctx_, &request_, &responder_, cq_, cq_, this);
}

void HCFitnessTransaction::Process() {
    new HCFitnessTransaction(service_, cq_, db_);
    
    /*
     * save data in mongodb if it is a better solution (Hill Climber First Improvement with minimisation)
     */
    // get the transaction
    auto filterTransactionToSearch = bsoncxx::builder::stream::document{} ;
    filterTransactionToSearch << "_id" << bsoncxx::oid(request_.id());

    mongocxx::stdx::optional<bsoncxx::document::value> view = transac_coll.find_one(filterTransactionToSearch.view());

    if(view) {
        // get the best fitness of the transaction
        bsoncxx::document::view viewFitnessToSearch = *view;
        bsoncxx::document::element eltBestFitnessId = viewFitnessToSearch["best_fitness_id"];

        auto filterFitnessToSearch = bsoncxx::builder::stream::document{};
        filterFitnessToSearch << "_id" << eltBestFitnessId.get_oid();

        auto docFitnessFindOne = fitness_coll.find_one(filterFitnessToSearch.view());
        auto bestFitness = docFitnessFindOne.value().view()["fitness"].get_double().value;

        auto bestSolution = docFitnessFindOne.value().view()["solution"].get_utf8().value.to_string();


        // If the new fitness is better (Case of minimization) than the actual best fitness, then we replace the solution
        if (bestFitness > request_.fitness()) {


            bsoncxx::builder::stream::document documentFitnessToInsert{};
            documentFitnessToInsert << "transaction_id" << request_.id();
            documentFitnessToInsert << "solution" << request_.solution();
            documentFitnessToInsert << "fitness" << request_.fitness();

            bestSolution = request_.solution();
            bsoncxx::types::value newBestFitnessId = fitness_coll.insert_one(
                    documentFitnessToInsert.view())->inserted_id();

            transac_coll.update_one(
                    bsoncxx::builder::stream::document{} << "_id" << bsoncxx::oid(request_.id())
                                                         << bsoncxx::builder::stream::finalize,
                    bsoncxx::builder::stream::document{} << "$set" << bsoncxx::builder::stream::open_document <<
                                                         "best_fitness_id" << newBestFitnessId.get_oid() <<
                                                         bsoncxx::builder::stream::close_document
                                                         << bsoncxx::builder::stream::finalize
            );
        }

        /*
         * set the response
         */

        reply_.set_id(request_.id());
        reply_.set_solution(getNeighbourSolution(bestSolution));
    }

    responder_.Finish(reply_, Status::OK, this);
}