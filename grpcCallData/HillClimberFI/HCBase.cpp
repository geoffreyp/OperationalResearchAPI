#include "HCBase.h"

HCBase::HCBase(hcfi::HillClimberService::AsyncService* service, ServerCompletionQueue* cq, mongocxx::database db):
        CallData(service, cq), db_(db){
    transac_coll = db[TRANSACTION_COLLECTION];
    fitness_coll = db[FITNESS_COLLECTION];
}