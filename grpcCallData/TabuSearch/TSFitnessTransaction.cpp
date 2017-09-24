#include "TSFitnessTransaction.h"
#include "../../libs/tabousearch.h"

TSFitnessTransaction::TSFitnessTransaction(ts::TabouSearchService::AsyncService *service, ServerCompletionQueue *cq,  mongocxx::database db) :
        TSBase(service, cq, db), responder_(&ctx_) {
    service_->RequestSendFitness(&ctx_, &request_, &responder_, cq_, cq_, this);
}

void TSFitnessTransaction::Process() {
    new TSFitnessTransaction(service_, cq_, db_);

    /*
     * set the response
     */

    // Test if solutions_size == fitnesses_size
    if(request_.solutions_size() != request_.fitnesses_size()){
        Status status_perso = Status(StatusCode::INVALID_ARGUMENT, "The number of solutions and the number of fitness have to be equals");
        responder_.Finish(reply_, status_perso, this);
        return;
    }

    // Find the best neighbor for this iteration
    int bestI = 0;
    double bestFitness = request_.fitnesses(0);
    for (int i = 0; i < request_.solutions_size(); ++i) {
        if(request_.fitnesses(i) < bestFitness){
            bestFitness = request_.fitnesses(i);
            bestI = i;
        }
    }
    std::cout << "best  : " << bestFitness << " for i = " << bestI << std::endl;
    reply_.set_id(request_.id());

    std::vector<std::string> neighborsOfBest = getAllNeighbors(request_.solutions(bestI));

    std::cout << "best solution : "<< request_.solutions(bestI) << std::endl;
    for (auto neighbor:neighborsOfBest){
        reply_.add_solutions(neighbor);
    }

    // todo : add the move in tabu_list

    responder_.Finish(reply_, Status::OK, this);
}