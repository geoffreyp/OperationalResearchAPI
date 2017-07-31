#ifndef OPERATIONALRESEARCHAPI_HCBASE_H
#define OPERATIONALRESEARCHAPI_HCBASE_H
#include "../CallData.h"

#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>

#define TRANSACTION_COLLECTION "transactions"
#define FITNESS_COLLECTION "fitnesses"

class HCBase : public CallData{
public:
    HCBase(hcfi::HillClimberService::AsyncService* service, ServerCompletionQueue* cq, mongocxx::database db);

protected:
    mongocxx::collection transac_coll;
    mongocxx::collection fitness_coll;
    mongocxx::database db_;
    ServerContext ctx_;
};

#endif //OPERATIONALRESEARCHAPI_HCBASE_H
