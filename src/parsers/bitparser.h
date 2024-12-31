#ifndef BITPARSER_H
#define BITPARSER_H

#include <QObject>
#include <QTextStream>
#include "model/common/comsequence.h"
class BitParser : public QObject
{
    Q_OBJECT
public:
    explicit BitParser(QObject *parent = 0);
    bool parseLCUBitFile(std::istream &pcInputStream, ComSequence* pcSequence);
    bool parseSCUBitFile(std::istream &pcInputStream, ComSequence* pcSequence);

protected:
    size_t xParseSCUBitFile(std::vector<int> vPCInfo, size_t s, ComCU* pcCU);
signals:
    
public slots:
    
};

#endif // BITPARSER_H
