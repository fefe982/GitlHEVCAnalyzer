#pragma once
#include <fstream>
#include <string>
#include <vector>


#include "TLibCommon/TComDataCU.h"
#include "TLibCommon/TComSlice.h"
#include "TLibDecoder/TDecCu.h"
#include "CUInfo.h"

#define WRITE_TEXT_OUTPUT 0

class TSysuAnalyzerOutput
{
public:
  TSysuAnalyzerOutput(void);
  ~TSysuAnalyzerOutput(void);

#if 0
  /// write out residual
  Void writeOutResiYUV (TDecCu* pcDecCU, TComDataCU* pcCU, UInt uiZorderIdx, UInt uiDepth);
#endif
 

  /// splitting mode
  Void writeOutCUInfo   ( TComDataCU* pcCU );
  Void xWriteOutCUInfo(TComDataCU* pcCU, Int iLength, Int iOffset, UInt iDepth, CUInfo& frameInfo);
  
  /// Sequence parameter set output
  Void writeOutSps         ( TComSPS* pcSPS );
  Void writeOutVps(TComVPS* pcVPS);


  ///write out tile info
  Void writeOutTileInfo(TComPic * pcPic);
  Void writeOutGeneral(TComSlice* pcSlice, double decodeTime);


  std::vector<int> aiCUBits;
  /*
  Void setAllDepthTo       ( TComDataCU* pcCU, UInt uiDepth );
  Bool compareSplitMode    ( TComDataCU* pcRecursive, TComDataCU* pcFast );

  Void printCUModeForLCU   ( TComDataCU* pcCU, Char* phMessage );
  Void xPrintCUModeForLCU  ( UChar* pcCU, Int iLength, UInt iDepth );
  */



  /// SINGLETON 
  static TSysuAnalyzerOutput* getInstance() { if( m_instance == NULL ) m_instance = new TSysuAnalyzerOutput(); return m_instance;}

private:
    Void xWriteOutTUInfo(const TComDataCU* pcCU, Int iLength, Int iOffset, UInt iDepth, CUInfo& cuInfo);
    Void xWriteOutTUInfoInner(const TComDataCU* pcCU, Int iLength, Int iOffset, UInt iDepth, UInt id, CUInfo& cuInfo);

  /// Decoder output ( extracted from bitstream )
  std::ofstream m_cGeneralOut;
  std::ofstream m_cSpsOut;          ///< SPS info
  std::ofstream m_cVpsOut;
  std::ofstream m_decoderBinOut;
  std::ostringstream m_frameBuffer{ std::ios::binary };
#if WRITE_TEXT_OUTPUT
  std::ofstream m_cPredOutput;      ///< Prediction mode info output
  std::ofstream m_cCUPUOutput;      ///< CU info output
  std::ofstream m_cMVOutput;        ///< MV info output
  std::ofstream m_cMergeOutput;     ///< Merge info output
  std::ofstream m_cIntraOutput;     ///< Intra info output
  std::ofstream m_cTUOutput;        ///< TU info output
  std::ofstream m_cBitOutputLCU;    ///< LCU bit consumption info output
  std::ofstream m_cBitOutputSCU;    ///< SCU bit consumption info output
  std::ofstream m_cTileOutPut;

  /// Encoder output ( extracted in the encoding process
  std::ofstream m_cMEOutput;    ///< ME info (search point number, SAD, cost, etc)
#endif
  static TSysuAnalyzerOutput* m_instance;

};
