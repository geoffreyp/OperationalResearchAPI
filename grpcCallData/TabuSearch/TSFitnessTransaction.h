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
    FitnessRequest request_;
    FitnessResponse reply_;
    ServerAsyncResponseWriter<FitnessResponse> responder_;

};


#endif //OPERATIONALRESEARCHAPI_TSFITNESSTRANSACTION_H
