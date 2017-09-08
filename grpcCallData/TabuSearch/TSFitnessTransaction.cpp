#include "TSFitnessTransaction.h"
#include "../../libs/helper.h"

TSFitnessTransaction::TSFitnessTransaction(ts::TabouSearchService::AsyncService *service, ServerCompletionQueue *cq,  mongocxx::database db) :
        TSBase(service, cq, db), responder_(&ctx_) {
    service_->RequestSendFitness(&ctx_, &request_, &responder_, cq_, cq_, this);
}

void TSFitnessTransaction::Process() {
    new TSFitnessTransaction(service_, cq_, db_);

    /*
     * Pseudo Code from wikipedia : https://en.wikipedia.org/wiki/Tabu_search
     *
  sBest ← s0
  tabuList ← []
  tabuList.push(s0)
  while (not stoppingCondition())
  	sNeighborhood ← getNeighbors(bestCandidate)
  	bestCandidate ← sNeighborHood.firstElement
  	for (sCandidate in sNeighborhood)
  		if ( (not tabuList.contains(sCandidate)) and (fitness(sCandidate) > fitness(bestCandidate)) )
  			bestCandidate ← sCandidate
 		end
 	end
 	if (fitness(bestCandidate) > fitness(sBest))
 		sBest ← bestCandidate
 	end
 	tabuList.push(bestCandidate)
 	if (tabuList.size > maxTabuSize)
 		tabuList.removeFirst()
 	end
 end
 return sBest
     */



    /*
     * set the response
     */

    reply_.set_id(request_.id());
    reply_.set_solution(getNeighbourSolution(request_.solution()));

    responder_.Finish(reply_, Status::OK, this);
}