#ifndef CUPUPARSER_H
#define CUPUPARSER_H

#include "model/common/comsequence.h"
#include "streamreader.h"

class CUPUParser : public InfoParser
{
protected:
    virtual bool parseSequence() override;
    virtual size_t xReadCU(const std::vector<int>& vPCInfo, size_t s, ComCU& pcCU) override;
    virtual size_t xReadCULeaf(const std::vector<int>& vPCInfo, size_t s, ComCU& pcCU) override;
};

#endif // CUPUPARSER_H
