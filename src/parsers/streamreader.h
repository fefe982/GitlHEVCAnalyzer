#include <QDebug>

#include <functional>
#include <iostream>
#include <string>
#include <vector>

class StreamReader {
public:
    template<typename T> static std::vector<std::vector<std::vector<T>>> parse(std::istream& pcInputStream, size_t frames, size_t cuCnt) {
        std::vector<std::vector<std::vector<T>>> fileStore(frames);
        size_t iLastPoc = (size_t)-1;
        size_t iDecOrder = (size_t)-1;
        size_t iCU = cuCnt;
        std::string line;
        while (std::getline(pcInputStream, line))
        {
            if (line.empty() || line[0] != '<') {
                continue;
            }
            char* endPos;
            int iPoc = std::strtol(line.data() + 1, &endPos, 10);
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
            fileStore[iDecOrder][iAddr].reserve((&line.back() - sPos) / 2);
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
};