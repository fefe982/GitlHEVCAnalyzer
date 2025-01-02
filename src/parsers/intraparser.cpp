#include "intraparser.h"

#include <QDebug>

size_t IntraParser::xReadCULeaf(const std::vector<int>& vPCInfo, size_t s, ComSequence*, ComCU& pcCU)
{
    int iIntraDirLuma;
    int iIntraDirChroma;
    for (int i = 0; i < pcCU.getPUs().size(); i++)
    {
        Q_ASSERT(s < vPCInfo.size());
        iIntraDirLuma = vPCInfo[s++];
        iIntraDirChroma = vPCInfo[s++];
        pcCU.getPUs()[i].setIntraDirLuma(iIntraDirLuma);
        pcCU.getPUs()[i].setIntraDirChroma(iIntraDirChroma);
    }
    return s;
}
