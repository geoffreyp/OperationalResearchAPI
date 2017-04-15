#include <iostream>
#include <memory>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <grpc++/grpc++.h>
#include "libs/helper.h"

#ifdef BAZEL_BUILD
#include "protos/api.proto"
#else
#include "protoClassServer/api.grpc.pb.h"
#endif

#define BDD "api"
#define BDD_COLLECTION "logs"

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

        std::string _id(generateId());
        reply->set_id(_id);
        reply->set_solution(request->solution());

        mongocxx::instance inst{};
        mongocxx::client conn{mongocxx::uri{}};
        bsoncxx::builder::stream::document document{};

        auto collection = conn[BDD][BDD_COLLECTION];
        document << "transaction_id" << _id;
        document << "solution" << request->solution();
        collection.insert_one(document.view());

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
