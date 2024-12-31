#ifndef CUPUPARSER_H
#define CUPUPARSER_H

#include "model/common/comsequence.h"
#include "streamreader.h"

class CUPUParser : public InfoParser
{
protected:
    virtual InfoParser::ContinueFlag withData(const std::vector<std::vector<std::vector<int>>>& fileStore, ComSequence* pcSequence) override;
    virtual size_t xReadCU(const std::vector<int>& vPCInfo, size_t s, ComSequence* pcSequence, ComCU& pcCU) override;
    virtual size_t xReadCULeaf(const std::vector<int>& vPCInfo, size_t s, ComSequence* pcSequence, ComCU& pcCU) override;
};

#endif // CUPUPARSER_H
