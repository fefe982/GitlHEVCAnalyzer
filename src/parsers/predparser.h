#ifndef PREDPARSER_H
#define PREDPARSER_H

#include "model/common/comsequence.h"
#include "streamreader.h"

class PredParser : public InfoParser
{
protected:
    virtual size_t xReadCULeaf(const StreamReader::TCUStore& vPCInfo, size_t s, ComCU& pcCU)override;
};

#endif // PREDPARSER_H
