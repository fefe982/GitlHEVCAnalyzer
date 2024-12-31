#include "streamreader.h"

#include <iostream>
#include <string>

std::vector<std::vector<std::vector<int>>> StreamReader::parse(std::vector<char>& pcInputStream, size_t frames, size_t cuCnt) {
    std::vector<std::vector<std::vector<int>>> fileStore(frames);
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
        if (fileStore[iDecOrder].empty()) {
            fileStore[iDecOrder].resize(cuCnt);
        }
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


bool InfoParser::parseFile(std::vector<char>& pcInputStream, ComSequence* pcSequence)
{
    Q_ASSERT(pcSequence != NULL);
    nFrames = pcSequence->getFramesInDisOrder().size();
    nCu = pcSequence->getNumberMaxCu();
    auto fileStore = StreamReader::parse(pcInputStream, nFrames, nCu);
    auto flag = withData(fileStore, pcSequence);
    if (flag == ContinueFlag::STOP) {
        return true;
    }
    else if (flag == ContinueFlag::ERROR) {
        return false;
    }
    for (int iFrame = 0; iFrame < nFrames; iFrame++) {
        ComFrame* pcFrame = pcSequence->getFramesInDecOrder().at(iFrame);
        for (int iAddr = 0; iAddr < nCu; iAddr++) {
            if (xReadCU(fileStore[iFrame][iAddr], 0, pcSequence, pcFrame->getLCUs()[iAddr]) == size_t(-1)) {
                return false;
            }
        }
    }
    return true;
}

InfoParser::ContinueFlag InfoParser::withData(const std::vector<std::vector<std::vector<int>>>&, ComSequence*) { return ContinueFlag::CONTINUE; }

size_t InfoParser::xReadCU(const std::vector<int>& vPCInfo, size_t s, ComSequence* pcSequence, ComCU& pcCU) {
    if (!pcCU.getSCUs().empty())
    {
        for (int i = 0; i < 4; i++) {
            s = xReadCU(vPCInfo, s, pcSequence, *pcCU.getSCUs()[i]);
        }
    }
    else
    {
        s = xReadCULeaf(vPCInfo, s, pcSequence, pcCU);
    }
    return s;
}