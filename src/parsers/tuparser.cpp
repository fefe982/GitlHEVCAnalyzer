#include "tuparser.h"

#include <QDebug>

constexpr auto TU_SLIPT_FLAG = 99;

InfoParser::ContinueFlag TUParser::withData(const std::vector<std::vector<std::vector<int>>> &fileStore, ComSequence* pcSequence)
{
    size_t iSplitCount = 0;
    for (auto& vFrame : fileStore) {
        for (auto& vPoc : vFrame) {
            for (int i : vPoc) {
                if (i == TU_SLIPT_FLAG) {
                    iSplitCount++;
                }
            }
        }
    }
    return ContinueFlag::CONTINUE;
}


size_t TUParser::xReadCULeaf(const std::vector<int>& vPCInfo, size_t s, ComSequence* sequence, ComCU& pcCU)
{

    ComTU* pcTURoot = &pcCU.getTURoot();
    pcTURoot->setX(pcCU.getX());
    pcTURoot->setY(pcCU.getY());
    pcTURoot->setSize(pcCU.getSize());
    s = xReadTUHelper(vPCInfo, s, sequence, &(pcCU.getTURoot()));
    return s;
}


size_t TUParser::xReadTUHelper(const std::vector<int>& vPCInfo, size_t s, ComSequence* sequence, ComTU* pcTU)
{
    int iTUMode;
    if (s > vPCInfo.size())
    {
        qCritical() << "TUParser Error! Illegal TU Mode!";
        return size_t(-1);
    }
    iTUMode = vPCInfo[s++];

    if (iTUMode == TU_SLIPT_FLAG)
    {
        /// non-leaf node : add 4 children CUs
        pcTU->getTUs().reserve(4);
        for (int i = 0; i < 4; i++)
        {
            ComTU* pcChildNode = &pcTU->getTUs().emplace_back();
            pcChildNode->setSize(pcTU->getSize() / 2);
            int iSubCUX = pcTU->getX() + i % 2 * (pcTU->getSize() / 2);
            int iSubCUY = pcTU->getY() + i / 2 * (pcTU->getSize() / 2);
            pcChildNode->setX(iSubCUX);
            pcChildNode->setY(iSubCUY);
            s = xReadTUHelper(vPCInfo, s, sequence, pcChildNode);
        }
    }
    return s;
}
