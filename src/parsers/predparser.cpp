#include "predparser.h"

#include "streamreader.h"
#include <QDebug>

PredParser::PredParser(QObject *parent) :
    QObject(parent)
{
}

bool PredParser::parseFile(std::istream& pcInputStream, ComSequence* pcSequence)
{
    Q_ASSERT(pcSequence != NULL);
    size_t cuCnt = pcSequence->getNumberMaxCu();
    size_t frames = pcSequence->getFramesInDisOrder().size();
    auto fileStore = StreamReader::parse<uchar>(pcInputStream, frames, cuCnt);
    for (int iFrame = 0; iFrame < frames; iFrame++) {
        ComFrame* pcFrame = pcSequence->getFramesInDecOrder().at(iFrame);
        for (int iAddr = 0; iAddr < cuCnt; iAddr++) {
            auto pcLCU = pcFrame->getLCUs().at(iAddr);
            xReadPredMode(fileStore[iFrame][iAddr], 0, pcSequence, pcLCU);
        }
    }
    return true;
}


size_t PredParser::xReadPredMode(const std::vector<uchar>& vPCInfo, size_t s, ComSequence* sequence, ComCU* pcCU)
{
    if (!pcCU->getSCUs().empty())
    {
        /// non-leaf node : recursive reading for children
        s = xReadPredMode(vPCInfo, s, sequence, pcCU->getSCUs().at(0));
        s = xReadPredMode(vPCInfo, s, sequence, pcCU->getSCUs().at(1));
        s = xReadPredMode(vPCInfo, s, sequence, pcCU->getSCUs().at(2));
        s = xReadPredMode(vPCInfo, s, sequence, pcCU->getSCUs().at(3));
    }
    else
    {
        int iPredMode;
        for (int i = 0; i < pcCU->getPUs().size(); i++)
        {
            Q_ASSERT(s < vPCInfo.size());
            iPredMode = vPCInfo[s++];
            ComPU* pcPU = pcCU->getPUs().at(i);
            pcPU->setPredMode((PredMode)iPredMode);
        }
    }
    return s;
}
