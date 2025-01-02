#include "bitparser.h"

BitParserLCU::BitParserLCU() {
    m_delayed = false;
}

size_t BitParserLCU::xReadCULeaf(const std::vector<int> &, size_t s, ComCU& )
{
    return s;
}
bool BitParserLCU::parseSequence()
{
    for (int iFrame = 0; iFrame < m_nFrames; iFrame++) {
        ComFrame* pcFrame = m_pcSequence->getFramesInDecOrder().at(iFrame);
        for (int iAddr = 0; iAddr < m_nCu; iAddr++) {
            auto pcLCU = &pcFrame->getLCUs()[iAddr];
            int iLCUBit = m_fileStore[iFrame][iAddr][0];
            pcLCU->setBitCount(iLCUBit);
            pcFrame->getBitCount() += iLCUBit;
        }
    }
    return true;
}

size_t BitParserSCU::xReadCULeaf(const std::vector<int> &vPCInfo, size_t s, ComCU& pcCU)
{
    Q_ASSERT(s < vPCInfo.size());
    pcCU.setBitCount(vPCInfo[s++]);
    return s;
}
