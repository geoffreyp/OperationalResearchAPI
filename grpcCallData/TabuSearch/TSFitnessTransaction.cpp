#include "TSFitnessTransaction.h"
#include "../../libs/tabousearch.h"

TSFitnessTransaction::TSFitnessTransaction(ts::TabouSearchService::AsyncService *service, ServerCompletionQueue *cq,  mongocxx::database db) :
        TSBase(service, cq, db), responder_(&ctx_) {
    service_->RequestSendFitness(&ctx_, &request_, &responder_, cq_, cq_, this);
}

void TSFitnessTransaction::Process() {
    new TSFitnessTransaction(service_, cq_, db_);

    // Test if solutions_size == fitnesses_size
    if(request_.solutions_size() != request_.fitnesses_size()){
        Status status_perso = Status(StatusCode::INVALID_ARGUMENT, "The number of solutions and the number of fitness have to be equals");
        responder_.Finish(reply_, status_perso, this);
        return;
    }

    // Find the best neighbor for this iteration
    int bestI = 0;
    double bestFitnessLocal = request_.fitnesses(0);
    for (int i = 0; i < request_.solutions_size(); ++i) {
        if(request_.fitnesses(i) < bestFitnessLocal){
            bestFitnessLocal = request_.fitnesses(i);
            bestI = i;
        }
    }

    // if it is the best solution for the current transaction, replace it in database
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


        // If the new fitness is better (Case of minimization) than the actual best fitness, then we replace the solution
        if (bestFitness > bestFitnessLocal) {
            std::cout << "best global : " << bestFitness << std::endl;
            std::cout << "best local  : " << bestFitnessLocal << std::endl;

            bsoncxx::builder::stream::document documentFitnessToInsert{};
            documentFitnessToInsert << "transaction_id" << request_.id();
            documentFitnessToInsert << "solution" << request_.solutions(bestI);
            documentFitnessToInsert << "fitness" << bestFitnessLocal;


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
    }


    /*
     * set the response
     */
    reply_.set_id(request_.id());

    std::vector<std::string> neighborsOfBest = getAllNeighbors(request_.solutions(bestI));

    for (auto neighbor:neighborsOfBest){
        reply_.add_solutions(neighbor);
    }

    // todo : add the move in tabu_list

    responder_.Finish(reply_, Status::OK, this);
}