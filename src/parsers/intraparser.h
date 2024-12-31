#ifndef INTRAPARSER_H
#define INTRAPARSER_H

#include <QObject>

#include "model/common/comsequence.h"

class IntraParser : public QObject
{
    Q_OBJECT
public:
    explicit IntraParser(QObject *parent = 0);
    bool parseFile(std::istream& pcInputStream, ComSequence* pcSequence);
protected:
    size_t xReadIntraMode(std::vector<uchar> &vPCInfo, size_t s, ComCU* pcCU);
signals:

public slots:

};

#endif // INTRAPARSER_H
