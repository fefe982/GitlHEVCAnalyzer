#include "TSysuAnalyzerOutput.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"

TSysuAnalyzerOutput* TSysuAnalyzerOutput::m_instance = NULL;

TSysuAnalyzerOutput::TSysuAnalyzerOutput() {
    m_cGeneralOut.open("decoder_general.txt", ios::out);
    m_cSpsOut.open("decoder_sps.txt", ios::out);
    m_cVpsOut.open("decoder_vps.txt", ios::out);
    m_decoderBinOut.open("decoder_bin.txt", ios::out | ios::binary);
#if WRITE_TEXT_OUTPUT
    m_cPredOutput.open("decoder_pred.txt", ios::out);
    m_cCUPUOutput.open("decoder_cupu.txt", ios::out);
    m_cMVOutput.open("decoder_mv.txt", ios::out);
    m_cMergeOutput.open("decoder_merge.txt", ios::out);
    m_cIntraOutput.open("decoder_intra.txt", ios::out);
    m_cTUOutput.open("decoder_tu.txt", ios::out);
    m_cMEOutput.open("encoder_me.txt", ios::out);
    m_cBitOutputLCU.open("decoder_bit_lcu.txt", ios::out);
    m_cBitOutputSCU.open("decoder_bit_scu.txt", ios::out);
#endif
}

#if ( HM_VERSION > 40)
//write out tile info
void TSysuAnalyzerOutput::writeOutTileInfo(TComPic* pcPic) {
    int iPoc = pcPic->getPOC();
    int iTileNumRows = pcPic->getPicSym()->
#if HM_VERSION >= 160
        getNumTileRowsMinus1()
#else
        getNumRowsMinus1()
#endif
        + 1;
    int iTileNumCols = pcPic->getPicSym()->
#if HM_VERSION >= 160
        getNumTileColumnsMinus1()
#else
        getNumColumnsMinus1()
#endif
        + 1;

    for (int uiRowIdx = 0; uiRowIdx < iTileNumRows; uiRowIdx++)
        for (int uiColumnIdx = 0; uiColumnIdx < iTileNumCols; uiColumnIdx++) {
            int uiTileIdx = uiRowIdx * (iTileNumCols)+uiColumnIdx;

            //information for each tile
            int uiTileWidth = 0;
            int uiTileHeight = 0;
            int uiFirstCUAddr = 0;

            uiTileWidth = pcPic->getPicSym()->getTComTile(uiTileIdx)->
#if HM_VERSION >= 160
                getTileWidthInCtus();
#else
                getTileWidth();
#endif
            uiTileHeight = pcPic->getPicSym()->getTComTile(uiTileIdx)->
#if HM_VERSION >= 160
                getTileHeightInCtus();
#else
                getTileHeight();
#endif

            uiFirstCUAddr = pcPic->getPicSym()->getTComTile(uiTileIdx)->
#if HM_VERSION >= 160
                getFirstCtuRsAddr();
#else
                getFirstCUAddr();
#endif
#if WRITE_TEXT_OUTPUT
            m_cTileOutPut << "<" << iPoc << "," << (iTileNumCols) * (iTileNumRows) << ">"
                << " " << uiFirstCUAddr << " " << uiTileWidth << " " << uiTileHeight
                << endl;
        }
#endif
}

#endif

namespace {
    void write_short(std::ostream& os, short i) {
        os.write((char*)&i, sizeof(short));
    }
}
void TSysuAnalyzerOutput::writeOutCUInfo(TComDataCU* pcCU) {
    Int iPoc = pcCU->getSlice()->getPOC();
    Int iAddr = pcCU->
#if HM_VERSION >= 160
        getCtuRsAddr();
#else
        getAddr();
#endif
    Int iTotalNumPart = pcCU->getTotalNumPart();

    write_short(m_decoderBinOut, iPoc);
    write_short(m_decoderBinOut, iAddr);
#if WRITE_TEXT_OUTPUT
    m_cPredOutput << "<" << iPoc << "," << iAddr << ">" << " ";  ///< Write out prediction info
    m_cCUPUOutput << "<" << iPoc << "," << iAddr << ">" << " ";  ///< Write out CU & PU splitting info
    m_cMVOutput << "<" << iPoc << "," << iAddr << ">" << " ";  ///< Write out me info
    m_cMergeOutput << "<" << iPoc << "," << iAddr << ">" << " ";  ///< Write out merge mode info
    m_cIntraOutput << "<" << iPoc << "," << iAddr << ">" << " ";  ///< Write out intra mode info
    m_cTUOutput << "<" << iPoc << "," << iAddr << ">" << " ";  ///< Write out TU mode info
    m_cBitOutputLCU << "<" << iPoc << "," << iAddr << ">" << " ";  ///< Write out bit info
    m_cBitOutputSCU << "<" << iPoc << "," << iAddr << ">" << " ";  ///< Write out bit info
    m_cMEOutput << "<" << iPoc << "," << iAddr << ">" << " ";  ///< Write out ME info  
#endif
    CUInfo cuInfo;
    xWriteOutCUInfo(pcCU, iTotalNumPart, 0, 0, cuInfo);   ///< Recursive write Prediction, CU, PU, Merge, Intra, ME
#if WRITE_TEXT_OUTPUT
    m_cBitOutputLCU << pcCU->getTotalBits(); ///< Bit info
#endif
    cuInfo.push_bitLCU(pcCU->getTotalBits()); ///< Bit info
    for (int i = 0; i < aiCUBits.size(); i++) {
        cuInfo.push_bitSCU(aiCUBits.at(i)); ///< Bit info
#if WRITE_TEXT_OUTPUT
        m_cBitOutputSCU << aiCUBits.at(i) << " "; ///< Bit info
#endif
    }
    cuInfo.write_all(m_decoderBinOut);
#if WRITE_TEXT_OUTPUT
    m_cPredOutput << endl;
    m_cCUPUOutput << endl;
    m_cMVOutput << endl;
    m_cMergeOutput << endl;
    m_cIntraOutput << endl;
    m_cTUOutput << endl;
    m_cBitOutputLCU << endl;
    m_cBitOutputSCU << endl;
    m_cMEOutput << endl;
#endif
}

void TSysuAnalyzerOutput::xWriteOutCUInfo(TComDataCU* pcCU, Int iLength, Int iOffset, UInt iDepth, CUInfo& cuInfo) {

    UChar* puhDepth = pcCU->getDepth();
#if HM_VERSION >= 160
    SChar*
#else
    Char*
#endif
        puhPartSize
        = pcCU->getPartitionSize();

    TComMv rcMV;

    if (puhDepth[iOffset] <= iDepth) {
        ///< CU PU info
        cuInfo.push_cupu(puhPartSize[iOffset]);
#if WRITE_TEXT_OUTPUT
        m_cCUPUOutput << (Int)(puhPartSize[iOffset]) << " ";
#endif

        ///< TU info
        xWriteOutTUInfo(pcCU, iLength, iOffset, 0, cuInfo);   ///< Recursive write TU


        /// PU number in this leaf CU
        int iNumPart = 0;

        switch (puhPartSize[iOffset]) {
        case SIZE_2Nx2N:    iNumPart = 1; break;
        case SIZE_2NxN:     iNumPart = 2; break;
        case SIZE_Nx2N:     iNumPart = 2; break;
        case SIZE_NxN:      iNumPart = 4; break;
        case SIZE_2NxnU:    iNumPart = 2; break;
        case SIZE_2NxnD:    iNumPart = 2; break;
        case SIZE_nLx2N:    iNumPart = 2; break;
        case SIZE_nRx2N:    iNumPart = 2; break;
        default:    iNumPart = 0;  /*assert(0);*/  break;  ///< out of boundery
        }

        /// Traverse every PU
        int iPartAddOffset = 0;   ///< PU offset
        for (int i = 0; i < iNumPart; i++) {

            switch (puhPartSize[iOffset]) {
            case SIZE_2NxN:
                iPartAddOffset = (i == 0) ? 0 : iLength >> 1;
                break;
            case SIZE_Nx2N:
                iPartAddOffset = (i == 0) ? 0 : iLength >> 2;
                break;
            case SIZE_NxN:
                iPartAddOffset = (iLength >> 2) * i;
                break;
            case SIZE_2NxnU:
                iPartAddOffset = (i == 0) ? 0 : iLength >> 3;
                break;
            case SIZE_2NxnD:
                iPartAddOffset = (i == 0) ? 0 : (iLength >> 1) + (iLength >> 3);
                break;
            case SIZE_nLx2N:
                iPartAddOffset = (i == 0) ? 0 : iLength >> 4;
                break;
            case SIZE_nRx2N:
                iPartAddOffset = (i == 0) ? 0 : (iLength >> 2) + (iLength >> 4);
                break;
            default:
                assert(puhPartSize[iOffset] == SIZE_2Nx2N);
                iPartAddOffset = 0;
                break;
            }

            /// Write prediction info (for historical reason, MODE_SKIP = 0, MODE_INTER = 1 ....) (SKIP mode removed after HM-8.0)
            PredMode ePred = pcCU->getPredictionMode(iOffset + iPartAddOffset);
            Int iPred = ePred;
            if (ePred == MODE_INTER)
                iPred = 1;
            else if (ePred == MODE_INTRA)
                iPred = 2;
#if HM_VERSION < 160
            else if (ePred == MODE_NONE)
                iPred = 15;
#endif
            cuInfo.push_pred(iPred);
#if WRITE_TEXT_OUTPUT
            m_cPredOutput << iPred << " ";
#endif

            /// Write merge info
            Bool bMergeFlag = pcCU->getMergeFlag(iOffset + iPartAddOffset);
            Int iMergeIndex = pcCU->getMergeIndex(iOffset + iPartAddOffset);
            cuInfo.push_merge(bMergeFlag ? iMergeIndex : -1);
#if WRITE_TEXT_OUTPUT
            if (bMergeFlag)
                m_cMergeOutput << iMergeIndex << " ";
            else
                m_cMergeOutput << -1 << " ";
#endif

            /// Write MV info
            Int iInterDir = pcCU->getInterDir(iOffset + iPartAddOffset);   ///< Inter direction: 0--Invalid, 1--List 0 only, 2--List 1 only, 3--List 0&1(bi-direction)
            int iRefIdx = -1;
            cuInfo.push_mv(iInterDir);
#if WRITE_TEXT_OUTPUT
            m_cMVOutput << iInterDir << " ";
#endif
            if (iInterDir == 0) {
                // do nothing
            } else if (iInterDir == 1) {
                rcMV = pcCU->getCUMvField(REF_PIC_LIST_0)->getMv(iOffset + iPartAddOffset);
                iRefIdx = pcCU->getCUMvField(REF_PIC_LIST_0)->getRefIdx(iOffset + iPartAddOffset);
#if WRITE_TEXT_OUTPUT
                m_cMVOutput << pcCU->getSlice()->getRefPOC(REF_PIC_LIST_0, iRefIdx) << " " << rcMV.getHor() << " " << rcMV.getVer() << " ";
#endif
                cuInfo.push_mv(pcCU->getSlice()->getRefPOC(REF_PIC_LIST_0, iRefIdx));
                cuInfo.push_mv(rcMV.getHor());
                cuInfo.push_mv(rcMV.getVer());
            } else if (iInterDir == 2) {
                rcMV = pcCU->getCUMvField(REF_PIC_LIST_1)->getMv(iOffset + iPartAddOffset);
                iRefIdx = pcCU->getCUMvField(REF_PIC_LIST_1)->getRefIdx(iOffset + iPartAddOffset);
#if WRITE_TEXT_OUTPUT
                m_cMVOutput << pcCU->getSlice()->getRefPOC(REF_PIC_LIST_1, iRefIdx) << " " << rcMV.getHor() << " " << rcMV.getVer() << " ";
#endif
                cuInfo.push_mv(pcCU->getSlice()->getRefPOC(REF_PIC_LIST_1, iRefIdx));
                cuInfo.push_mv(rcMV.getHor());
                cuInfo.push_mv(rcMV.getVer());
            } else if (iInterDir == 3) {
                rcMV = pcCU->getCUMvField(REF_PIC_LIST_0)->getMv(iOffset + iPartAddOffset);
                iRefIdx = pcCU->getCUMvField(REF_PIC_LIST_0)->getRefIdx(iOffset + iPartAddOffset);
#if WRITE_TEXT_OUTPUT
                m_cMVOutput << pcCU->getSlice()->getRefPOC(REF_PIC_LIST_0, iRefIdx) << " " << rcMV.getHor() << " " << rcMV.getVer() << " ";
#endif
                cuInfo.push_mv(pcCU->getSlice()->getRefPOC(REF_PIC_LIST_0, iRefIdx));
                cuInfo.push_mv(rcMV.getHor());
                cuInfo.push_mv(rcMV.getVer());
                rcMV = pcCU->getCUMvField(REF_PIC_LIST_1)->getMv(iOffset + iPartAddOffset);
                iRefIdx = pcCU->getCUMvField(REF_PIC_LIST_1)->getRefIdx(iOffset + iPartAddOffset);
#if WRITE_TEXT_OUTPUT
                m_cMVOutput << pcCU->getSlice()->getRefPOC(REF_PIC_LIST_1, iRefIdx) << " " << rcMV.getHor() << " " << rcMV.getVer() << " ";
#endif
                cuInfo.push_mv(pcCU->getSlice()->getRefPOC(REF_PIC_LIST_1, iRefIdx));
                cuInfo.push_mv(rcMV.getHor());
                cuInfo.push_mv(rcMV.getVer());
            }

            /// Write Intra info
#if HM_VERSION >= 160
            Int iLumaIntraDir = pcCU->getIntraDir(CHANNEL_TYPE_LUMA, iOffset + iPartAddOffset);
            Int iChromaIntraDir = pcCU->getIntraDir(CHANNEL_TYPE_CHROMA, iOffset + iPartAddOffset);
#else
            Int iLumaIntraDir = pcCU->getLumaIntraDir(iOffset + iPartAddOffset);
            Int iChromaIntraDir = pcCU->getChromaIntraDir(iOffset + iPartAddOffset);
#endif
#if WRITE_TEXT_OUTPUT
            m_cIntraOutput << iLumaIntraDir << " " << iChromaIntraDir << " ";
#endif
            cuInfo.push_intra(iLumaIntraDir);
            cuInfo.push_intra(iChromaIntraDir);
        } /// PU end
    } else {
#if WRITE_TEXT_OUTPUT
        m_cCUPUOutput << "99" << " ";     ///< CU info
#endif
        cuInfo.push_cupu(99);     ///< CU info
        for (UInt i = 0; i < 4; i++) {
            xWriteOutCUInfo(pcCU, iLength / 4, iOffset + iLength / 4 * i, iDepth + 1, cuInfo);
        }
    }
}


Void TSysuAnalyzerOutput::xWriteOutTUInfo(TComDataCU* pcCU, Int iLength, Int iOffset, UInt iDepth, CUInfo& cuInfo) {
    UChar* puhTranIdx = pcCU->getTransformIdx();
    if (puhTranIdx[iOffset] <= iDepth) {
        /// Write TU info
#if WRITE_TEXT_OUTPUT
        m_cTUOutput << (Int)(puhTranIdx[iOffset]) << " ";
#endif
        cuInfo.push_tu(puhTranIdx[iOffset]);
    } else {
#if WRITE_TEXT_OUTPUT
        m_cTUOutput << "99" << " ";
#endif
        cuInfo.push_tu(99);
        for (UInt i = 0; i < 4; i++) {
            xWriteOutTUInfo(pcCU, iLength / 4, iOffset + iLength / 4 * i, iDepth + 1, cuInfo);
        }
    }
}

Void TSysuAnalyzerOutput::writeOutSps   ( TComSPS* pcSPS )
{
    rapidjson::StringBuffer sb;
    rapidjson::Writer w(sb);
    rapidjson::Document doc(rapidjson::kObjectType);
    doc.AddMember("HM_VERSION", HM_VERSION, doc.GetAllocator());
    doc.AddMember("ResolutionX", pcSPS->getPicWidthInLumaSamples()
        - pcSPS->getConformanceWindow().getWindowLeftOffset()
        - pcSPS->getConformanceWindow().getWindowRightOffset(), doc.GetAllocator());
    doc.AddMember("ResolutionY", pcSPS->getPicHeightInLumaSamples()
        - pcSPS->getConformanceWindow().getWindowTopOffset()
        - pcSPS->getConformanceWindow().getWindowBottomOffset(), doc.GetAllocator());
    doc.AddMember("MaxCuSize", pcSPS->getMaxCUHeight(), doc.GetAllocator());
    doc.AddMember("MaxCuDepth", pcSPS->getMaxTotalCUDepth(), doc.GetAllocator());
    doc.AddMember("MaxInterTUDepth", pcSPS->getQuadtreeTUMaxDepthInter(), doc.GetAllocator());
    doc.AddMember("MaxIntraTUDepth", pcSPS->getQuadtreeTUMaxDepthIntra(), doc.GetAllocator());
    doc.AddMember("InputBitDepth", pcSPS->getBitDepth(CHANNEL_TYPE_LUMA), doc.GetAllocator());
    if (pcSPS->getVuiParametersPresentFlag()) {
        auto vui = pcSPS->getVuiParameters();
        if (vui->getVideoSignalTypePresentFlag()) {
            doc.AddMember("video_full_range_flag", vui->getVideoFullRangeFlag(), doc.GetAllocator());
            if (vui->getColourDescriptionPresentFlag()) {
                doc.AddMember("matrix_coeffs", vui->getMatrixCoefficients(), doc.GetAllocator());
            }
        }
        auto timing_info = vui->getTimingInfo();
        if (timing_info->getTimingInfoPresentFlag()) {
            doc.AddMember("vui_num_units_in_tick", timing_info->getNumUnitsInTick(), doc.GetAllocator());
            doc.AddMember("vui_time_scale", timing_info->getTimeScale(), doc.GetAllocator());
        }
    }
    doc.Accept(w);
    m_cSpsOut << sb.GetString() << std::endl;
#if (HM_VERSION >= 100)
    m_cSpsOut << "Resolution:"
              << (pcSPS->getPicWidthInLumaSamples()
                  - pcSPS->getConformanceWindow().getWindowLeftOffset()
                  - pcSPS->getConformanceWindow().getWindowRightOffset())
              << "x"
              << (pcSPS->getPicHeightInLumaSamples()
                  - pcSPS->getConformanceWindow().getWindowTopOffset()
                  - pcSPS->getConformanceWindow().getWindowBottomOffset())
              << endl;
#else
  m_cSpsOut << "Resolution:"   << pcSPS->getWidth() << "x" << pcSPS->getHeight() << endl;
#endif

  m_cSpsOut << "Max CU Size:"  << pcSPS->getMaxCUHeight() << endl;
#if HM_VERSION >= 160
  m_cSpsOut << "Max CU Depth:" << pcSPS->getMaxTotalCUDepth() << endl;
#else
  m_cSpsOut << "Max CU Depth:" << pcSPS->getMaxCUDepth() << endl;
#endif
  m_cSpsOut << "Max Inter TU Depth:" << pcSPS->getQuadtreeTUMaxDepthInter() << endl;
  m_cSpsOut << "Max Intra TU Depth:" << pcSPS->getQuadtreeTUMaxDepthIntra() << endl;
#if HM_VERSION >= 160
  int iInputBitDepth = pcSPS->getBitDepth(CHANNEL_TYPE_LUMA);
#elif (HM_VERSION >= 100)
  int iInputBitDepth = pcSPS->getBitDepthY();
#else
  int iInputBitDepth = pcSPS->getBitDepth();
#endif

  m_cSpsOut << "Input Bit Depth:"  << iInputBitDepth  << endl;

#if HM_VERSION >= 100
  m_cSpsOut << "Input Chroma Format:" << pcSPS->getChromaFormatIdc() << endl;
  m_cSpsOut << "Input Conformance Window: l " << pcSPS->getConformanceWindow().getWindowLeftOffset()
            << ", r " << pcSPS->getConformanceWindow().getWindowRightOffset() << ", t "
            << pcSPS->getConformanceWindow().getWindowTopOffset() << ", b "
            << pcSPS->getConformanceWindow().getWindowBottomOffset() << endl;
#endif
  m_cSpsOut << "HM_VERSOIN: " << HM_VERSION << endl;
}

Void TSysuAnalyzerOutput::writeOutVps(TComVPS* pcVPS) {
    rapidjson::StringBuffer sb;
    rapidjson::Writer w(sb);
    rapidjson::Document doc(rapidjson::kObjectType);
    auto timingInfo = pcVPS->getTimingInfo();
    if (timingInfo->getTimingInfoPresentFlag()) {
        doc.AddMember("vps_num_nunits_in_tick", timingInfo->getNumUnitsInTick(), doc.GetAllocator());
        doc.AddMember("vps_time_scale", timingInfo->getTimeScale(), doc.GetAllocator());
    }
    doc.Accept(w);
    m_cVpsOut << sb.GetString() << std::endl;
}

Void TSysuAnalyzerOutput::writeOutGeneral(TComSlice* pcSlice, double decodeTime) {
    rapidjson::Document doc(rapidjson::kObjectType);
    doc.AddMember("POC", pcSlice->getPOC(), doc.GetAllocator());
    doc.AddMember("byte_count", pcSlice->getByteCount() + 4, doc.GetAllocator());
    doc.AddMember("QP", pcSlice->getSliceQp(), doc.GetAllocator());
    doc.AddMember("decode_time", decodeTime, doc.GetAllocator());
    rapidjson::Value v_ref_list(rapidjson::kArrayType);
    for (Int iRefList = 0; iRefList < 2; iRefList++) {
        rapidjson::Value v_ref_list_i(rapidjson::kArrayType);
        for (Int iRefIndex = 0; iRefIndex < pcSlice->getNumRefIdx(RefPicList(iRefList)); iRefIndex++) {
            v_ref_list_i.PushBack(pcSlice->getRefPOC(RefPicList(iRefList), iRefIndex), doc.GetAllocator());
        }
        v_ref_list.PushBack(std::move(v_ref_list_i), doc.GetAllocator());
    }
    doc.AddMember("ref_list", std::move(v_ref_list), doc.GetAllocator());
    rapidjson::StringBuffer sb;
    rapidjson::Writer w(sb);
    doc.Accept(w);
    m_cGeneralOut << sb.GetString() << std::endl;
}

TSysuAnalyzerOutput::~TSysuAnalyzerOutput() = default;