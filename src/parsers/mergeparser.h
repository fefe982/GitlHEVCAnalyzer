#ifndef MERGEPARSER_H
#define MERGEPARSER_H

#include <QObject>
#include <QTextStream>
#include "model/common/comsequence.h"

class MergeParser : public QObject
{
    Q_OBJECT
public:
    explicit MergeParser(QObject *parent = 0);
    bool parseFile(std::istream& pcInputStream, ComSequence* pcSequence);
protected:
    size_t xReadMergeIndex(std::vector<int> vPCInfo, size_t s, ComCU* pcCU);
signals:

public slots:

};

#endif // MERGEPARSER_H
