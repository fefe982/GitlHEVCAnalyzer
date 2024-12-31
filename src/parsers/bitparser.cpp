#include "bitparser.h"

size_t BitParserLCU::xReadCULeaf(const std::vector<int> &, size_t s, ComSequence*, ComCU& )
{
    return s;
}
InfoParser::ContinueFlag BitParserLCU::withData(const std::vector<std::vector<std::vector<int>>> &fileStore, ComSequence* pcSequence)
{
    for (int iFrame = 0; iFrame < nFrames; iFrame++) {
        ComFrame* pcFrame = pcSequence->getFramesInDecOrder().at(iFrame);
        for (int iAddr = 0; iAddr < nCu; iAddr++) {
            auto pcLCU = &pcFrame->getLCUs()[iAddr];
            int iLCUBit = fileStore[iFrame][iAddr][0];
            pcLCU->setBitCount(iLCUBit);
            pcFrame->getBitCount() += iLCUBit;
        }
    }
    return ContinueFlag::STOP;
}

size_t BitParserSCU::xReadCULeaf(const std::vector<int> &vPCInfo, size_t s, ComSequence*, ComCU& pcCU)
{
    Q_ASSERT(s < vPCInfo.size());
    pcCU.setBitCount(vPCInfo[s++]);
    return s;
}
