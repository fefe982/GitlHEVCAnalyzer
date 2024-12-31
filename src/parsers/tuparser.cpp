#include "tuparser.h"

#include "streamreader.h"
#include <QDebug>

constexpr auto TU_SLIPT_FLAG = 99;

TUParser::TUParser(QObject *parent):
    QObject(parent)
{
}


bool TUParser::parseFile(std::istream &pcInputStream, ComSequence* pcSequence)
{
    Q_ASSERT( pcSequence != NULL );

    size_t cuCnt = pcSequence->getNumberMaxCu();
    size_t frames = pcSequence->getFramesInDisOrder().size();
    size_t iSplitCount = 0;
    auto fileStore = StreamReader::parse<uchar>(pcInputStream, frames, cuCnt);
    for (auto& vFrame : fileStore) {
        for (auto& vPoc : vFrame) {
            for (int i : vPoc) {
                if (i == TU_SLIPT_FLAG) {
                    iSplitCount++;
                }
            }
        }
    }
    pcSequence->allocComTU(iSplitCount * 4);
    for (int iFrame = 0; iFrame < frames; iFrame++) {
        ComFrame* pcFrame = pcSequence->getFramesInDecOrder().at(iFrame);
        for (int iAddr = 0; iAddr < cuCnt; iAddr++) {
            auto pcLCU = &pcFrame->getLCUs()[iAddr];
            xReadTU(fileStore[iFrame][iAddr], 0, pcSequence, pcLCU);
        }
    }
    return true;
}


size_t TUParser::xReadTU(const std::vector<uchar>& vPCInfo, size_t s, ComSequence* sequence, ComCU* pcCU)
{
    if (!pcCU->getSCUs().empty())
    {
        /// non-leaf CU node : continue to leaf CU
        s = xReadTU(vPCInfo, s, sequence, pcCU->getSCUs().at(0));
        s = xReadTU(vPCInfo, s, sequence, pcCU->getSCUs().at(1));
        s = xReadTU(vPCInfo, s, sequence, pcCU->getSCUs().at(2));
        s = xReadTU(vPCInfo, s, sequence, pcCU->getSCUs().at(3));
    }
    else
    {
        /// leaf CU node : read TU
        ComTU* pcTURoot = &pcCU->getTURoot();
        pcTURoot->setX(pcCU->getX());
        pcTURoot->setY(pcCU->getY());
        pcTURoot->setSize(pcCU->getSize());
        s = xReadTUHelper(vPCInfo, s, sequence, &(pcCU->getTURoot()));
    }
    return s;
}


size_t TUParser::xReadTUHelper(const std::vector<uchar>& vPCInfo, size_t s, ComSequence* sequence, ComTU* pcTU)
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
        for (int i = 0; i < 4; i++)
        {
            ComTU* pcChildNode = sequence->newComTU();
            pcChildNode->setSize(pcTU->getSize() / 2);
            int iSubCUX = pcTU->getX() + i % 2 * (pcTU->getSize() / 2);
            int iSubCUY = pcTU->getY() + i / 2 * (pcTU->getSize() / 2);
            pcChildNode->setX(iSubCUX);
            pcChildNode->setY(iSubCUY);
            pcTU->getTUs().push_back(pcChildNode);
            s = xReadTUHelper(vPCInfo, s, sequence, pcChildNode);
        }
    }
    return s;
}
