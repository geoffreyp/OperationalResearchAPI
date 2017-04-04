#include <iostream>
#include <memory>
#include <string>

#include <grpc++/grpc++.h>

#ifdef BAZEL_BUILD
#include "protos/api.proto"
#else
#include "protoClassServer/api.grpc.pb.h"
#endif

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using api::InitRequest;
using api::FitnessResponse;
using api::FitnessRequest;
using api::StopRequest;
using api::StopResponse;


class ORServiceImpl final : public api::OperationalResearch::Service {
    Status InitConversation(ServerContext* context, const InitRequest* request,
                    FitnessResponse* reply) override {
        std::string prefix("Hello ");
        reply->set_id("Z5E2EZ5A1Z5Z5AAZDFHYY5G$");
        reply->set_solution("randomize "+request->solution());
        return Status::OK;
    }


};

void RunServer() {
    std::string server_address("0.0.0.0:50051");
    ORServiceImpl service;

    ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);

    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_address << std::endl;

    server->Wait();
}

int main(int argc, char** argv) {
    RunServer();

    return 0;
}
