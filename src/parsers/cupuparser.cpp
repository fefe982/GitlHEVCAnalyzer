#include "cupuparser.h"
#include <QDebug>
constexpr auto CU_SLIPT_FLAG = 99;      ///< CU splitting flag in file

InfoParser::ContinueFlag CUPUParser::withData(const std::vector<std::vector<std::vector<int>>> &fileStore, ComSequence* pcSequence)
{
    int iSeqWidth = pcSequence->getWidth();
    int iMaxCUSize = pcSequence->getMaxCUSize();
    int iCUOneRow = (iSeqWidth+iMaxCUSize-1)/iMaxCUSize;
    size_t iSplitCount = 0;
    size_t iPUCount = 0;
    for (auto& vFrame : fileStore) {
        for (auto& vPoc : vFrame) {
            for (int i : vPoc) {
                if (i == CU_SLIPT_FLAG) {
                    iSplitCount++;
                }
                else {
                    iPUCount += ComCU::getPUNum((PartSize)i);
                }
            }
        }
    }
    int iLCUSize = pcSequence->getMaxCUSize();
    pcSequence->allocComCU(iSplitCount * 4);
    pcSequence->allocComPU(iPUCount);
    for (int iFrame = 0; iFrame < nFrames; iFrame++) {
        ComFrame* pcFrame = pcSequence->getFramesInDecOrder().at(iFrame);
        pcFrame->getLCUs().resize(nCu);
        for (int iAddr = 0; iAddr < nCu; iAddr++) {
            ComCU* pcLCU = &pcFrame->getLCUs()[iAddr];
            pcLCU->setAddr(iAddr);
            pcLCU->setFrame(pcFrame);
            pcLCU->setDepth(0);
            pcLCU->setZorder(0);
            pcLCU->setSize(iLCUSize);
            int iPixelX = (pcLCU->getAddr() % iCUOneRow) * iMaxCUSize;
            int iPixelY = (pcLCU->getAddr() / iCUOneRow) * iMaxCUSize;
            pcLCU->setX(iPixelX);
            pcLCU->setY(iPixelY);
        }
    }
    return ContinueFlag::CONTINUE;
}

size_t CUPUParser::xReadCU(const std::vector<int>& vPCInfo, size_t s, ComSequence* pcSequence, ComCU& pcCU)
{
    int iCUMode;
    if (s == vPCInfo.size())
    {
        qCritical() << "CUPUParser Error! Illegal CU/PU Mode!";
        return size_t(-1);
    }
    iCUMode = vPCInfo[s++];

    if (iCUMode == CU_SLIPT_FLAG)
    {
        int iMaxDepth = pcCU.getFrame()->getSequence()->getMaxCUDepth();
        int iTotalNumPart = 1 << ((iMaxDepth - pcCU.getDepth()) << 1);
        /// non-leaf node : add 4 children CUs
        for (int i = 0; i < 4; i++)
        {
            ComCU* pcChildNode = pcSequence->newComCU(pcCU.getFrame());
            pcChildNode->setAddr(pcCU.getAddr());
            pcChildNode->setDepth(pcCU.getDepth() + 1);
            pcChildNode->setZorder(pcCU.getZorder() + (iTotalNumPart / 4) * i);
            pcChildNode->setSize(pcCU.getSize() / 2);
            int iSubCUX = pcCU.getX() + i % 2 * (pcCU.getSize() / 2);
            int iSubCUY = pcCU.getY() + i / 2 * (pcCU.getSize() / 2);
            pcChildNode->setX(iSubCUX);
            pcChildNode->setY(iSubCUY);
            pcCU.getSCUs().push_back(pcChildNode);
            s = xReadCU(vPCInfo, s, pcSequence, *pcChildNode);
        }
    }
    else
    {
        pcCU.setPartSize((PartSize)iCUMode);
        int iPUCount = ComCU::getPUNum((PartSize)iCUMode);
        for (int i = 0; i < iPUCount; i++)
        {
            ComPU* pcPU = pcSequence->newComPU(&pcCU);
            int iPUOffsetX, iPUOffsetY, iPUWidth, iPUHeight;
            ComCU::getPUOffsetAndSize(pcCU.getSize(), (PartSize)iCUMode, i, iPUOffsetX, iPUOffsetY, iPUWidth, iPUHeight);
            int iPUX = pcCU.getX() + iPUOffsetX;
            int iPUY = pcCU.getY() + iPUOffsetY;
            pcPU->setX(iPUX);
            pcPU->setY(iPUY);
            pcPU->setWidth(iPUWidth);
            pcPU->setHeight(iPUHeight);
            pcCU.getPUs().push_back(pcPU);
        }
    }
    return s;
}
size_t CUPUParser::xReadCULeaf(const std::vector<int>&, size_t s, ComSequence*, ComCU&) { return s; }
