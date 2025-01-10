#pragma once
#include <QDebug>

#include <vector>

class ComSequence;
class ComFrame;
class ComCU;

class StreamReader {
public:
    typedef short TElemType;
    typedef std::vector<TElemType> TCUStore;
    typedef std::vector<std::vector<TCUStore>> TFileStore;
    static std::vector<const char*> getFramePointer(const char* pcInputStream, size_t frames);
    static TFileStore parse(const char* pcInputStream, size_t cuCnt);
};

class InfoParser {
public:
    explicit InfoParser(ComSequence *pcSequence);
    InfoParser();
    virtual ~InfoParser() = default;
    bool parseFrame(const std::vector<StreamReader::TCUStore>& vCuInfo, ComFrame& frame);
protected:
    bool m_has_leaf;
    ComSequence* m_pcSequence;
protected:
    virtual bool parseSequence(const std::vector<StreamReader::TCUStore>& vCuInfo, ComFrame& frame);
    virtual size_t xReadCU(const StreamReader::TCUStore& vPCInfo, size_t s, ComCU& pcCU);
    virtual size_t xReadCULeaf(const StreamReader::TCUStore& vPCInfo, size_t s, ComCU& pcCU)=0;
};