#ifndef OPERATIONALRESEARCHAPI_TABOUSEARCH_H
#define OPERATIONALRESEARCHAPI_TABOUSEARCH_H

#include "helper.h"

void addMoveInTabuList();
bool moveIsAllowed();
std::vector<std::string> getAllNeighbors(std::string solution);

#endif //OPERATIONALRESEARCHAPI_TABOUSEARCH_H
