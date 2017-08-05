#ifndef OPERATIONALRESEARCHAPI_CALLDATA_H
#define OPERATIONALRESEARCHAPI_CALLDATA_H

#include <grpc++/grpc++.h>
#include <grpc/support/log.h>
#include "../protoClassServer/hcfi.grpc.pb.h"
#include "../protoClassServer/messages.grpc.pb.h"



using grpc::ServerContext;
using grpc::ServerCompletionQueue;
using hcfi::HillClimberService;

class CallData {
public:
    CallData(HillClimberService::AsyncService* service, ServerCompletionQueue* cq);
    virtual ~CallData() {}
    void proceed();

protected:
    virtual void Process() = 0;
    HillClimberService::AsyncService* service_;
    ServerCompletionQueue* cq_;

private:
    enum CallStatus { PROCESS, FINISH };
    CallStatus status_;
};


#endif //OPERATIONALRESEARCHAPI_CALLDATA_H
