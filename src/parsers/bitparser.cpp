#include "bitparser.h"

#include "streamreader.h"

BitParser::BitParser(QObject *parent) :
    QObject(parent)
{
}


bool BitParser::parseLCUBitFile(std::istream &pcInputStream, ComSequence* pcSequence)
{
    Q_ASSERT( pcSequence != NULL );
    size_t cuCnt = pcSequence->getNumberMaxCu();
    size_t frames = pcSequence->getFramesInDisOrder().size();
    auto fileStore = StreamReader::parse<int>(pcInputStream, frames, cuCnt);
    for (int iFrame = 0; iFrame < frames; iFrame++) {
        ComFrame* pcFrame = pcSequence->getFramesInDecOrder().at(iFrame);
        for (int iAddr = 0; iAddr < cuCnt; iAddr++) {
            auto pcLCU = pcFrame->getLCUs().at(iAddr);
            int iLCUBit = fileStore[iFrame][iAddr][0];
            pcLCU->setBitCount(iLCUBit);
            pcFrame->getBitCount() += iLCUBit;
        }
    }
    return true;
}



bool BitParser::parseSCUBitFile(std::istream& pcInputStream, ComSequence* pcSequence)
{
    Q_ASSERT( pcSequence != NULL );
    size_t cuCnt = pcSequence->getNumberMaxCu();
    size_t frames = pcSequence->getFramesInDisOrder().size();
    auto fileStore = StreamReader::parse<int>(pcInputStream, frames, cuCnt);
    for (int iFrame = 0; iFrame < frames; iFrame++) {
        ComFrame* pcFrame = pcSequence->getFramesInDecOrder().at(iFrame);
        for (int iAddr = 0; iAddr < cuCnt; iAddr++) {
            auto pcLCU = pcFrame->getLCUs().at(iAddr);
            xParseSCUBitFile(fileStore[iFrame][iAddr], 0, pcLCU);
        }
    }
    return true;
}


size_t BitParser::xParseSCUBitFile(std::vector<int> vPCInfo, size_t s, ComCU* pcCU)
{
    if (!pcCU->getSCUs().empty())
    {
        /// non-leaf node : recursive reading for children
        s = xParseSCUBitFile(vPCInfo, s, pcCU->getSCUs().at(0));
        s = xParseSCUBitFile(vPCInfo, s, pcCU->getSCUs().at(1));
        s = xParseSCUBitFile(vPCInfo, s, pcCU->getSCUs().at(2));
        s = xParseSCUBitFile(vPCInfo, s, pcCU->getSCUs().at(3));
    }
    else
    {
        /// leaf node : read data
        Q_ASSERT(s < vPCInfo.size());
        int iSCUBit = vPCInfo[s++];
        pcCU->setBitCount(iSCUBit);
    }
    return s;
}
