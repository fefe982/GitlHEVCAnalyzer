#include "tuparser.h"

#include <QDebug>

constexpr auto TU_SLIPT_FLAG = 99;

size_t TUParser::xReadCULeaf(const StreamReader::TCUStore& vPCInfo, size_t s, ComCU& pcCU) {
    ComTU& pcTURoot = pcCU.getTURoot();
    pcTURoot.setX(pcCU.getX());
    pcTURoot.setY(pcCU.getY());
    pcTURoot.setSize(pcCU.getSize());
    Q_ASSERT(s < vPCInfo.size() && vPCInfo[s] < 2);
    if (vPCInfo[s] == 0) {
        s++;
    } else {
        s = xReadTUHelper(vPCInfo, s, 0, 0, pcCU.getTURoot());
    }
    return s;
}

size_t TUParser::xReadTUHelper(const StreamReader::TCUStore& vPCInfo, size_t s, int iDepth, int id, ComTU& pcTU)
{
    if (s >= vPCInfo.size()) {
        return s;
    }
    if (vPCInfo[s] == ((1 << (iDepth << 1)) - 1) / 3 + 1 + id) {
        s++;
        /// non-leaf node : add 4 children CUs
        pcTU.getTUs().reserve(4);
        for (int i = 0; i < 4; i++) {
            ComTU& pcChildNode = pcTU.getTUs().emplace_back();
            pcChildNode.setSize(pcTU.getSize() / 2);
            int iSubCUX = pcTU.getX() + i % 2 * (pcTU.getSize() / 2);
            int iSubCUY = pcTU.getY() + i / 2 * (pcTU.getSize() / 2);
            pcChildNode.setX(iSubCUX);
            pcChildNode.setY(iSubCUY);
            s = xReadTUHelper(vPCInfo, s, iDepth + 1, id * 4 + i, pcChildNode);
        }
    }
    return s;
}
