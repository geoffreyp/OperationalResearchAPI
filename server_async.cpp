#include <memory>
#include <iostream>
#include <thread>

#include <grpc++/grpc++.h>
#include <grpc/support/log.h>

#include "hcfi.grpc.pb.h"

using grpc::Server;
using grpc::ServerAsyncResponseWriter;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::ServerCompletionQueue;
using grpc::Status;
using hcfi::InitTransactionRequest;
using hcfi::FitnessResponse;
using hcfi::HillClimberService;

class ServerImpl final {
public:
    ~ServerImpl() {
        server_->Shutdown();
        cq_->Shutdown();
    }


    void run() {
        std::string server_address("0.0.0.0:50051");

        ServerBuilder builder;
        builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
        builder.RegisterService(&service_);
        cq_ = builder.AddCompletionQueue();
        server_ = builder.BuildAndStart();

        std::cout << "Server listening on " << server_address << std::endl;
        handleRpcs();
    }

private:
    class CallData {
    public:
        CallData(HillClimberService::AsyncService* service, ServerCompletionQueue* cq)
                : service_(service), cq_(cq), responder_(&ctx_), status_(CREATE) {
            proceed();
        }

        void proceed() {
            if (status_ == CREATE) {
                status_ = PROCESS;
                service_->RequestInitTransaction(&ctx_, &request_, &responder_, cq_, cq_, this);
            } else if (status_ == PROCESS) {
                new CallData(service_, cq_); // Spawn a new CallData instance to serve new clients

                reply_.set_id("new_id");
                reply_.set_solution("new_solution");

                status_ = FINISH;
                responder_.Finish(reply_, Status::OK, this);
            } else {
                GPR_ASSERT(status_ == FINISH);
                delete this;  // Once in the FINISH state, deallocate actual CallData.
            }
        }

    private:
        HillClimberService::AsyncService* service_;
        ServerCompletionQueue* cq_;
        ServerContext ctx_;

        InitTransactionRequest request_; // What we get from the client.
        FitnessResponse reply_; // What we send back to the client.

        ServerAsyncResponseWriter<FitnessResponse> responder_;
        enum CallStatus { CREATE, PROCESS, FINISH };
        CallStatus status_;  // The current serving state.
    };

    // This can be run in multiple threads if needed.
    void handleRpcs() {

        new CallData(&service_, cq_.get()); // Spawn a new CallData instance to serve new clients.
        void* tag;
        bool ok;
        while (true) {
            GPR_ASSERT(cq_->Next(&tag, &ok));
            GPR_ASSERT(ok);
            static_cast<CallData*>(tag)->proceed();
        }
    }

    std::unique_ptr<ServerCompletionQueue> cq_;
    HillClimberService::AsyncService service_;
    std::unique_ptr<Server> server_;
};

int main(int argc, char** argv) {
    ServerImpl server;
    server.run();

    return 0;
}
