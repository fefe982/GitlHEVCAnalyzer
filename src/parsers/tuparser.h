#ifndef TUPARSER_H
#define TUPARSER_H

#include "model/common/comsequence.h"
#include "streamreader.h"

class TUParser :public InfoParser
{
    using InfoParser::InfoParser;
protected:
    virtual size_t xReadCULeaf(const StreamReader::TCUStore& vPCInfo, size_t s, ComCU& pcTU)override;
    size_t xReadTUHelper(const StreamReader::TCUStore& vPCInfo, size_t s, int iDepth, int id, ComTU& pcTU);
};

#endif // TUPARSER_H
