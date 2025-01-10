#include "bitparser.h"

BitParserLCU::BitParserLCU() :BitParserLCU(nullptr) {
}

BitParserLCU::BitParserLCU(ComSequence* pcSequence) : InfoParser(pcSequence) {
    m_has_leaf = false;
}

size_t BitParserLCU::xReadCULeaf(const StreamReader::TCUStore&, size_t s, ComCU&) {
    return s;
}
bool BitParserLCU::parseSequence(const std::vector<StreamReader::TCUStore>& vCuInfo, ComFrame& frame) {
    for (int iAddr = 0; iAddr < vCuInfo.size(); iAddr++) {
        int iLCUBit = vCuInfo[iAddr][0];
        frame.getLCUs()[iAddr].setBitCount(iLCUBit);
    }
    return true;
}

size_t BitParserSCU::xReadCULeaf(const StreamReader::TCUStore& vPCInfo, size_t s, ComCU& pcCU) {
    Q_ASSERT(s < vPCInfo.size());
    pcCU.setBitCount(vPCInfo[s++]);
    return s;
}
