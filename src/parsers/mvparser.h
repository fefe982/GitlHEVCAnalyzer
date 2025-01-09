#ifndef MVPARSER_H
#define MVPARSER_H

#include "model/common/comsequence.h"
#include "streamreader.h"

class MVParser : public InfoParser
{
protected:
    virtual size_t xReadCULeaf(const StreamReader::TCUStore& vPCInfo, size_t s, ComCU& pcCU)override;
};

#endif // MVPARSER_H
