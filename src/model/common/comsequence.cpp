#include "comsequence.h"
#include "parsers/cupuparser.h"
#include "parsers/tuparser.h"
#include "parsers/predparser.h"
#include "parsers/mvparser.h"
#include "parsers/mergeparser.h"
#include "parsers/intraparser.h"
#include "parsers/bitparser.h"

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
    m_iNumUnitsInTick = 1;
    m_iTimeScale = 60;
}

int ComSequence::getNumberMaxCu() const {
    return ((m_iWidth + m_iMaxCUSize - 1) / m_iMaxCUSize) * ((m_iHeight + m_iMaxCUSize) / m_iMaxCUSize);
}

void ComSequence::addDelyedParser(std::unique_ptr<InfoParser> &&parser) {
    m_vDelayedParser.emplace_back(std::move(parser));
}

bool ComSequence::parseFrame(size_t iFrame) {
    bool res = true;
    for (auto& parser : m_vDelayedParser) {
        res == res && parser->parseFrame(iFrame);
    }
    return res;
}