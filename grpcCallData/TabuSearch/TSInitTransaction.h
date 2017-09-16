#ifndef OPERATIONALRESEARCHAPI_TSINITTRANSACTION_H
#define OPERATIONALRESEARCHAPI_TSINITTRANSACTION_H


#include "TSBase.h"

using grpc::Server;
using grpc::ServerAsyncResponseWriter;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::ServerCompletionQueue;
using grpc::Status;


class TSInitTransaction : public TSBase{

public:
    TSInitTransaction(ts::TabouSearchService::AsyncService* service, ServerCompletionQueue* cq, mongocxx::database db);
    void Process() override ;

private:
    InitTransactionRequest request_;
    GenericFitnessResponse reply_;
    ServerAsyncResponseWriter<GenericFitnessResponse> responder_;

};


#endif //OPERATIONALRESEARCHAPI_HCINITTRANSACTION_H
