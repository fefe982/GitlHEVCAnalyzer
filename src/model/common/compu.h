#ifndef COMPU_H
#define COMPU_H

#include "commv.h"

enum PredMode
{
  MODE_SKIP,            ///< SKIP mode
  MODE_INTER,           ///< inter-prediction mode
  MODE_INTRA,           ///< intra-prediction mode
  MODE_NONE = 15
};

class ComCU;

class ComPU
{
public:
    ComPU() :m_iX(-1), m_iY(-1), m_iWidth(-1), m_iHeight(-1), m_ePredMode(PredMode::MODE_NONE), m_mergeIndex(-1), m_iInterDir(-1), m_iIntraDirLuma(-1), m_iIntraDirChroma(-1)
    {
    }

    ~ComPU() = default;
    int getX() const { return m_iX; }
    void setX(int iX) { m_iX = iX; }
    int getY() const { return m_iY; }
    void setY(int iY) { m_iY = iY; }
    int getWidth() const { return m_iWidth; }
    void setWidth(int iWidth) { m_iWidth = iWidth; }
    int getHeight() const { return m_iHeight; }
    void setHeight(int iHeight) { m_iHeight = iHeight; }
    PredMode getPredMode() const { return m_ePredMode; }
    void setPredMode(PredMode ePredMode) { m_ePredMode = ePredMode; }
    int getMergeIndex() const { return m_mergeIndex; }
    void setMergeIndex(int mergeIndex) { m_mergeIndex = mergeIndex; }
    int getInterDir() const { return m_iInterDir; }
    void setInterDir(int iInterDir) { m_iInterDir = iInterDir; }
    int getIntraDirLuma() const { return m_iIntraDirLuma; }
    void setIntraDirLuma(int iIntraDirLuma) { m_iIntraDirLuma = iIntraDirLuma; }
    int getIntraDirChroma() const { return m_iIntraDirChroma; }
    void setIntraDirChroma(int iIntraDirChroma) { m_iIntraDirChroma = iIntraDirChroma; }
    const std::vector<ComMV>& getMVs()const { return m_apcMVs; }
    std::vector<ComMV>& getMVs() { return m_apcMVs; }
private:
    int m_iX, m_iY;
    int m_iWidth, m_iHeight;
    PredMode m_ePredMode;
    int m_mergeIndex;
    int m_iInterDir;
    int m_iIntraDirLuma;
    int m_iIntraDirChroma;
    std::vector<ComMV> m_apcMVs;
};
#endif // COMPU_H
