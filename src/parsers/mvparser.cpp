#include "mvparser.h"

size_t MVParser::xReadCULeaf(const StreamReader::TCUStore& vPCInfo, size_t s, ComCU& pcCU)
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
