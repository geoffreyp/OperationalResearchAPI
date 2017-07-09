#ifndef OPERATIONALRESEARCHAPI_HCINITTRANSACTION_H
#define OPERATIONALRESEARCHAPI_HCINITTRANSACTION_H


#include "../CallData.h"

using grpc::Server;
using grpc::ServerAsyncResponseWriter;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::ServerCompletionQueue;
using grpc::Status;
using hcfi::InitTransactionRequest;
using hcfi::FitnessResponse;

class HCInitTransaction : public CallData{

public:
    HCInitTransaction(HillClimberService::AsyncService* service, ServerCompletionQueue* cq);
    void Process() override ;

private:
    ServerContext ctx_;
    InitTransactionRequest request_;
    FitnessResponse reply_;
    ServerAsyncResponseWriter<FitnessResponse> responder_;

};


#endif //OPERATIONALRESEARCHAPI_HCINITTRANSACTION_H
