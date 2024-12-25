#include "TSysuAnalyzerOutput.h"

template <typename T>
void writeOstream(std::ostream& s, const std::string &key, T val, bool first = false) {
    if (!first) {
        s << ",";
    }
    s << '"' << key << "\":" << val;
}

TSysuAnalyzerOutput* TSysuAnalyzerOutput::m_instance = NULL;

TSysuAnalyzerOutput::TSysuAnalyzerOutput()
{

  m_cSpsOut.open     ("decoder_sps.txt",  ios::out);
  m_cPredOutput.open ("decoder_pred.txt", ios::out);
  m_cCUPUOutput.open ("decoder_cupu.txt", ios::out);
  m_cMVOutput.open   ("decoder_mv.txt",   ios::out);
  m_cMergeOutput.open("decoder_merge.txt",ios::out);
  m_cIntraOutput.open("decoder_intra.txt",ios::out);
  m_cTUOutput.open   ("decoder_tu.txt",   ios::out);
  m_cMEOutput.open   ("encoder_me.txt",   ios::out);
  m_cBitOutputLCU.open  ("decoder_bit_lcu.txt",  ios::out);
  m_cBitOutputSCU.open  ("decoder_bit_scu.txt",  ios::out);

#if ( HM_VERSION > 40)
  m_cTileOutPut.open("decoder_tile.txt", ios::out);
#endif


}


#if ( HM_VERSION > 40)
//write out tile info
void TSysuAnalyzerOutput::writeOutTileInfo(TComPic * pcPic)
{
    int iPoc = pcPic ->getPOC();
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
            int uiTileIdx = uiRowIdx * (iTileNumCols) + uiColumnIdx;

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

            m_cTileOutPut << "<" << iPoc << "," << (iTileNumCols) * (iTileNumRows) << ">"
                          << " " << uiFirstCUAddr << " " << uiTileWidth << " " << uiTileHeight
                          << endl;
        }
}

#endif




void TSysuAnalyzerOutput::writeOutCUInfo   ( TComDataCU* pcCU )
{
  Int iPoc = pcCU->getSlice()->getPOC();
  Int iAddr = pcCU->
#if HM_VERSION >= 160
              getCtuRsAddr();
#else
              getAddr();
#endif
  Int iTotalNumPart = pcCU->getTotalNumPart();


  m_cPredOutput << "<" << iPoc << "," << iAddr << ">" << " ";  ///< Write out prediction info
  m_cCUPUOutput << "<" << iPoc << "," << iAddr << ">" << " ";  ///< Write out CU & PU splitting info
  m_cMVOutput   << "<" << iPoc << "," << iAddr << ">" << " ";  ///< Write out me info
  m_cMergeOutput<< "<" << iPoc << "," << iAddr << ">" << " ";  ///< Write out merge mode info
  m_cIntraOutput<< "<" << iPoc << "," << iAddr << ">" << " ";  ///< Write out intra mode info
  m_cTUOutput   << "<" << iPoc << "," << iAddr << ">" << " ";  ///< Write out TU mode info
  m_cBitOutputLCU << "<" << iPoc << "," << iAddr << ">" << " ";  ///< Write out bit info
  m_cBitOutputSCU << "<" << iPoc << "," << iAddr << ">" << " ";  ///< Write out bit info
  m_cMEOutput   << "<" << iPoc << "," << iAddr << ">" << " ";  ///< Write out ME info  

  xWriteOutCUInfo  ( pcCU, iTotalNumPart, 0, 0 );   ///< Recursive write Prediction, CU, PU, Merge, Intra, ME
  m_cBitOutputLCU << pcCU->getTotalBits(); ///< Bit info
  for(int i = 0; i < aiCUBits.size(); i++)
    m_cBitOutputSCU << aiCUBits.at(i) << " "; ///< Bit info

  m_cPredOutput << endl;
  m_cCUPUOutput << endl;
  m_cMVOutput   << endl;
  m_cMergeOutput<< endl;
  m_cIntraOutput<< endl;
  m_cTUOutput   << endl;
  m_cBitOutputLCU  << endl;
  m_cBitOutputSCU  << endl;
  m_cMEOutput   << endl;
}

void TSysuAnalyzerOutput::xWriteOutCUInfo  ( TComDataCU* pcCU, Int iLength, Int iOffset, UInt iDepth )
{
  
  UChar* puhDepth    = pcCU->getDepth();
#if HM_VERSION >= 160
  SChar *
#else
  Char *
#endif
      puhPartSize
      = pcCU->getPartitionSize();

  TComMv rcMV;

  if( puhDepth[iOffset] <= iDepth )
  {
    ///< CU PU info
    m_cCUPUOutput << (Int)(puhPartSize[iOffset]) << " "; 

    ///< TU info
    xWriteOutTUInfo  ( pcCU, iLength, iOffset, 0 );   ///< Recursive write TU
    

    /// PU number in this leaf CU
    int iNumPart = 0;           

    switch ( puhPartSize[iOffset] )
    {
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
    for( int i = 0; i < iNumPart; i++ )
    {

      switch ( puhPartSize[iOffset] )
      {
      case SIZE_2NxN:
        iPartAddOffset = ( i == 0 )? 0 : iLength >> 1;
        break;
      case SIZE_Nx2N:
        iPartAddOffset = ( i == 0 )? 0 : iLength >> 2;
        break;
      case SIZE_NxN:
        iPartAddOffset = ( iLength >> 2 ) * i;
        break;
      case SIZE_2NxnU:    
        iPartAddOffset = ( i == 0 ) ? 0 : iLength >> 3;
        break;
      case SIZE_2NxnD:    
        iPartAddOffset = ( i == 0 ) ? 0 : (iLength >> 1) + (iLength >> 3);
        break;
      case SIZE_nLx2N:    
        iPartAddOffset = ( i == 0 ) ? 0 : iLength >> 4;
        break;
      case SIZE_nRx2N:   
        iPartAddOffset = ( i == 0 ) ? 0 : (iLength >> 2) + (iLength >> 4);
        break;
      default:
        assert ( puhPartSize[iOffset] == SIZE_2Nx2N );
        iPartAddOffset = 0;
        break;
      }

      /// Write prediction info (for historical reason, MODE_SKIP = 0, MODE_INTER = 1 ....) (SKIP mode removed after HM-8.0)
      PredMode ePred = pcCU->getPredictionMode(iOffset+iPartAddOffset);
      Int iPred = ePred; 
      if(ePred == MODE_INTER )
        iPred = 1;
      else if(ePred == MODE_INTRA)
        iPred = 2;
#if HM_VERSION < 160
      else if (ePred == MODE_NONE)
          iPred = 15;
#endif
      m_cPredOutput << iPred << " ";

      /// Write merge info
      Bool bMergeFlag = pcCU->getMergeFlag(iOffset+iPartAddOffset);      
      Int iMergeIndex = pcCU->getMergeIndex(iOffset+iPartAddOffset);
      if(bMergeFlag)
        m_cMergeOutput << iMergeIndex << " ";
      else
        m_cMergeOutput << -1 << " ";

      /// Write MV info
      Int iInterDir = pcCU->getInterDir(iOffset+iPartAddOffset);   ///< Inter direction: 0--Invalid, 1--List 0 only, 2--List 1 only, 3--List 0&1(bi-direction)
      int iRefIdx = -1;
      m_cMVOutput << iInterDir << " ";
      if( iInterDir == 0 )
      {
        // do nothing
      }
      else if ( iInterDir == 1 )
      {
        rcMV= pcCU->getCUMvField(REF_PIC_LIST_0)->getMv(iOffset+iPartAddOffset);	
        iRefIdx = pcCU->getCUMvField(REF_PIC_LIST_0)->getRefIdx(iOffset+iPartAddOffset);
        m_cMVOutput << pcCU->getSlice()->getRefPOC(REF_PIC_LIST_0, iRefIdx) << " " << rcMV.getHor() << " " << rcMV.getVer() << " ";
      }
      else if ( iInterDir == 2 )
      {
        rcMV= pcCU->getCUMvField(REF_PIC_LIST_1)->getMv(iOffset+iPartAddOffset);
        iRefIdx = pcCU->getCUMvField(REF_PIC_LIST_1)->getRefIdx(iOffset+iPartAddOffset);
        m_cMVOutput << pcCU->getSlice()->getRefPOC(REF_PIC_LIST_1, iRefIdx) << " " << rcMV.getHor() << " " << rcMV.getVer() << " ";
      }
      else if ( iInterDir == 3 )
      {
        rcMV= pcCU->getCUMvField(REF_PIC_LIST_0)->getMv(iOffset+iPartAddOffset);	
        iRefIdx = pcCU->getCUMvField(REF_PIC_LIST_0)->getRefIdx(iOffset+iPartAddOffset);
        m_cMVOutput << pcCU->getSlice()->getRefPOC(REF_PIC_LIST_0, iRefIdx) << " " << rcMV.getHor() << " " << rcMV.getVer() << " ";
        rcMV= pcCU->getCUMvField(REF_PIC_LIST_1)->getMv(iOffset+iPartAddOffset);
        iRefIdx = pcCU->getCUMvField(REF_PIC_LIST_1)->getRefIdx(iOffset+iPartAddOffset);
        m_cMVOutput << pcCU->getSlice()->getRefPOC(REF_PIC_LIST_1, iRefIdx) << " " << rcMV.getHor() << " " << rcMV.getVer() << " ";
      }    

      /// Write Intra info
#if HM_VERSION >= 160
      Int iLumaIntraDir = pcCU->getIntraDir(CHANNEL_TYPE_LUMA, iOffset + iPartAddOffset);
      Int iChromaIntraDir = pcCU->getIntraDir(CHANNEL_TYPE_CHROMA, iOffset + iPartAddOffset);
#else
      Int iLumaIntraDir = pcCU->getLumaIntraDir(iOffset + iPartAddOffset);
      Int iChromaIntraDir = pcCU->getChromaIntraDir(iOffset + iPartAddOffset);
#endif
      m_cIntraOutput << iLumaIntraDir << " " << iChromaIntraDir << " ";

    } /// PU end
  }
  else
  {
    m_cCUPUOutput << "99" << " ";     ///< CU info
    for( UInt i = 0; i < 4; i++ )
    {
      xWriteOutCUInfo  ( pcCU, iLength/4, iOffset+iLength/4*i, iDepth+1);
    }
  }
}


Void TSysuAnalyzerOutput::xWriteOutTUInfo  ( TComDataCU* pcCU, Int iLength, Int iOffset, UInt iDepth)
{
  UChar* puhTranIdx  = pcCU->getTransformIdx();
  if( puhTranIdx[iOffset] <= iDepth )
  {
    /// Write TU info
    m_cTUOutput << (Int)(puhTranIdx[iOffset]) << " ";
  }
  else
  {
    m_cTUOutput << "99" << " ";     
    for( UInt i = 0; i < 4; i++ )
    {
      xWriteOutTUInfo  ( pcCU, iLength/4, iOffset+iLength/4*i, iDepth+1);
    }
  }
}

Void TSysuAnalyzerOutput::writeOutSps   ( TComSPS* pcSPS )
{
    m_cSpsOut << "{";
    writeOstream(m_cSpsOut, "HM_VERSION", HM_VERSION, true);
    writeOstream(m_cSpsOut, "ResolutionX", pcSPS->getPicWidthInLumaSamples()
        - pcSPS->getConformanceWindow().getWindowLeftOffset()
        - pcSPS->getConformanceWindow().getWindowRightOffset());
    writeOstream(m_cSpsOut, "ResolutionY", pcSPS->getPicHeightInLumaSamples()
        - pcSPS->getConformanceWindow().getWindowTopOffset()
        - pcSPS->getConformanceWindow().getWindowBottomOffset());
    writeOstream(m_cSpsOut, "MaxCuSize", pcSPS->getMaxCUHeight());
    writeOstream(m_cSpsOut, "MaxCuDepth", pcSPS->getMaxTotalCUDepth());
    writeOstream(m_cSpsOut, "MaxInterTUDepth", pcSPS->getQuadtreeTUMaxDepthInter());
    writeOstream(m_cSpsOut, "MaxIntraTUDepth", pcSPS->getQuadtreeTUMaxDepthIntra());
    writeOstream(m_cSpsOut, "InputBitDepth", pcSPS->getBitDepth(CHANNEL_TYPE_LUMA));
    writeOstream(m_cSpsOut, "vui_parameters_present_flag", pcSPS->getVuiParametersPresentFlag());
    if (pcSPS->getVuiParametersPresentFlag()) {
        auto vui = pcSPS->getVuiParameters();
        writeOstream(m_cSpsOut, "video_signal_type_present_flag", vui->getVideoSignalTypePresentFlag());
        if (vui->getVideoSignalTypePresentFlag()) {
            writeOstream(m_cSpsOut, "video_full_range_flag", vui->getVideoFullRangeFlag());
            writeOstream(m_cSpsOut, "colour_description_present_flag", vui->getColourDescriptionPresentFlag());
            if (vui->getColourDescriptionPresentFlag()) {
                writeOstream(m_cSpsOut, "matrix_coeffs", vui->getMatrixCoefficients());
            }
        }
    }
    m_cSpsOut << "}" << std::endl;
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


TSysuAnalyzerOutput::~TSysuAnalyzerOutput()
{
  m_cCUPUOutput.close();
  m_cMVOutput.close();
  m_cPredOutput.close();
  m_cSpsOut.close();
  m_cIntraOutput.close();
  m_cTUOutput.close();
  m_cBitOutputLCU.close();
  m_cBitOutputSCU.close();
  m_cMEOutput.close();

#if (HM_VERSION >40)
   m_cTileOutPut.close();
#endif
}
