#include "mvparser.h"

#include "streamreader.h"

MVParser::MVParser(QObject *parent) :
    QObject(parent)
{
}

bool MVParser::parseFile(std::istream& pcInputStream, ComSequence* pcSequence)
{
    Q_ASSERT(pcSequence != NULL);
    size_t cuCnt = pcSequence->getNumberMaxCu();
    size_t frames = pcSequence->getFramesInDisOrder().size();
    auto fileStore = StreamReader::parse<int>(pcInputStream, frames, cuCnt);
    int iMVCnt = 0;
    for (auto& frame : fileStore) {
        for (auto& addr : frame) {
            size_t i = 0;
            while (i < addr.size()) {
                if (addr[i] == 0) {
                    i += 1;
                }
                else if (addr[i] == 1 || addr[i] == 2) {
                    iMVCnt += 1;
                    i += 4;
                }
                else if (addr[i] == 3) {
                    iMVCnt += 2;
                    i += 7;
                }
                else {
                    Q_ASSERT(false);
                }
            }
        }
    }
    pcSequence->allocComMV(iMVCnt);
    for (int iFrame = 0; iFrame < frames; iFrame++) {
        ComFrame* pcFrame = pcSequence->getFramesInDecOrder().at(iFrame);
        for (int iAddr = 0; iAddr < cuCnt; iAddr++) {
            auto pcLCU = &pcFrame->getLCUs()[iAddr];
            xReadMV(fileStore[iFrame][iAddr], 0, pcSequence, pcLCU);
        }
    }
    return true;
}
size_t MVParser::xReadMV(const std::vector<int>& vPCInfo, size_t s, ComSequence *sequence, ComCU* pcCU)
{
    if (!pcCU->getSCUs().empty())
    {
        /// non-leaf node : recursive reading for children
        s = xReadMV(vPCInfo, s, sequence, pcCU->getSCUs().at(0));
        s = xReadMV(vPCInfo, s, sequence, pcCU->getSCUs().at(1));
        s = xReadMV(vPCInfo, s, sequence, pcCU->getSCUs().at(2));
        s = xReadMV(vPCInfo, s, sequence, pcCU->getSCUs().at(3));
    }
    else
    {
        /// leaf node : read data
        int iInterDir;
        for(int i = 0; i < pcCU->getPUs().size(); i++)
        {
            Q_ASSERT(s < vPCInfo.size());
            iInterDir = vPCInfo[s++];
            ComPU* pcPU = pcCU->getPUs().at(i);
            pcPU->setInterDir(iInterDir);

            int iRefPOC;
            int iHor, iVer;
            ComMV* pcReadMV = NULL;
            if( iInterDir == 1 || iInterDir == 2)   //uni-prediction, 1 MV
            {
                iRefPOC = vPCInfo[s++];
                iHor = vPCInfo[s++];
                iVer = vPCInfo[s++];
                pcReadMV = sequence->newComMV();
                pcReadMV->setRefPOC(iRefPOC);
                pcReadMV->setHor(iHor);
                pcReadMV->setVer(iVer);
                pcPU->getMVs().push_back(pcReadMV);
            }
            else if( iInterDir == 3 )               //bi-prediction, 2 MVs
            {
                iRefPOC = vPCInfo[s++];
                iHor = vPCInfo[s++];
                iVer = vPCInfo[s++];
                pcReadMV = sequence->newComMV();
                pcReadMV->setRefPOC(iRefPOC);
                pcReadMV->setHor(iHor);
                pcReadMV->setVer(iVer);
                pcPU->getMVs().push_back(pcReadMV);

                iRefPOC = vPCInfo[s++];
                iHor = vPCInfo[s++];
                iVer = vPCInfo[s++];
                pcReadMV = sequence->newComMV();
                pcReadMV->setRefPOC(iRefPOC);
                pcReadMV->setHor(iHor);
                pcReadMV->setVer(iVer);
                pcPU->getMVs().push_back(pcReadMV);
            }
        }
    }
    return s;
}
