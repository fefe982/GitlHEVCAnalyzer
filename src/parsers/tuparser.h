#ifndef TUPARSER_H
#define TUPARSER_H
#include <QObject>
#include "model/common/comsequence.h"

class TUParser : public QObject
{
    Q_OBJECT
public:
    explicit TUParser(QObject *parent = 0);
    bool parseFile(std::istream& pcInputStream, ComSequence* pcSequence);
protected:
    size_t xReadTU(const std::vector<uchar>& vPCInfo, size_t s, ComSequence* sequence, ComCU* pcTU);
    size_t xReadTUHelper(const std::vector<uchar>& vPCInfo, size_t s, ComSequence* sequence, ComTU* pcTU);
};

#endif // TUPARSER_H
