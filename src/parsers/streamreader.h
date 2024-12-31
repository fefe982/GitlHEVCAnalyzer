#include <QDebug>

#include <vector>

class StreamReader {
public:
    static std::vector<std::vector<std::vector<int>>> parse(std::istream& pcInputStream, size_t frames, size_t cuCnt);
};