#include "cupuparser.h"
#include <QDebug>
constexpr auto CU_SLIPT_FLAG = 99;      ///< CU splitting flag in file

bool CUPUParser::parseSequence()
{
    int iSeqWidth = m_pcSequence->getWidth();
    int iMaxCUSize = m_pcSequence->getMaxCUSize();
    int iCUOneRow = (iSeqWidth+iMaxCUSize-1)/iMaxCUSize;
    size_t iSplitCount = 0;
    size_t iPUCount = 0;
    for (auto& vFrame : m_fileStore) {
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
    int iLCUSize = m_pcSequence->getMaxCUSize();
    for (int iFrame = 0; iFrame < m_nFrames; iFrame++) {
        ComFrame* pcFrame = m_pcSequence->getFramesInDecOrder().at(iFrame);
        pcFrame->getLCUs().resize(m_nCu);
        for (int iAddr = 0; iAddr < m_nCu; iAddr++) {
            ComCU* pcLCU = &pcFrame->getLCUs()[iAddr];
            pcLCU->setAddr(iAddr);
            pcLCU->setDepth(0);
            pcLCU->setZorder(0);
            pcLCU->setSize(iLCUSize);
            int iPixelX = (pcLCU->getAddr() % iCUOneRow) * iMaxCUSize;
            int iPixelY = (pcLCU->getAddr() / iCUOneRow) * iMaxCUSize;
            pcLCU->setX(iPixelX);
            pcLCU->setY(iPixelY);
        }
    }
    return true;
}

size_t CUPUParser::xReadCU(const std::vector<int>& vPCInfo, size_t s, ComCU& pcCU)
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
        int iMaxDepth = m_pcSequence->getMaxCUDepth();
        int iTotalNumPart = 1 << ((iMaxDepth - pcCU.getDepth()) << 1);
        pcCU.getSCUs().reserve(4);
        for (int i = 0; i < 4; i++)
        {
            ComCU* pcChildNode = &pcCU.getSCUs().emplace_back();
            pcChildNode->setAddr(pcCU.getAddr());
            pcChildNode->setDepth(pcCU.getDepth() + 1);
            pcChildNode->setZorder(pcCU.getZorder() + (iTotalNumPart / 4) * i);
            pcChildNode->setSize(pcCU.getSize() / 2);
            int iSubCUX = pcCU.getX() + i % 2 * (pcCU.getSize() / 2);
            int iSubCUY = pcCU.getY() + i / 2 * (pcCU.getSize() / 2);
            pcChildNode->setX(iSubCUX);
            pcChildNode->setY(iSubCUY);
            s = xReadCU(vPCInfo, s, *pcChildNode);
        }
    }
    else
    {
        pcCU.setPartSize((PartSize)iCUMode);
        int iPUCount = ComCU::getPUNum((PartSize)iCUMode);
        pcCU.getPUs().reserve(iPUCount);
        for (int i = 0; i < iPUCount; i++)
        {
            ComPU* pcPU = &pcCU.getPUs().emplace_back();
            int iPUOffsetX, iPUOffsetY, iPUWidth, iPUHeight;
            ComCU::getPUOffsetAndSize(pcCU.getSize(), (PartSize)iCUMode, i, iPUOffsetX, iPUOffsetY, iPUWidth, iPUHeight);
            int iPUX = pcCU.getX() + iPUOffsetX;
            int iPUY = pcCU.getY() + iPUOffsetY;
            pcPU->setX(iPUX);
            pcPU->setY(iPUY);
            pcPU->setWidth(iPUWidth);
            pcPU->setHeight(iPUHeight);
        }
    }
    return s;
}
size_t CUPUParser::xReadCULeaf(const std::vector<int>&, size_t s, ComCU&) { return s; }
