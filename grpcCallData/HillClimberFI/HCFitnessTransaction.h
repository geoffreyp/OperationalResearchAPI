#ifndef OPERATIONALRESEARCHAPI_HCFITNESSTRANSACTION_H
#define OPERATIONALRESEARCHAPI_HCFITNESSTRANSACTION_H


#include "HCBase.h"

using grpc::Server;
using grpc::ServerAsyncResponseWriter;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::ServerCompletionQueue;
using grpc::Status;

class HCFitnessTransaction : public HCBase{

public:
    HCFitnessTransaction(hcfi::HillClimberService::AsyncService* service, ServerCompletionQueue* cq, mongocxx::database db);
    void Process() override ;

private:
    GenericFitnessRequest request_;
    GenericFitnessResponse reply_;
    ServerAsyncResponseWriter<GenericFitnessResponse> responder_;

};


#endif //OPERATIONALRESEARCHAPI_HCFITNESSTRANSACTION_H
