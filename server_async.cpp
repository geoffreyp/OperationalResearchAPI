#include <memory>
#include <iostream>
#include <thread>

#include "grpcCallData/HCInitTransaction.h"

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

    // This can be run in multiple threads if needed.
    void handleRpcs() {

        new HCInitTransaction(&service_, cq_.get()); // Spawn a new CallData instance to serve new clients.
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
