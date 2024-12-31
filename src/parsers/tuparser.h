#ifndef TUPARSER_H
#define TUPARSER_H

#include "model/common/comsequence.h"
#include "streamreader.h"

class TUParser :public InfoParser
{
protected:
    virtual InfoParser::ContinueFlag withData(const std::vector<std::vector<std::vector<int>>>& fileStore, ComSequence* pcSequence)override;
    virtual size_t xReadCULeaf(const std::vector<int>& vPCInfo, size_t s, ComSequence* pcSequence, ComCU& pcTU)override;
    size_t xReadTUHelper(const std::vector<int>& vPCInfo, size_t s, ComSequence* pcSequence, ComTU* pcTU);
};

#endif // TUPARSER_H
