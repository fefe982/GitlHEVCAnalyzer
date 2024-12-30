#include "cupuparser.h"
#include <QTextStream>
#include <QRegExp>
#include <QtAlgorithms>
#include <QDebug>
#include <QIODevice>
#define CU_SLIPT_FLAG 99      ///< CU splitting flag in file

/// for CU sorting in Addr ascending order
static bool xCUSortingOrder(const ComCU* pcCUFirst, const ComCU* pcCUSecond)
{
    return (*pcCUFirst < *pcCUSecond);
}

CUPUParser::CUPUParser(QObject *parent) :
    QObject(parent)
{
}


bool CUPUParser::parseFile(QTextStream* pcInputStream, ComSequence* pcSequence)
{
    Q_ASSERT( pcSequence != NULL );

    ///
    int iSeqWidth = pcSequence->getWidth();
    int iMaxCUSize = pcSequence->getMaxCUSize();
    int iCUOneRow = (iSeqWidth+iMaxCUSize-1)/iMaxCUSize;

    ////
    QString strOneLine;
    QRegExp cMatchTarget;

    int cuCnt = pcSequence->getNumberMaxCu();
    int frames = pcSequence->getFramesInDisOrder().size();
    std::vector<std::vector<std::vector<uchar>>> fileStore(frames);
    int iLastPoc = -1;
    int iDecOrder = -1;
    int iCU = cuCnt;
    int iSplitCount = 0;
    while (!pcInputStream->atEnd())
    {
        strOneLine = pcInputStream->readLine();
        std::string line = strOneLine.toStdString();
        if (strOneLine.isEmpty() || strOneLine[0] != '<') {
            continue;
        }
        char* endPos;
        int iPoc = std::strtol(line.data() + 1, &endPos, 10);
        Q_ASSERT(*endPos = ',');
        int iAddr = std::strtol(endPos + 1, &endPos, 10);
        Q_ASSERT(*endPos = '>');
        endPos++;
        iCU += 1;
        if (iCU >= cuCnt) {
            iCU = 0;
            iDecOrder += 1;
            Q_ASSERT(iPoc != iLastPoc);
            iLastPoc = iPoc;
        }
        else {
            Q_ASSERT(iPoc == iLastPoc);
        }
        Q_ASSERT(iCU == iAddr);
        Q_ASSERT(iPoc < frames);
        if (fileStore[iDecOrder].empty()) {
            fileStore[iDecOrder].resize(cuCnt);
        }
        char* sPos = endPos;
        for(;;) {
            int i = std::strtol(sPos, &endPos, 10);
            if (sPos == endPos) {
                break;
            }
            if (i == CU_SLIPT_FLAG) {
                iSplitCount++;
            }
            fileStore[iDecOrder][iAddr].push_back(i);
            sPos = endPos;
        }
    }

    int iLCUSize = pcSequence->getMaxCUSize();
    pcSequence->allocComCU(cuCnt * frames + iSplitCount * 4);
    for (int iFrame = 0; iFrame < frames; iFrame++) {
        ComFrame* pcFrame = pcSequence->getFramesInDecOrder().at(iFrame);
        for (int iAddr = 0; iAddr < cuCnt; iAddr++) {
            ComCU* pcLCU = pcSequence->newComCU(pcFrame);
            pcLCU->setAddr(iAddr);
            pcLCU->setFrame(pcFrame);
            pcLCU->setDepth(0);
            pcLCU->setZorder(0);
            pcLCU->setSize(iLCUSize);
            int iPixelX = (pcLCU->getAddr() % iCUOneRow) * iMaxCUSize;
            int iPixelY = (pcLCU->getAddr() / iCUOneRow) * iMaxCUSize;
            pcLCU->setX(iPixelX);
            pcLCU->setY(iPixelY);

            if (xReadInCUMode(fileStore[iFrame][iAddr], 0, pcSequence, pcLCU) == size_t(-1)) {
                return false;
            }
            pcFrame->getLCUs().push_back(pcLCU);
        }
    }
    return true;
}



size_t CUPUParser::xReadInCUMode(const std::vector<uchar>& vPCInfo, size_t s, ComSequence* sequence, ComCU* pcCU)
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
        int iMaxDepth = pcCU->getFrame()->getSequence()->getMaxCUDepth();
        int iTotalNumPart = 1 << ((iMaxDepth - pcCU->getDepth()) << 1);
        /// non-leaf node : add 4 children CUs
        for (int i = 0; i < 4; i++)
        {
            ComCU* pcChildNode = sequence->newComCU(pcCU->getFrame());
            pcChildNode->setAddr(pcCU->getAddr());
            pcChildNode->setDepth(pcCU->getDepth() + 1);
            pcChildNode->setZorder(pcCU->getZorder() + (iTotalNumPart / 4) * i);
            pcChildNode->setSize(pcCU->getSize() / 2);
            int iSubCUX = pcCU->getX() + i % 2 * (pcCU->getSize() / 2);
            int iSubCUY = pcCU->getY() + i / 2 * (pcCU->getSize() / 2);
            pcChildNode->setX(iSubCUX);
            pcChildNode->setY(iSubCUY);
            pcCU->getSCUs().push_back(pcChildNode);
            s = xReadInCUMode(vPCInfo, s, sequence, pcChildNode);
        }
    }
    else
    {
        /// leaf node : create PUs and write the PU Mode for it
        pcCU->setPartSize((PartSize)iCUMode);

        int iPUCount = ComCU::getPUNum((PartSize)iCUMode);
        for (int i = 0; i < iPUCount; i++)
        {
            ComPU* pcPU = new ComPU(pcCU);
            int iPUOffsetX, iPUOffsetY, iPUWidth, iPUHeight;
            ComCU::getPUOffsetAndSize(pcCU->getSize(), (PartSize)iCUMode, i, iPUOffsetX, iPUOffsetY, iPUWidth, iPUHeight);
            int iPUX = pcCU->getX() + iPUOffsetX;
            int iPUY = pcCU->getY() + iPUOffsetY;
            pcPU->setX(iPUX);
            pcPU->setY(iPUY);
            pcPU->setWidth(iPUWidth);
            pcPU->setHeight(iPUHeight);
            pcCU->getPUs().push_back(pcPU);
        }

    }
    return s;
}
