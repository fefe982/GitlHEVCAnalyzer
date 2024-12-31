#ifndef MVPARSER_H
#define MVPARSER_H

#include "model/common/comsequence.h"
#include <QObject>

class MVParser : public QObject
{
    Q_OBJECT
public:
    explicit MVParser(QObject *parent = 0);
    bool parseFile(std::istream& pcInputStream, ComSequence* pcSequence);
protected:
    size_t xReadMV(const std::vector<int>& vPCInfo, size_t s, ComSequence* sequence, ComCU* pcCU);
signals:

public slots:

};

#endif // MVPARSER_H
