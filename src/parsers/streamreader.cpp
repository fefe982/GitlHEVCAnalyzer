#include "streamreader.h"

#include "model/common/comsequence.h"

#include <iostream>
#include <string>

namespace {
    template<typename T> T read(const char*& pcInputStream) {
        T val = *(T*)pcInputStream;
        pcInputStream += sizeof(T);
        return val;
    }
    template<typename T> void read_vec(const char*& pcInputStream, std::vector<short>& v) {
        int sz = read<char>(pcInputStream);
        read_vec_len<T>(pcInputStream, v, sz);
    }
    template<typename T> void read_vec_len(const char*& pcInputStream, std::vector<short>& v, int sz) {
        v.resize(sz);
        for (int i = 0; i < sz; i++) {
            v[i] = read<T>(pcInputStream);
        }
    }
}

std::vector<StreamReader::TFileStore> StreamReader::parse(const char* pcInputStream, size_t frames, size_t cuCnt) {
    std::vector<TFileStore> fileStore(8, TFileStore(frames, std::vector<TCUStore>(cuCnt)));
    size_t iLastPoc = (size_t)-1;
    for (int iFrame = 0; iFrame < frames; iFrame++ ){
        for (int iCU = 0; iCU < cuCnt; iCU++) {
            int iPoc = read<short>(pcInputStream);
            int iAddr = read<short>(pcInputStream);
            if (iCU == 0) {
                Q_ASSERT(iPoc != iLastPoc);
                iLastPoc = iPoc;
            } else {
                Q_ASSERT(iPoc == iLastPoc);
            }
            Q_ASSERT(iCU == iAddr);
            read_vec<signed char>(pcInputStream, fileStore[0][iFrame][iCU]);
            read_vec<signed char>(pcInputStream, fileStore[1][iFrame][iCU]);
            read_vec<signed char>(pcInputStream, fileStore[2][iFrame][iCU]);
            read_vec<signed char>(pcInputStream, fileStore[3][iFrame][iCU]);
            read_vec<signed char>(pcInputStream, fileStore[4][iFrame][iCU]);
            read_vec<signed char>(pcInputStream, fileStore[5][iFrame][iCU]);
            read_vec_len<short>(pcInputStream, fileStore[6][iFrame][iCU], 1);
            read_vec<short>(pcInputStream, fileStore[7][iFrame][iCU]);
        }
    }
    return fileStore;
}

InfoParser::InfoParser() : m_nFrames(0), m_nCu(0), m_delayed(true), m_pcSequence(nullptr) {}

bool InfoParser::parseFile(StreamReader::TFileStore &&fileStore, ComSequence* pcSequence)
{
    Q_ASSERT(pcSequence != NULL);
    m_pcSequence = pcSequence;
    m_nFrames = pcSequence->getFramesInDisOrder().size();
    m_nCu = pcSequence->getNumberMaxCu();
    m_fileStore = std::move(fileStore);
    auto flag = parseSequence();
    if (!m_delayed) {
        m_fileStore.clear();
    }
    return flag;
}

bool InfoParser::parseFrame(size_t iFrame)
{
    if (!m_delayed) {
        return true;
    }
    if (m_pcSequence == nullptr) {
        return false;
    }
    if (m_fileStore[iFrame].empty()) {
        return true;
    }
    ComFrame* pcFrame = m_pcSequence->getFramesInDecOrder().at(iFrame);
    for (int iAddr = 0; iAddr < m_nCu; iAddr++) {
        if (xReadCU(m_fileStore[iFrame][iAddr], 0, pcFrame->getLCUs()[iAddr]) == size_t(-1)) {
            return false;
        }
    }
    m_fileStore[iFrame].clear();
    return true;
}

bool InfoParser::parseSequence() { return true; }

bool InfoParser::delayed() const {
    return m_delayed;
}

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