#ifndef MERGEPARSER_H
#define MERGEPARSER_H

#include "model/common/comsequence.h"
#include "streamreader.h"

class MergeParser : public InfoParser
{
protected:
    virtual size_t xReadCULeaf(const std::vector<int> &vPCInfo, size_t s, ComCU& pcCU)override;
};

#endif // MERGEPARSER_H
