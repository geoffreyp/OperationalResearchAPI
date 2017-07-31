#ifndef OPERATIONALRESEARCHAPI_HCFITNESSTRANSACTION_H
#define OPERATIONALRESEARCHAPI_HCFITNESSTRANSACTION_H


#include "HCBase.h"

using grpc::Server;
using grpc::ServerAsyncResponseWriter;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::ServerCompletionQueue;
using grpc::Status;
using hcfi::FitnessRequest;
using hcfi::FitnessResponse;

class HCFitnessTransaction : public HCBase{

public:
    HCFitnessTransaction(HillClimberService::AsyncService* service, ServerCompletionQueue* cq, mongocxx::database db);
    void Process() override ;

private:
    FitnessRequest request_;
    FitnessResponse reply_;
    ServerAsyncResponseWriter<FitnessResponse> responder_;

};


#endif //OPERATIONALRESEARCHAPI_HCFITNESSTRANSACTION_H
