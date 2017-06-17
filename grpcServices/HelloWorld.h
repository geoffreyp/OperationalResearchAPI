#ifndef OPERATIONALRESEARCHAPI_HELLOWORLD_H
#define OPERATIONALRESEARCHAPI_HELLOWORLD_H

// Includes required library by mongodb driver
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>

// Includes required library by GRPC
#include <grpc++/grpc++.h>

// Includes helpers and additional libs
#include "../libs/helper.h"

// Include protobuf file if it is not compile yep or the generated class by grpc
#ifdef BAZEL_BUILD
#include "../protos/helloworld.proto"
#else
#include "../protoClassServer/helloworld.grpc.pb.h"
#endif


// Using grpc namespaces
using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

// Using messages namespaces
using example::HelloRequest;
using example::HelloResponse;

/*
 * Implement the HelloWorld Service
 */
class HelloWorld final : public example::HelloWorldService::Service {

public:
    // implement the rpc method define in the protobuf file
    // the signature is in the file /protoClassServer/helloworld.grpc.pb.h at line 60
    Status SayHello(::grpc::ServerContext* context, const ::example::HelloRequest* request, ::example::HelloResponse* response) override;

};


#endif //OPERATIONALRESEARCHAPI_HELLOWORLD_H
