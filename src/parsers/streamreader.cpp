#include "streamreader.h"

#include "model/common/comsequence.h"

#include <iostream>
#include <string>

std::vector<std::vector<std::vector<int>>> StreamReader::parse(std::vector<char>& pcInputStream, size_t frames, size_t cuCnt) {
    std::vector<std::vector<std::vector<int>>> fileStore(frames, std::vector<std::vector<int>>(cuCnt));
    size_t iLastPoc = (size_t)-1;
    size_t iDecOrder = (size_t)-1;
    size_t iCU = cuCnt;
    char* lineStart;
    char* lineEnd = pcInputStream.data() - 1;
    char* contentEnd = pcInputStream.data() + pcInputStream.size();
    for(;;)
    {
        lineStart = lineEnd + 1;
        while (lineStart < contentEnd && (*lineStart == '\r' || *lineStart == '\n')) {
            lineStart++;
        }
        if (lineStart >= contentEnd) {
            break;
        }
        lineEnd = lineStart + 1;
        int nBlank=0;
        while (lineEnd < contentEnd && *lineEnd != '\r' && *lineEnd != '\n') {
            if (*lineEnd == ' ') {
                nBlank++;
            }
            lineEnd++;
        }
        if (lineEnd < contentEnd) {
            *lineEnd = 0;
        }
        if (lineStart + 1 == lineEnd || *lineStart != '<') {
            continue;
        }
        char* endPos = lineStart + 1;
        int iPoc = std::strtol(endPos, &endPos, 10);
        Q_ASSERT(*endPos = ',');
        int iAddr = std::strtol(endPos + 1, &endPos, 10);
        Q_ASSERT(*endPos = '>');
        endPos++;
        iCU += 1;
        if (iCU >= cuCnt) {
            iCU = 0;
            iDecOrder += 1;
            Q_ASSERT(iPoc != iLastPoc);
            iLastPoc = iPoc;
        }
        else {
            Q_ASSERT(iPoc == iLastPoc);
        }
        Q_ASSERT(iCU == iAddr);
        Q_ASSERT(iDecOrder < frames);
        char* sPos = endPos;
        fileStore[iDecOrder][iAddr].reserve(nBlank);
        for (;;) {
            int i = std::strtol(sPos, &endPos, 10);
            if (sPos == endPos) {
                break;
            }
            fileStore[iDecOrder][iAddr].push_back(i);
            sPos = endPos;
        }
    }
    return fileStore;
}

InfoParser::InfoParser() : m_nFrames(0), m_nCu(0), m_delayed(true), m_pcSequence(nullptr) {}

bool InfoParser::parseFile(std::vector<char>& pcInputStream, ComSequence* pcSequence)
{
    Q_ASSERT(pcSequence != NULL);
    m_pcSequence = pcSequence;
    m_nFrames = pcSequence->getFramesInDisOrder().size();
    m_nCu = pcSequence->getNumberMaxCu();
    m_fileStore = StreamReader::parse(pcInputStream, m_nFrames, m_nCu);
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

size_t InfoParser::xReadCU(const std::vector<int>& vPCInfo, size_t s, ComCU& pcCU) {
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