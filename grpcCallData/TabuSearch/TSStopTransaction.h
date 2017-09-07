#ifndef OPERATIONALRESEARCHAPI_TSSTOPTRANSACTION_H
#define OPERATIONALRESEARCHAPI_TSSTOPTRANSACTION_H


#include "TSBase.h"

using grpc::Server;
using grpc::ServerAsyncResponseWriter;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::ServerCompletionQueue;
using grpc::Status;


class TSStopTransaction : public TSBase{

public:
    TSStopTransaction(ts::TabouSearchService::AsyncService* service, ServerCompletionQueue* cq, mongocxx::database db);
    void Process() override ;

private:
    StopRequest request_;
    StopResponse reply_;
    ServerAsyncResponseWriter<StopResponse> responder_;

};


#endif //OPERATIONALRESEARCHAPI_TSSTOPTRANSACTION_H
