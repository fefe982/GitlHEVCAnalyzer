#include "streamreader.h"

#include "model/common/comframe.h"
#include "../appgitlhevcdecoder/TLibSysuAnalyzer/CUInfo.h"
#include <iostream>
#include <string>

namespace {
    template<typename T> T read(const char*& pcInputStream) {
        T val = *(T*)pcInputStream;
        pcInputStream += sizeof(T);
        return val;
    }
    template<CUInfoParts Part> void read_vec(const char*& pcInputStream, std::vector<short>& v) {
        int sz;
        if constexpr (CUInfoPartTrait<Part>::len == 0) {
            sz = read<char>(pcInputStream);
        } else {
            sz = CUInfoPartTrait<Part>::len;
        }
        read_vec_len<typename CUInfoPartTrait<Part>::value_type>(pcInputStream, v, sz);
    }
    template<typename T> void read_vec_len(const char*& pcInputStream, std::vector<short>& v, int sz) {
        v.resize(sz);
        for (int i = 0; i < sz; i++) {
            v[i] = read<T>(pcInputStream);
        }
    }
}

std::vector<const char*> StreamReader::getFramePointer(const char* pcInputStream, size_t frames) {
    std::vector<const char*> framePointer(frames);
    for (int iFrame = 0; iFrame < frames; iFrame++) {
        int iFrameSize = read<int>(pcInputStream);
        framePointer[iFrame] = pcInputStream;
        pcInputStream += iFrameSize;
    }
    return framePointer;
}
StreamReader::TFileStore StreamReader::parse(const char* pcInputStream, size_t cuCnt) {
    TFileStore fileStore(8, std::vector<TCUStore>(cuCnt));
    for (int iCU = 0; iCU < cuCnt; iCU++) {
        int iAddr = read<int>(pcInputStream);
        Q_ASSERT(iCU == iAddr);
        read_vec<CUInfoParts::CUPU>(pcInputStream, fileStore[0][iCU]);
        read_vec<CUInfoParts::TU>(pcInputStream, fileStore[1][iCU]);
        read_vec<CUInfoParts::PRED>(pcInputStream, fileStore[2][iCU]);
        read_vec<CUInfoParts::MV>(pcInputStream, fileStore[3][iCU]);
        read_vec<CUInfoParts::MERGE>(pcInputStream, fileStore[4][iCU]);
        read_vec<CUInfoParts::INTRA>(pcInputStream, fileStore[5][iCU]);
        read_vec<CUInfoParts::BIT_LCU>(pcInputStream, fileStore[6][iCU]);
        read_vec<CUInfoParts::BIT_SCU>(pcInputStream, fileStore[7][iCU]);
    }
    return fileStore;
}

InfoParser::InfoParser(ComSequence *pcSequence) : m_has_leaf(true), m_pcSequence(pcSequence) {}

InfoParser::InfoParser() : InfoParser(nullptr) {}

bool InfoParser::parseFrame(const std::vector<StreamReader::TCUStore>& vCuInfo, ComFrame& pcFrame)
{
    if (!parseSequence(vCuInfo, pcFrame)) {
        return false;
    }
    if (!m_has_leaf) {
        return true;
    }
    for (int iAddr = 0; iAddr < vCuInfo.size(); iAddr++) {
        if (xReadCU(vCuInfo[iAddr], 0, pcFrame.getLCUs()[iAddr]) == size_t(-1)) {
            return false;
        }
    }
    return true;
}

bool InfoParser::parseSequence(const std::vector<StreamReader::TCUStore>&, ComFrame&) { return true; }

size_t InfoParser::xReadCU(const StreamReader::TCUStore& vPCInfo, size_t s, ComCU& pcCU) {
    if (!pcCU.getSCUs().empty())
    {
        for (int i = 0; i < 4; i++) {
            s = xReadCU(vPCInfo, s, pcCU.getSCUs()[i]);
        }
    }
    else
    {
        s = xReadCULeaf(vPCInfo, s, pcCU);
    }
    return s;
}