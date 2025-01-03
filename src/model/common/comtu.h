#ifndef COMTU_H
#define COMTU_H
#include <vector>
class ComTU {
public:
    ComTU();
    std::vector<ComTU>& getTUs() { return m_apcTUs; }
    const std::vector<ComTU>& getTUs() const { return m_apcTUs; }
    short getX() { return m_iX; }
    void setX(short iX) { m_iX = iX; }
    short getY() { return m_iY; }
    void setY(short iY) { m_iY = iY; }
    short getSize() { return m_iSize; }
    void setSize(short iSize) { m_iSize = iSize; }
private:
    std::vector<ComTU> m_apcTUs;
    short m_iX;                                        ///< X Position in frame
    short m_iY;                                        ///< Y Position in frame
    short m_iSize;                               ///< CU Size
};
#endif // COMTU_H
