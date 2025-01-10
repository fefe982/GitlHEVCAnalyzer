#ifndef MERGEPARSER_H
#define MERGEPARSER_H

#include "model/common/comsequence.h"
#include "streamreader.h"

class MergeParser : public InfoParser
{
    using InfoParser::InfoParser;
protected:
    virtual size_t xReadCULeaf(const StreamReader::TCUStore &vPCInfo, size_t s, ComCU& pcCU)override;
};

#endif // MERGEPARSER_H
