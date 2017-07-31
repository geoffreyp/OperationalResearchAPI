#ifndef OPERATIONALRESEARCHAPI_HCSTOPTRANSACTION_H
#define OPERATIONALRESEARCHAPI_HCSTOPTRANSACTION_H


#include "HCBase.h"

using grpc::Server;
using grpc::ServerAsyncResponseWriter;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::ServerCompletionQueue;
using grpc::Status;
using hcfi::StopRequest;
using hcfi::StopResponse;

class HCStopTransaction : public HCBase{

public:
    HCStopTransaction(HillClimberService::AsyncService* service, ServerCompletionQueue* cq, mongocxx::database db);
    void Process() override ;

private:
    StopRequest request_;
    StopResponse reply_;
    ServerAsyncResponseWriter<StopResponse> responder_;

};


#endif //OPERATIONALRESEARCHAPI_HCSTOPTRANSACTION_H
