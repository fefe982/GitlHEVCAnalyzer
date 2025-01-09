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
    virtual size_t xReadCULeaf(const StreamReader::TCUStore &vPCInfo, size_t s, ComCU& pcCU)override;
};

class BitParserSCU : public InfoParser
{
protected:
    virtual size_t xReadCULeaf(const StreamReader::TCUStore &vPCInfo, size_t s, ComCU& pcCU)override;
};


#endif // BITPARSER_H
