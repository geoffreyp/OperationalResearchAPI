#ifndef OPERATIONALRESEARCHAPI_TSBASE_H
#define OPERATIONALRESEARCHAPI_TSBASE_H
#include "../CallData.h"
#include "../../protoClassServer/tabousearch.grpc.pb.h"

#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>

#define TRANSACTION_COLLECTION "transactions"
#define FITNESS_COLLECTION "fitnesses"

class TSBase : public CallData{
public:
    TSBase(ts::TabouSearchService::AsyncService* service, ServerCompletionQueue* cq, mongocxx::database db);

protected:
    mongocxx::collection transac_coll;
    mongocxx::collection fitness_coll;
    mongocxx::database db_;
    ServerContext ctx_;
    ts::TabouSearchService::AsyncService* service_;
};

#endif //OPERATIONALRESEARCHAPI_TSBASE_H
