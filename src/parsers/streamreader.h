#pragma once
#include <QDebug>

#include <vector>

class ComSequence;
class ComCU;

class StreamReader {
public:
    typedef short TElemType;
    typedef std::vector<TElemType> TCUStore;
    typedef std::vector<std::vector<TCUStore>> TFileStore;
    static TFileStore parse(std::vector<char>& pcInputStream, size_t frames, size_t cuCnt);
};

class InfoParser {
public:
    InfoParser();
    virtual ~InfoParser() = default;
    bool parseFile(std::vector<char>& pcInputStream, ComSequence* pcSequence);
    bool parseFrame(size_t iFrame);
protected:
    size_t m_nFrames;
    size_t m_nCu;
    bool m_delayed;
    ComSequence* m_pcSequence;
    StreamReader::TFileStore m_fileStore;
protected:
    virtual bool parseSequence();
    virtual size_t xReadCU(const StreamReader::TCUStore& vPCInfo, size_t s, ComCU& pcCU);
    virtual size_t xReadCULeaf(const StreamReader::TCUStore& vPCInfo, size_t s, ComCU& pcCU)=0;
};