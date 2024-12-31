#include "intraparser.h"

#include "streamreader.h"
#include <QDebug>

IntraParser::IntraParser(QObject *parent) :
    QObject(parent)
{
}

bool IntraParser::parseFile(std::istream & pcInputStream, ComSequence* pcSequence)
{
    Q_ASSERT( pcSequence != NULL );
    size_t cuCnt = pcSequence->getNumberMaxCu();
    size_t frames = pcSequence->getFramesInDisOrder().size();
    auto fileStore = StreamReader::parse<uchar>(pcInputStream, frames, cuCnt);
    for (int iFrame = 0; iFrame < frames; iFrame++) {
        ComFrame* pcFrame = pcSequence->getFramesInDecOrder().at(iFrame);
        for (int iAddr = 0; iAddr < cuCnt; iAddr++) {
            auto pcLCU = &pcFrame->getLCUs()[iAddr];
            xReadIntraMode(fileStore[iFrame][iAddr], 0, pcLCU);
        }
    }
    return true;
}


size_t IntraParser::xReadIntraMode(std::vector<uchar>& vPCInfo, size_t s, ComCU* pcCU)
{
    if (!pcCU->getSCUs().empty())
    {
        /// non-leaf node : recursive reading for children
        s = xReadIntraMode(vPCInfo, s, pcCU->getSCUs().at(0));
        s = xReadIntraMode(vPCInfo, s, pcCU->getSCUs().at(1));
        s = xReadIntraMode(vPCInfo, s, pcCU->getSCUs().at(2));
        s = xReadIntraMode(vPCInfo, s, pcCU->getSCUs().at(3));
    }
    else
    {
        /// leaf node : read data
        int iIntraDirLuma;
        int iIntraDirChroma;
        for (int i = 0; i < pcCU->getPUs().size(); i++)
        {
            Q_ASSERT(s < vPCInfo.size());
            iIntraDirLuma = vPCInfo[s++];
            iIntraDirChroma = vPCInfo[s++];
            pcCU->getPUs().at(i)->setIntraDirLuma(iIntraDirLuma);
            pcCU->getPUs().at(i)->setIntraDirChroma(iIntraDirChroma);
        }
    }
    return s;
}
