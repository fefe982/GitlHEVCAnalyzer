#ifndef BITPARSER_H
#define BITPARSER_H

#include "model/common/comsequence.h"
#include "streamreader.h"

class BitParserLCU : public InfoParser
{
protected:
    virtual InfoParser::ContinueFlag withData(const std::vector<std::vector<std::vector<int>>>& fileStore, ComSequence* pcSequence)override;
    virtual size_t xReadCULeaf(const std::vector<int> &vPCInfo, size_t s, ComSequence* pcSequence, ComCU& pcCU)override;
};

class BitParserSCU : public InfoParser
{
protected:
    virtual size_t xReadCULeaf(const std::vector<int> &vPCInfo, size_t s, ComSequence* pcSequence, ComCU& pcCU)override;
};


#endif // BITPARSER_H
