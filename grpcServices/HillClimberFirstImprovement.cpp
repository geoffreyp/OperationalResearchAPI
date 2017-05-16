#include "HillClimberFirstImprovement.h"


HillClimberFirstImprovement::HillClimberFirstImprovement(){
    mongocxx::instance inst{};
    conn = mongocxx::uri("mongodb://mongodb:27017");
    mongocxx::database db = conn[BDD];
    transac_coll = db[TRANSACTION_COLLECTION];
    fitness_coll = db[FITNESS_COLLECTION];
}



Status HillClimberFirstImprovement::InitTransaction(ServerContext* context, const InitTransactionRequest* request,
                       FitnessResponse* reply) {

    std::string _id(generateId());

    // set the response
    reply->set_id(_id);
    reply->set_solution(getNeighbourSolution(request->solution()));

    // save data in mongodb
    bsoncxx::builder::stream::document documentTransaction{};
    documentTransaction << "transaction_id" << _id;
    documentTransaction << "customer" << request->customer();
    documentTransaction << "solution_initial" << request->solution();
    documentTransaction << "solution_size" << request->solutionsize();
    documentTransaction << "type" << request->type();


    bsoncxx::builder::stream::document documentFitness{};
    documentFitness << "transaction_id" << _id;
    documentFitness << "solution" << request->solution();
    documentFitness << "fitness" << request->fitness();
    bsoncxx::types::value  fitnessId = fitness_coll.insert_one(documentFitness.view())->inserted_id();

    documentTransaction << "best_fitness_id" << fitnessId;
    documentTransaction << "algorithm" << request->algorithm();
    transac_coll.insert_one(documentTransaction.view());

    return Status::OK;
}


Status HillClimberFirstImprovement::SendFitness(ServerContext* context, const FitnessRequest* request,
                   FitnessResponse* reply) {

    /*
     * set the response
     */
    reply->set_id(request->id());
    reply->set_solution(getNeighbourSolution(request->solution()));

    /*
     * save data in mongodb if it is a better solution (Hill Climber First Improvement)
     */
    // get the transaction
    bsoncxx::builder::stream::document documentFitnessToSearch{};
    documentFitnessToSearch << "transaction_id" << request->id() << bsoncxx::builder::stream::finalize;
    mongocxx::stdx::optional<bsoncxx::document::value> view = transac_coll.find_one(documentFitnessToSearch.view());
    if(view) {
        // get the best fitness of the transaction
        bsoncxx::document::view vtmp = *view;
        bsoncxx::document::element elt= vtmp["best_fitness_id"];
        std::string idBestFitness = elt.get_oid().value.to_string();

        auto filter = bsoncxx::builder::stream::document{} ;
        filter << "transaction_id" << request->id();

        auto docOpts = bsoncxx::builder::stream::document{};
        docOpts << "_id" << idBestFitness << bsoncxx::builder::stream::finalize;
        mongocxx::options::find opts{};
        opts.projection(docOpts.view());

        auto doc = fitness_coll.find_one(filter.view(), opts);
        auto bestFitness = doc.value().view()["fitness"].get_double().value;

        // If the new fitness is better (Case of minimization) than the actual best fitness, then we replace the solution
        if(bestFitness > request->fitness()){
            bsoncxx::builder::stream::document documentFitnessToInsert{};
            documentFitnessToInsert << "transaction_id" << request->id();
            documentFitnessToInsert << "solution" << request->solution();
            documentFitnessToInsert << "fitness" << request->fitness();

            bsoncxx::types::value  newBestFitnessId = fitness_coll.insert_one(documentFitnessToInsert.view())->inserted_id();

            transac_coll.update_one(
                    bsoncxx::builder::stream::document{} << "transaction_id" << request->id() <<   bsoncxx::builder::stream::finalize,
                    bsoncxx::builder::stream::document{} << "$set" <<  bsoncxx::builder::stream::open_document <<
                                                         "best_fitness_id" << newBestFitnessId.get_oid() <<
                                                         bsoncxx::builder::stream::close_document <<  bsoncxx::builder::stream::finalize
            );
        }

    }

    return Status::OK;
}

Status HillClimberFirstImprovement::StopTransaction(ServerContext* context, const StopRequest* request,
                       StopResponse* reply){
    if(request->message() == "done"){
        auto filterTransactionId = bsoncxx::builder::stream::document{} ;
        filterTransactionId << "transaction_id" << request->id();
        auto documentTransaction = transac_coll.find_one(filterTransactionId.view());

        bsoncxx::document::view vtmp = *documentTransaction;
        bsoncxx::document::element elt= vtmp["best_fitness_id"];
        std::string idBestFitness = elt.get_oid().value.to_string();


        auto filterId = bsoncxx::builder::stream::document{} ;
        filterId << "_id" << elt.get_oid();

        auto documentFitness = fitness_coll.find_one(filterId.view());
        bsoncxx::document::view viewFitness = *documentFitness;

        reply->set_solution(viewFitness["solution"].get_utf8().value.to_string());
        reply->set_fitness(viewFitness["fitness"].get_double());
        reply->set_id(request->id());


    }

    return Status::OK;

}
