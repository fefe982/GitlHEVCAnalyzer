#include "decodergeneralparser.h"
#include <QRegExp>
#include <QTextStream>
#include <QDebug>
#include "rapidjson/document.h"

/// rearrange frames into POC ascending order
static bool xFrameSortingOrder(ComFrame* pcFrameFirst, ComFrame* pcFrameSecond)
{
    return (pcFrameFirst->getPOC() < pcFrameSecond->getPOC());
}


DecoderGeneralParser::DecoderGeneralParser() = default;

static void readIntArray(QVector<int>* paiArr, QString* pstrArrStr)
{
    QString strTrimmed = pstrArrStr->trimmed();
    QTextStream strTextStream(&strTrimmed);
    int iPOC;
    while(!strTextStream.atEnd())
    {
        strTextStream >> iPOC;
        paiArr->push_back(iPOC);
    }
}

bool DecoderGeneralParser::parseFile(std::istream &pcInputStream, ComSequence* pcSequence)
{
    std::string line;
    while (std::getline(pcInputStream, line)) {
        rapidjson::Document doc;
        doc.Parse(line.c_str());
        if (doc.HasParseError()) {
            continue;
        }
        ComFrame* pcFrame = new ComFrame(pcSequence);

        /// POC & Decoding time
        pcFrame->setPOC(doc["POC"].GetInt());
        pcFrame->setQp(doc["QP"].GetInt());
        pcFrame->setBitCount(doc["byte_count"].GetInt() * 8);
        pcFrame->setTotalDecTime(doc["decode_time"].GetDouble());

        for (auto& poc : doc["ref_list"][0].GetArray()) {
            pcFrame->getL0List().push_back(poc.GetInt());
        }
        for (auto& poc : doc["ref_list"][1].GetArray()) {
            pcFrame->getL1List().push_back(poc.GetInt());
        }
        pcSequence->getFramesInDecOrder().push_back(pcFrame);
        pcSequence->getFramesInDisOrder().push_back(pcFrame);
    }
    pcSequence->setTotalFrames(pcSequence->getFramesInDisOrder().size());
    /// sort & calculate frame displaying order according to POC
    xSortByFrameCount(pcSequence);

    return true;
}

void DecoderGeneralParser::xSortByFrameCount( ComSequence* pcSequence )
{
    /// Get IDR groups
    QList<QVector<ComFrame*>::iterator> cIDRGroup;
    QVector<ComFrame*>::iterator cIter = pcSequence->getFramesInDisOrder().begin();
    while(cIter!=pcSequence->getFramesInDisOrder().end())
    {
        if ((*cIter)->getPOC() == 0)
        {
            cIDRGroup.push_back(cIter);
        }
        cIter++;
    }
    cIDRGroup.push_back(cIter);
    Q_ASSERT(cIDRGroup.size() >= 2);    /// at least one IDR group

    /// sort each IDRGroup
    for(int i = 0; i < cIDRGroup.size()-1; i++)
        std::sort(cIDRGroup[i], cIDRGroup[i+1], xFrameSortingOrder);

    /// assign frame num
    for(int i = 0; i < pcSequence->getFramesInDisOrder().size(); i++)
    {
        pcSequence->getFramesInDisOrder().at(i)->setFrameCount(i);
    }
}
