#ifndef PREDPARSER_H
#define PREDPARSER_H

#include "model/common/comsequence.h"
#include "streamreader.h"

class PredParser : public InfoParser
{
protected:
    virtual size_t xReadCULeaf(const std::vector<int>& vPCInfo, size_t s, ComSequence* pcSequence, ComCU& pcCU)override;
};

#endif // PREDPARSER_H
