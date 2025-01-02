#include "mvparser.h"

InfoParser::ContinueFlag MVParser::withData(const std::vector<std::vector<std::vector<int>>> &fileStore, ComSequence* pcSequence)
{
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
    return ContinueFlag::CONTINUE;
}
size_t MVParser::xReadCULeaf(const std::vector<int>& vPCInfo, size_t s, ComSequence* pcSequence, ComCU& pcCU)
{
    int iInterDir;
    for (int i = 0; i < pcCU.getPUs().size(); i++)
    {
        Q_ASSERT(s < vPCInfo.size());
        iInterDir = vPCInfo[s++];
        ComPU* pcPU = &pcCU.getPUs()[i];
        pcPU->setInterDir(iInterDir);

        int iRefPOC;
        int iHor, iVer;
        ComMV* pcReadMV = NULL;
        if (iInterDir == 1 || iInterDir == 2)   //uni-prediction, 1 MV
        {
            iRefPOC = vPCInfo[s++];
            iHor = vPCInfo[s++];
            iVer = vPCInfo[s++];
            pcReadMV = &pcPU->getMVs().emplace_back();
            pcReadMV->setRefPOC(iRefPOC);
            pcReadMV->setHor(iHor);
            pcReadMV->setVer(iVer);
        }
        else if (iInterDir == 3)               //bi-prediction, 2 MVs
        {
            iRefPOC = vPCInfo[s++];
            iHor = vPCInfo[s++];
            iVer = vPCInfo[s++];
            pcReadMV = &pcPU->getMVs().emplace_back();
            pcReadMV->setRefPOC(iRefPOC);
            pcReadMV->setHor(iHor);
            pcReadMV->setVer(iVer);

            iRefPOC = vPCInfo[s++];
            iHor = vPCInfo[s++];
            iVer = vPCInfo[s++];
            pcReadMV = &pcPU->getMVs().emplace_back();
            pcReadMV->setRefPOC(iRefPOC);
            pcReadMV->setHor(iHor);
            pcReadMV->setVer(iVer);
        }
    }
    return s;
}
