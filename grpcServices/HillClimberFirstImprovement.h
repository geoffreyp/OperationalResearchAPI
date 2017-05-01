#ifndef OPERATIONALRESEARCHAPI_HILLCLIMBERFIRSTIMPROVEMENT_H
#define OPERATIONALRESEARCHAPI_HILLCLIMBERFIRSTIMPROVEMENT_H

#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <grpc++/grpc++.h>
#include "../libs/helper.h"

#ifdef BAZEL_BUILD
#include "../protos/hcfi.proto"
#else
#include "../protoClassServer/hcfi.grpc.pb.h"
#endif

#define BDD "api"
#define TRANSACTION_COLLECTION "transactions"
#define FITNESS_COLLECTION "fitness"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using hcfi::InitTransactionRequest;
using hcfi::FitnessResponse;
using hcfi::FitnessRequest;
using hcfi::StopRequest;
using hcfi::StopResponse;

/*
 * Implement Protobuf OperationalResearch Service
 */
class HillClimberFirstImprovement final : public hcfi::HillClimberService::Service {

private:
    mongocxx::client conn;
    mongocxx::collection transac_coll;
    mongocxx::collection fitness_coll;

public:
    HillClimberFirstImprovement();
    Status InitTransaction(ServerContext* context, const InitTransactionRequest* request,FitnessResponse* reply) override;
    Status SendFitness(ServerContext* context, const FitnessRequest* request,FitnessResponse* reply) override;
    Status StopTransaction(ServerContext* context, const StopRequest* request,StopResponse* reply) override;

};


#endif //OPERATIONALRESEARCHAPI_HILLCLIMBERFIRSTIMPROVEMENT_H
