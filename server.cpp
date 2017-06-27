#include <iostream>
#include <memory>
#include "grpcServices/HillClimberFirstImprovement.h"
#include "grpcServices/HelloWorld.h"




/*
 * Run Server function
 */
void RunServer() {
    std::string server_address("0.0.0.0:50051");
    HillClimberFirstImprovement service;
    HelloWorld helloWorldService;

    ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);
    builder.RegisterService(&helloWorldService);

    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_address << std::endl;

    server->Wait();
}

int main(int argc, char** argv) {
    RunServer();

    return 0;
}
