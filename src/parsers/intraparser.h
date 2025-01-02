#ifndef INTRAPARSER_H
#define INTRAPARSER_H

#include "model/common/comsequence.h"
#include "streamreader.h"

class IntraParser : public InfoParser
{
protected:
    virtual size_t xReadCULeaf(const std::vector<int> &vPCInfo, size_t s, ComCU& pcCU)override;
};

#endif // INTRAPARSER_H
