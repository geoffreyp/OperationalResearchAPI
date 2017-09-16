#ifndef OPERATIONALRESEARCHAPI_HCINITTRANSACTION_H
#define OPERATIONALRESEARCHAPI_HCINITTRANSACTION_H


#include "HCBase.h"

using grpc::Server;
using grpc::ServerAsyncResponseWriter;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::ServerCompletionQueue;
using grpc::Status;


class HCInitTransaction : public HCBase{

public:
    HCInitTransaction(hcfi::HillClimberService::AsyncService* service, ServerCompletionQueue* cq, mongocxx::database db);
    void Process() override ;

private:
    InitTransactionRequest request_;
    GenericFitnessResponse reply_;
    ServerAsyncResponseWriter<GenericFitnessResponse> responder_;

};


#endif //OPERATIONALRESEARCHAPI_HCINITTRANSACTION_H
