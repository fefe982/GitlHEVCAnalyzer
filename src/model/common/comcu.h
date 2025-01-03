#ifndef COMCU_H
#define COMCU_H

#include "compu.h"
#include "commv.h"
#include "comtu.h"

class ComFrame;

enum PartSize
{
  SIZE_2Nx2N,           ///< symmetric motion partition,  2Nx2N
  SIZE_2NxN,            ///< symmetric motion partition,  2Nx N
  SIZE_Nx2N,            ///< symmetric motion partition,   Nx2N
  SIZE_NxN,             ///< symmetric motion partition,   Nx N

  SIZE_2NxnU,           ///< asymmetric motion partition, 2Nx( N/2) + 2Nx(3N/2)
  SIZE_2NxnD,           ///< asymmetric motion partition, 2Nx(3N/2) + 2Nx( N/2)
  SIZE_nLx2N,           ///< asymmetric motion partition, ( N/2)x2N + (3N/2)x2N
  SIZE_nRx2N,           ///< asymmetric motion partition, (3N/2)x2N + ( N/2)x2N

  SIZE_NONE = 15
};



class ComCU
{
public:
    ComCU();
    ~ComCU() = default;

    bool operator < (const ComCU& cOther) const
    {
        return (m_iAddr < cOther.m_iAddr);
    }
    std::vector<ComCU>& getSCUs() { return m_apcSCUs; }
    const std::vector<ComCU>& getSCUs()const { return m_apcSCUs; }
    PartSize getPartSize() const { return m_ePartSize; }
    void setPartSize(PartSize ePartSize) { m_ePartSize = ePartSize; }
    std::vector<ComPU>& getPUs() { return m_apcPUs; }
    const std::vector<ComPU>& getPUs() const { return m_apcPUs; }
    ComTU& getTURoot() { return m_cTURoot; }
    const ComTU& getTURoot() const { return m_cTURoot; }
    short getX() const { return m_iX; }
    void setX(short iX) { m_iX = iX; }
    short getY() const { return m_iY; }
    void setY(short iY) { m_iY = iY; }
    int getSize() const { return m_iSize; }
    void setSize(int iSize) { m_iSize = iSize; }
    int getAddr() const { return m_iAddr; }
    void setAddr(int iAddr) { m_iAddr = iAddr; }
    short getZorder() const { return m_iZorder; }
    void setZorder(short iZorder) { m_iZorder = iZorder; }
    short getDepth() const { return m_iDepth; }
    void setDepth(short iDepth) { m_iDepth = iDepth; }
    int getBitCount() const { return m_iBitCount; }
    void setBitCount(int iBitCount) { m_iBitCount = iBitCount; }
private:
    std::vector<ComCU> m_apcSCUs;
    PartSize m_ePartSize;
    std::vector<ComPU> m_apcPUs;
    ComTU m_cTURoot;
    short m_iX;
    short m_iY;                                        ///< Y Position in frame
    int m_iSize;                               ///< CU Size
    int m_iAddr;                               ///< Raster index of LCU (which the sub-CU belongs to)
    short m_iZorder;                         ///< Z-Order of CU
    short m_iDepth;                            ///< Depth of CU
    int m_iBitCount;                ///< Bits comsumed by this LCU

public:
    static int getPUNum(PartSize ePartSize);
    static void getPUOffsetAndSize(int        iLeafCUSize,
        PartSize   ePartSize,
        int        uiPUIdx,
        int& riXOffset,
        int& riYOffset,
        int& riWidth,
        int& riHeight);
};

#endif // COMCU_H
