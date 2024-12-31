#pragma once
#include "model/common/comsequence.h"

#include <QDebug>

#include <vector>

class StreamReader {
public:
    static std::vector<std::vector<std::vector<int>>> parse(std::istream& pcInputStream, size_t frames, size_t cuCnt);
};

class InfoParser {
protected:
    size_t nFrames;
    size_t nCu;
public:
    InfoParser() = default;
    virtual ~InfoParser() = default;
    bool parseFile(std::istream& pcInputStream, ComSequence* pcSequence);
protected:
    enum class ContinueFlag {
        CONTINUE,
        STOP,
        ERROR
    };
    virtual ContinueFlag withData(const std::vector<std::vector<std::vector<int>>>& fileStore, ComSequence* pcSequence);
    virtual size_t xReadCU(const std::vector<int>& vPCInfo, size_t s, ComSequence* pcSequence, ComCU& pcCU);
    virtual size_t xReadCULeaf(const std::vector<int>& vPCInfo, size_t s, ComSequence* pcSequence, ComCU& pcCU)=0;
};