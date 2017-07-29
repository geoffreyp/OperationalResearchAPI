#ifndef OPERATIONALRESEARCHAPI_HCFITNESSTRANSACTION_H
#define OPERATIONALRESEARCHAPI_HCFITNESSTRANSACTION_H


#include "../CallData.h"

using grpc::Server;
using grpc::ServerAsyncResponseWriter;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::ServerCompletionQueue;
using grpc::Status;
using hcfi::FitnessRequest;
using hcfi::FitnessResponse;

class HCFitnessTransaction : public CallData{

public:
    HCFitnessTransaction(HillClimberService::AsyncService* service, ServerCompletionQueue* cq);
    void Process() override ;

private:
    ServerContext ctx_;
    FitnessRequest request_;
    FitnessResponse reply_;
    ServerAsyncResponseWriter<FitnessResponse> responder_;

};


#endif //OPERATIONALRESEARCHAPI_HCFITNESSTRANSACTION_H
