#include "yuv420rgbbuffer.h"
#include <QFile>
#include <QDebug>
#include <unordered_map>

std::unordered_map<int, std::pair<double, double>> mapMatrix = {
    {1, {0.2126, 0.0722}},
    {5, {0.0299, 0.0114}}
};

YUV420RGBBuffer::YUV420RGBBuffer()
{

    m_iBufferWidth = 0;
    m_iBufferHeight = 0;
    m_iFrameCount = -1;
    m_puhYUVBuffer = NULL;
    m_puhRGBBuffer = NULL;
    m_bIs16Bit = false;
    m_bFullRange = false;
    m_iMatrixCoeffs = 1;
}

YUV420RGBBuffer::~YUV420RGBBuffer()
{

    delete[] m_puhYUVBuffer;
    m_puhYUVBuffer = NULL;

    delete[] m_puhRGBBuffer;
    m_puhRGBBuffer = NULL;
}


bool YUV420RGBBuffer::openYUVFile( const QString& strYUVPath, int iWidth, int iHeight, bool bFullRange, int iMatrixCoeffs, bool bIs16Bit)
{
    /// if new size dosen't match current size, delete old one and create new one
    if( iWidth != m_iBufferWidth || iHeight != m_iBufferHeight || m_bIs16Bit != bIs16Bit)
    {
        int i16BitMulti = bIs16Bit?2:1;

        delete[] m_puhYUVBuffer;
        m_puhYUVBuffer = new uchar[((iWidth * iHeight * 3) / 2) * i16BitMulti];


        delete[] m_puhRGBBuffer;
        m_puhRGBBuffer = new uchar[iWidth * iHeight * 3];        

    }


    m_iBufferWidth = iWidth;
    m_iBufferHeight = iHeight;
    m_bIs16Bit = bIs16Bit;
    m_bFullRange = bFullRange;
    if (mapMatrix.count(iMatrixCoeffs) == 0) {
        qWarning() << QString("Matrix coeffs %1 not supported, default to BT709").arg(iMatrixCoeffs);
        iMatrixCoeffs = 1;
    }
    m_iMatrixCoeffs = iMatrixCoeffs;

    /// set YUV file reader
    if( !m_cIOYUV.openYUVFilePath(strYUVPath) )
    {
        qCritical() << "YUV Buffer Initialization Fail";
        return false;
    }


    return true;

}

QPixmap* YUV420RGBBuffer::getFrame(int iFrameCount)
{
    QPixmap* pcFramePixmap = NULL;

    if( xReadFrame(iFrameCount) )
    {
        QImage cFrameImg(m_puhRGBBuffer, m_iBufferWidth, m_iBufferHeight, QImage::Format_RGB888 );
        m_cFramePixmap = QPixmap::fromImage(cFrameImg);
        pcFramePixmap = &m_cFramePixmap;
    }
    else
    {
        qCritical() << "Read YUV File Failure.";
    }

    return pcFramePixmap;
}

bool YUV420RGBBuffer::xReadFrame(int iFrameCount)
{
    int i16BitMultiplier = ( m_bIs16Bit ? 2 : 1 );

    if( iFrameCount < 0 )
        return false;
    m_iFrameCount = iFrameCount;
    int iFrameSizeInByte = (m_iBufferWidth*m_iBufferHeight*3/2)*i16BitMultiplier;
    if( m_cIOYUV.seekTo(iFrameCount*(qint64)iFrameSizeInByte) == false )
        return false;
    int iReadBytes = 0;   ///read

    iReadBytes = m_cIOYUV.readOneFrame(m_puhYUVBuffer, (uint)iFrameSizeInByte);
    if(m_bIs16Bit)
    {
        x16to8BitClip(m_puhYUVBuffer, m_puhYUVBuffer, iReadBytes/i16BitMultiplier);
    }



    if( iReadBytes != iFrameSizeInByte )
    {
        qCritical() << "Read YUV Frame Error";
        return false;
    }
    else
    {
        /// YUV to RGB conversion
        xYuv2rgb(m_puhYUVBuffer, m_puhRGBBuffer, m_iBufferWidth, m_iBufferHeight);
        return true;
    }

}

/**
  *  \brief YUV to RGB conversion
  *
  *  http://www.fourcc.org/fccyvrgb.php
  *
  *  R = Y + 1.402 (Cr-128)
  *
  *  G = Y - 0.34414 (Cb-128) - 0.71414 (Cr-128)
  *
  *  B = Y + 1.772 (Cb-128)
  *
  *
  **/
void YUV420RGBBuffer::xYuv2rgb(uchar* puhYUV, uchar* puhRGB, int iWidth, int iHeight)
{
    int uiFrameSizeInPixel = iWidth*iHeight;
    uchar* const puhY = puhYUV;
    uchar* const puhU = puhYUV + uiFrameSizeInPixel;
    uchar* const puhV = puhYUV + uiFrameSizeInPixel*5/4;

    long lYOffset, lUVOffset;
    double iY, iU, iV;
    int tempR, tempG, tempB;
    const auto &krkb = mapMatrix[m_iMatrixCoeffs];
    double drv = 2.0 * (1 - krkb.first);
    double dbu = 2.0 * (1 - krkb.second);
    double dgv = -drv * krkb.first / (1 - krkb.first - krkb.second);
    double dgu = -dbu * krkb.second / (1 - krkb.first - krkb.second);

    uchar* iCurRgbPixelOffset = 0;
    for(int y = 0; y < iHeight; ++y)
    {
        for(int x = 0; x < iWidth; ++x)
        {
            lYOffset  = iWidth*y+x;
            lUVOffset = iWidth/2*(y/2)+(x/2);

            iY = puhY[lYOffset];
            iU = puhU[lUVOffset] - 128;
            iV = puhV[lUVOffset] - 128;

            if (!m_bFullRange) {
                iY = (iY - 16.0) / 219.0 * 255.0;
                iU = iU / 224.0 * 255.0;
                iV = iV / 224.0 * 255.0;
            }

            tempR = iY + drv * iV;
            tempG = iY + dgv * iV + dgu * iU;
            tempB = iY + dbu * iU;


            tempR = VALUE_CLIP(0,255,tempR);
            tempG = VALUE_CLIP(0,255,tempG);
            tempB = VALUE_CLIP(0,255,tempB);

            iCurRgbPixelOffset = puhRGB+3*(iWidth*y+x);
            *(iCurRgbPixelOffset)     = tempR;
            *(iCurRgbPixelOffset + 1) = tempG;
            *(iCurRgbPixelOffset + 2) = tempB;


        }
    }
}


void YUV420RGBBuffer::x16to8BitClip(uchar* puh8BitYUV, const uchar* puh16BitYUV,const long lSizeInUnitCount)
{
    qint16* pi16BitPelValue = NULL;
    for(int i = 0; i < lSizeInUnitCount; i++)
    {
        pi16BitPelValue = (qint16*)(puh16BitYUV+2*i);
        puh8BitYUV[i] = VALUE_CLIP(0,255,(*pi16BitPelValue)+128);
    }
}
