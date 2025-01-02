#ifndef TUPARSER_H
#define TUPARSER_H

#include "model/common/comsequence.h"
#include "streamreader.h"

class TUParser :public InfoParser
{
protected:
    virtual size_t xReadCULeaf(const std::vector<int>& vPCInfo, size_t s, ComCU& pcTU)override;
    size_t xReadTUHelper(const std::vector<int>& vPCInfo, size_t s, ComTU* pcTU);
};

#endif // TUPARSER_H
