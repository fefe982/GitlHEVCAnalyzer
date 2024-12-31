#include "predparser.h"

#include <QDebug>

size_t PredParser::xReadCULeaf(const std::vector<int>& vPCInfo, size_t s, ComSequence*, ComCU& pcCU)
{
    for (int i = 0; i < pcCU.getPUs().size(); i++)
    {
        Q_ASSERT(s < vPCInfo.size());
        int iPredMode = vPCInfo[s++];
        ComPU* pcPU = pcCU.getPUs().at(i);
        pcPU->setPredMode((PredMode)iPredMode);
    }
    return s;
}
