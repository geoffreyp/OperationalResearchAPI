#include "HelloWorld.h"

Status HelloWorld::SayHello(ServerContext *context, const HelloRequest *request, HelloResponse *response) {
    std::string response_message ("Hello Client ! I am the server and I receive : ");
    response_message.append(request->message());
    response->set_message(response_message);
}