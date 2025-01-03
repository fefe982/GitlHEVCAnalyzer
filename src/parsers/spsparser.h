#ifndef SPSPARSER_H
#define SPSPARSER_H

#include <QTextStream>
#include "model/common/comsequence.h"

class SpsParser
{
public:
    bool parseFile(QTextStream* pcInputStream, ComSequence* pcSequence);
};

class VpsParser {
public:
    bool parseFile(QTextStream* pcInputStream, ComSequence* pcSequence);
};

#endif // SPSPARSER_H
