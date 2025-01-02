#ifndef BITPARSER_H
#define BITPARSER_H

#include "model/common/comsequence.h"
#include "streamreader.h"

class BitParserLCU : public InfoParser
{
public:
    BitParserLCU();
protected:
    virtual bool parseSequence()override;
    virtual size_t xReadCULeaf(const std::vector<int> &vPCInfo, size_t s, ComCU& pcCU)override;
};

class BitParserSCU : public InfoParser
{
protected:
    virtual size_t xReadCULeaf(const std::vector<int> &vPCInfo, size_t s, ComCU& pcCU)override;
};


#endif // BITPARSER_H
