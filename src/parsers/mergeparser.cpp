#include "mergeparser.h"

#include "streamreader.h"

MergeParser::MergeParser(QObject *parent) :
    QObject(parent)
{
}
bool MergeParser::parseFile(std::istream& pcInputStream, ComSequence* pcSequence)
{
    Q_ASSERT(pcSequence != NULL);
    size_t cuCnt = pcSequence->getNumberMaxCu();
    size_t frames = pcSequence->getFramesInDisOrder().size();
    auto fileStore = StreamReader::parse(pcInputStream, frames, cuCnt);
    for (int iFrame = 0; iFrame < frames; iFrame++) {
        ComFrame* pcFrame = pcSequence->getFramesInDecOrder().at(iFrame);
        for (int iAddr = 0; iAddr < cuCnt; iAddr++) {
            auto pcLCU = &pcFrame->getLCUs()[iAddr];
            xReadMergeIndex(fileStore[iFrame][iAddr], 0, pcLCU);
        }
    }
    return true;
}

size_t MergeParser::xReadMergeIndex(std::vector<int> vPCInfo, size_t s, ComCU* pcCU)
{
    if (!pcCU->getSCUs().empty())
    {
        /// non-leaf node : recursive reading for children
        s = xReadMergeIndex(vPCInfo, s, pcCU->getSCUs().at(0));
        s = xReadMergeIndex(vPCInfo, s, pcCU->getSCUs().at(1));
        s = xReadMergeIndex(vPCInfo, s, pcCU->getSCUs().at(2));
        s = xReadMergeIndex(vPCInfo, s, pcCU->getSCUs().at(3));
    }
    else
    {
        /// leaf node : read data
        int iMergeIndex;
        for (int i = 0; i < pcCU->getPUs().size(); i++)
        {
            Q_ASSERT(s < vPCInfo.size());
            iMergeIndex = vPCInfo[s++];
            pcCU->getPUs().at(i)->setMergeIndex(iMergeIndex);
        }
    }
    return s;
}
