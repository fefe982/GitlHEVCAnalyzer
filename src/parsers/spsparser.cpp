#include "spsparser.h"
#include <QRegExp>
#include "rapidjson/document.h"

/** --- SAMPLE TEXT ---
  * Resolution:176x144
  * Max CU Size:64
  * Max CU Depth:4
  * Min TU Depth:0
  * Max TU Depth:1
  * Input Bit Depth:8
  */
bool SpsParser::parseFile(QTextStream* pcInputStream, ComSequence* pcSequence)
{

    Q_ASSERT( pcSequence != NULL );

    QString strOneLine;

    strOneLine = pcInputStream->readLine();
    if (strOneLine[0] == '{') {
        rapidjson::Document doc;
        doc.Parse(strOneLine.toUtf8());

        pcSequence->setWidth(doc["ResolutionX"].GetInt());
        pcSequence->setHeight(doc["ResolutionY"].GetInt());
        pcSequence->setMaxCUSize(doc["MaxCuSize"].GetInt());
        pcSequence->setMaxCUDepth(doc["MaxCuDepth"].GetInt());
        pcSequence->setMaxInterTUDepth(doc["MaxInterTUDepth"].GetInt());
        pcSequence->setMaxIntraTUDepth(doc["MaxIntraTUDepth"].GetInt());
        pcSequence->setInputBitDepth(doc["InputBitDepth"].GetInt());
        pcSequence->setIsFullRange(doc.HasMember("video_full_range_flag") && doc["video_full_range_flag"].GetBool());
        if (!doc.HasMember("matrix_coeffs")) {
            qWarning("Video does not contain Matrix Coeffs, assuming BT709");
            pcSequence->setMatrixCoeffs(1);
        }
        else {
            pcSequence->setMatrixCoeffs(doc["matrix_coeffs"].GetInt());
        }
        if (!doc.HasMember("vui_num_units_in_tick")) {
            pcSequence->setNumUnitsInTick(1);
        } else {
            pcSequence->setNumUnitsInTick(doc["vui_num_units_in_tick"].GetInt());
        }
        if (!doc.HasMember("vui_time_scale")) {
            pcSequence->setTimeScale(60);
        } else {
            pcSequence->setTimeScale(doc["vui_time_scale"].GetInt());
        }
        return true;
    }

    QRegExp cMatchTarget;


    // Resolution:176x144
    cMatchTarget.setPattern("Resolution:([0-9]+)x([0-9]+)");
    while( !pcInputStream->atEnd() ) {
        if( cMatchTarget.indexIn(strOneLine) != -1 ) {
            int iWidth  = cMatchTarget.cap(1).toInt();
            int iHeight = cMatchTarget.cap(2).toInt();
            pcSequence->setWidth(iWidth);
            pcSequence->setHeight(iHeight);
            break;
        }
        strOneLine = pcInputStream->readLine();
    }



    // Max CU Size:64
    cMatchTarget.setPattern("Max CU Size:([0-9]+)");
    while( !pcInputStream->atEnd() )
    {
        strOneLine = pcInputStream->readLine();
        if( cMatchTarget.indexIn(strOneLine) != -1 ) {
            int iMaxCUSize = cMatchTarget.cap(1).toInt();
            pcSequence->setMaxCUSize(iMaxCUSize);
            break;
        }
    }

    // Max CU Depth:4
    cMatchTarget.setPattern("Max CU Depth:([0-9]+)");
    while( !pcInputStream->atEnd() )
    {
        strOneLine = pcInputStream->readLine();
        if( cMatchTarget.indexIn(strOneLine) != -1 ) {
            int iMaxCUDepth = cMatchTarget.cap(1).toInt();
            pcSequence->setMaxCUDepth(iMaxCUDepth);
            break;
        }
    }

    // Max Inter TU Depth:3
    cMatchTarget.setPattern("Max Inter TU Depth:([0-9]+)");
    while( !pcInputStream->atEnd() )
    {
        strOneLine = pcInputStream->readLine();
        if( cMatchTarget.indexIn(strOneLine) != -1 ) {
            int iMinTUDepth = cMatchTarget.cap(1).toInt();
            pcSequence->setMaxInterTUDepth(iMinTUDepth);
            break;
        }
    }

    // Max Intra TU Depth:3
    cMatchTarget.setPattern("Max Intra TU Depth:([0-9]+)");
    while( !pcInputStream->atEnd() )
    {
        strOneLine = pcInputStream->readLine();
        if( cMatchTarget.indexIn(strOneLine) != -1 ) {
            int iMaxTUDepth = cMatchTarget.cap(1).toInt();
            pcSequence->setMaxIntraTUDepth(iMaxTUDepth);
            break;
        }
    }

    // Input Bit Depth:8
    cMatchTarget.setPattern("Input Bit Depth:([0-9]+)");
    while( !pcInputStream->atEnd() )
    {
        strOneLine = pcInputStream->readLine();
        if( cMatchTarget.indexIn(strOneLine) != -1 ) {
            int iInputBitDepth = cMatchTarget.cap(1).toInt();
            pcSequence->setInputBitDepth(iInputBitDepth);
            break;
        }
    }

    qWarning("Video does not contain Matrix Coeffs, assuming BT709");
    pcSequence->setMatrixCoeffs(1);

    return true;
}

bool VpsParser::parseFile(QTextStream* pcInputStream, ComSequence* pcSequence) {
    Q_ASSERT(pcSequence != NULL);
    QString strOneLine;
    strOneLine = pcInputStream->readLine();
    rapidjson::Document doc;
    doc.Parse(strOneLine.toUtf8());
    if (doc.HasMember("vps_num_units_in_tick")) {
        pcSequence->setNumUnitsInTick(doc["vps_num_units_in_tick"].GetInt());
    }
    if (doc.HasMember("vps_time_scale")) {
        pcSequence->setTimeScale(doc["vps_time_scale"].GetInt());
    }
    return true;
}
