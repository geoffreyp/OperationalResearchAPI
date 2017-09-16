#ifndef OPERATIONALRESEARCHAPI_TSFITNESSTRANSACTION_H
#define OPERATIONALRESEARCHAPI_TSFITNESSTRANSACTION_H


#include "TSBase.h"

using grpc::Server;
using grpc::ServerAsyncResponseWriter;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::ServerCompletionQueue;
using grpc::Status;

class TSFitnessTransaction : public TSBase{

public:
    TSFitnessTransaction(ts::TabouSearchService::AsyncService* service, ServerCompletionQueue* cq, mongocxx::database db);
    void Process() override ;

private:
    GenericFitnessRequest request_;
    GenericFitnessResponse reply_;
    ServerAsyncResponseWriter<GenericFitnessResponse> responder_;

};


#endif //OPERATIONALRESEARCHAPI_TSFITNESSTRANSACTION_H
