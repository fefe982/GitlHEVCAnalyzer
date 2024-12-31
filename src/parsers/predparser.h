#ifndef PREDPARSER_H
#define PREDPARSER_H

#include <QObject>
#include "model/common/comsequence.h"

class PredParser : public QObject
{
    Q_OBJECT
public:
    explicit PredParser(QObject* parent = 0);
    bool parseFile(std::istream& pcInputStream, ComSequence* pcSequence);
protected:
    size_t xReadPredMode(const std::vector<uchar>& vPCInfo, size_t s, ComCU* pcCU);
signals:

public slots:

};

#endif // PREDPARSER_H
