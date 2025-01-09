#include "mergeparser.h"

size_t MergeParser::xReadCULeaf(const StreamReader::TCUStore& vPCInfo, size_t s, ComCU& pcCU)
{
    /// leaf node : read data
    int iMergeIndex;
    for (int i = 0; i < pcCU.getPUs().size(); i++)
    {
        Q_ASSERT(s < vPCInfo.size());
        iMergeIndex = vPCInfo[s++];
        pcCU.getPUs()[i].setMergeIndex(iMergeIndex);
    }
    return s;
}
