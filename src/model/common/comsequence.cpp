#include "comsequence.h"


ComSequence::ComSequence()
{
    init();
}

ComSequence::~ComSequence()
{
    for( int i = 0; i < m_cFramesInDisOrder.size(); i++ )
    {
        delete m_cFramesInDisOrder.at(i);
    }
}

void ComSequence::init()
{
    /*! Frames in this sequence */
    for( int i = 0; i < m_cFramesInDisOrder.size(); i++ )
    {
        delete m_cFramesInDisOrder.at(i);
    }
    m_cFramesInDisOrder.clear();
    m_cFramesInDecOrder.clear();

    /*! Sequence general info */
    m_strFileName.clear();
    m_iWidth  = -1;
    m_iHeight = -1;    
    m_iTotalFrames = -1;
    m_iMaxCUSize = -1;
    m_iMaxCUDepth = -1;
    m_iMinTUDepth = -1;
    m_iMaxTUDepth = -1;

    /*! YUV Info -- Currently Displaying YUV*/
    m_eYUVRole = YUV_NONE;


    /*!
     * Optional info
     * Obsolescent
     */
    m_strEncoderVersion.clear();
    m_dTotalDecTime = -1;
    m_dPSNR = -1;
    m_dBitrate = -1;
    m_dTotalEncTime = -1;
    m_dSameCUModePercent = -1;
    m_dMeanCUDepthError = -1;
}

int ComSequence::getNumberMaxCu() const {
    return ((m_iWidth + m_iMaxCUSize - 1) / m_iMaxCUSize) * ((m_iHeight + m_iMaxCUSize) / m_iMaxCUSize);
}

void ComSequence::allocComCU(size_t sz) {
    m_vCUStore.resize(0);
    m_vCUStore.reserve(sz);
}

ComCU* ComSequence::newComCU(ComFrame* p) {
    Q_ASSERT(m_vCUStore.size() < m_vCUStore.capacity());
    m_vCUStore.emplace_back(p);
    return &m_vCUStore.back();
}

void ComSequence::allocComPU(size_t sz) {
    m_vPUStore.resize(0);
    m_vPUStore.reserve(sz);
}

ComPU* ComSequence::newComPU(ComCU* p) {
    Q_ASSERT(m_vPUStore.size() < m_vPUStore.capacity());
    m_vPUStore.emplace_back(p);
    return &m_vPUStore.back();
}

void ComSequence::allocComTU(size_t sz) {
    m_vTUStore.resize(0);
    m_vTUStore.reserve(sz);
}

ComTU* ComSequence::newComTU() {
    Q_ASSERT(m_vTUStore.size() < m_vTUStore.capacity());
    m_vTUStore.emplace_back();
    return &m_vTUStore.back();
}