#ifndef CUPUPARSER_H
#define CUPUPARSER_H

#include "model/common/comsequence.h"
#include "streamreader.h"

class CUPUParser : public InfoParser
{
    using InfoParser::InfoParser;
protected:
    virtual bool parseSequence(const std::vector<StreamReader::TCUStore>& vCuInfo, ComFrame& frame) override;
    virtual size_t xReadCU(const StreamReader::TCUStore& vPCInfo, size_t s, ComCU& pcCU) override;
    virtual size_t xReadCULeaf(const StreamReader::TCUStore& vPCInfo, size_t s, ComCU& pcCU) override;
};

#endif // CUPUPARSER_H
