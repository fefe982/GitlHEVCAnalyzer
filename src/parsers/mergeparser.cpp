#include "mergeparser.h"

size_t MergeParser::xReadCULeaf(const std::vector<int>& vPCInfo, size_t s, ComSequence*, ComCU& pcCU)
{
    /// leaf node : read data
    int iMergeIndex;
    for (int i = 0; i < pcCU.getPUs().size(); i++)
    {
        Q_ASSERT(s < vPCInfo.size());
        iMergeIndex = vPCInfo[s++];
        pcCU.getPUs().at(i)->setMergeIndex(iMergeIndex);
    }
    return s;
}
