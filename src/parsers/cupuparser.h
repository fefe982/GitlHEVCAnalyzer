#ifndef CUPUPARSER_H
#define CUPUPARSER_H

#include <QObject>
#include <QTextStream>
#include "model/common/comsequence.h"
//
/*!
 * \brief The CUPUParser class
 * this class is used to parse the CU&PU structure file (i.e. the 'decoder_cupu.txt')
 *
 */

class CUPUParser : public QObject
{
    Q_OBJECT
public:
    explicit CUPUParser(QObject *parent = 0);
    /*!
     * \brief parseFile
     * \param pcInputStream input file stream
     * \param pcSequence output sequence
     * \return
     */
    bool parseFile(std::istream& pcInputStream, ComSequence* pcSequence);
protected:
    size_t xReadInCUMode(const std::vector<uchar>& vPCInfo, size_t s, ComSequence* sequence, ComCU* pcCU);
signals:

public slots:

};

#endif // CUPUPARSER_H
