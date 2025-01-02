#ifndef COMPU_H
#define COMPU_H

#include <QVector>
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
private:
    ADD_CLASS_FIELD( int, iX, getX, setX )
    ADD_CLASS_FIELD( int, iY, getY, setY )
    ADD_CLASS_FIELD( int, iWidth, getWidth, setWidth )
    ADD_CLASS_FIELD( int, iHeight, getHeight, setHeight )
    ADD_CLASS_FIELD( PredMode, ePredMode, getPredMode, setPredMode )
    ADD_CLASS_FIELD( int, mergeIndex, getMergeIndex, setMergeIndex )
    ADD_CLASS_FIELD( int, iInterDir, getInterDir, setInterDir)
    ADD_CLASS_FIELD( int, iIntraDirLuma, getIntraDirLuma, setIntraDirLuma)
    ADD_CLASS_FIELD( int, iIntraDirChroma, getIntraDirChroma, setIntraDirChroma)
    ADD_CLASS_FIELD( std::vector<ComMV>, apcMVs, getMVs, setMVs)


};
#endif // COMPU_H
