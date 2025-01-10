#ifndef BITPARSER_H
#define BITPARSER_H

#include "model/common/comsequence.h"
#include "streamreader.h"

class BitParserLCU : public InfoParser
{
public:
    BitParserLCU();
    explicit BitParserLCU(ComSequence* pcSequence);
protected:
    virtual bool parseSequence(const std::vector<StreamReader::TCUStore>& vCuInfo, ComFrame& frame)override;
    virtual size_t xReadCULeaf(const StreamReader::TCUStore &vPCInfo, size_t s, ComCU& pcCU)override;
};

class BitParserSCU : public InfoParser
{
    using InfoParser::InfoParser;
protected:
    virtual size_t xReadCULeaf(const StreamReader::TCUStore &vPCInfo, size_t s, ComCU& pcCU)override;
};


#endif // BITPARSER_H
