#ifndef DECODERGENERALPARSER_H
#define DECODERGENERALPARSER_H

#include "model/common/comsequence.h"

class DecoderGeneralParser
{
public:
    DecoderGeneralParser();
    bool parseFile(std::istream& pcInputStream, ComSequence* pcSequence);
protected:
    void xSortByFrameCount( ComSequence* pcSequence );
};

#endif // DECODERGENERALPARSER_H
