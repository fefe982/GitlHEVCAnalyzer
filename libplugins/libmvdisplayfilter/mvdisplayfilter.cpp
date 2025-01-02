#include "mvdisplayfilter.h"

MVDisplayFilter::MVDisplayFilter(QObject* parent) :
    QObject(parent)
{
    setName("MV Display");
    m_bShowRefPOC = false;

    QColor cBlue(Qt::blue);
    cBlue.setAlpha(200);
    QColor cRed(Qt::red);
    cRed.setAlpha(200);
    QColor cGreen(Qt::green);
    cGreen.setAlpha(200);

    /// MV pen
    m_cPenL[0].setColor(m_cConfig.getL0Color());
    m_cPenL[1].setColor(m_cConfig.getL1Color());

    /// text pen
    m_cPenText.setColor(cGreen);

    /// circle filling
    m_cCircleLFill[0].setStyle(Qt::SolidPattern);
    m_cCircleLFill[0].setColor(m_cConfig.getL0Color());
    m_cCircleLFill[1].setStyle(Qt::SolidPattern);
    m_cCircleLFill[1].setColor(m_cConfig.getL1Color());

    /// config dialog init
    m_cConfigDialog.setWindowTitle("MV Display Filter");
    m_cConfigDialog.addCheckbox("Show Zero MVs", "", &m_cConfig.getShowZeroMV());
    m_cConfigDialog.addCheckbox("Show MV Start Point", "", &m_cConfig.getShowMVOrigin());
    m_cConfigDialog.addColorPicker("L0 MV Color", &m_cConfig.getL0Color());
    m_cConfigDialog.addColorPicker("L1 MV Color", &m_cConfig.getL1Color());
    m_cConfigDialog.addSlider("MV Opaque", 0.1, 1.0, &m_cConfig.getOpaque());
}

bool MVDisplayFilter::config(FilterContext*)
{
    m_cConfigDialog.exec();
    /// L0
    m_cConfig.getL0Color().setAlphaF(m_cConfig.getOpaque());
    m_cPenL[0].setColor(m_cConfig.getL0Color());
    m_cCircleLFill[0].setColor(m_cConfig.getL0Color());

    /// L1
    m_cConfig.getL1Color().setAlphaF(m_cConfig.getOpaque());
    m_cPenL[1].setColor(m_cConfig.getL1Color());
    m_cCircleLFill[1].setColor(m_cConfig.getL1Color());

    return true;
}

bool MVDisplayFilter::drawPU(FilterContext*, QPainter* pcPainter,
    ComPU* pcPU, double dScale, QRect* pcScaledArea)
{
    int iInterDir = pcPU->getInterDir();
    QPoint cCenter = pcScaledArea->center();

    QFont cFont = pcPainter->font();
    cFont.setPointSize(10);
    pcPainter->setFont(cFont);

    if (iInterDir == 0)
    {
        /// Do nothing
    }
    else if (iInterDir == 1)  /// uni-directional prediction
    {
        /// Get MV of PU
        auto& pcMV = pcPU->getMVs()[0];
        drawMV(pcPU->getMVs()[0], pcPainter, cCenter, dScale, 0);
        if (m_bShowRefPOC)
            pcPainter->drawText(*pcScaledArea, Qt::AlignCenter, QString("L0 %1").arg(pcMV.getRefPOC()));
    }
    else if (iInterDir == 2)  /// uni-directional prediction
    {
        /// Get MV of PU
        auto& pcMV = pcPU->getMVs()[0];
        drawMV(pcPU->getMVs()[0], pcPainter, cCenter, dScale, 1);
        if (m_bShowRefPOC)
            pcPainter->drawText(*pcScaledArea, Qt::AlignCenter, QString("L1 %1").arg(pcMV.getRefPOC()));

    }
    else if (iInterDir == 3)  /// bi-directional prediction
    {
        /// Get MV of PU ( first direction )
        drawMV(pcPU->getMVs()[0], pcPainter, cCenter, dScale, 0);
        drawMV(pcPU->getMVs()[1], pcPainter, cCenter, dScale, 1);
        /// Get MV of PU ( second direction)
        if (m_bShowRefPOC)
            pcPainter->drawText(*pcScaledArea, Qt::AlignCenter, QString("L0 %1 L1 %2").arg(pcPU->getMVs()[0].getRefPOC()).arg(pcPU->getMVs()[1].getRefPOC()));
    }
    return true;

}

void MVDisplayFilter::drawMV(ComMV& pcMV, QPainter* pcPainter, QPoint& cCenter, double dScale, int dir)
{
    if (m_cConfig.getShowZeroMV() || !pcMV.isZero())
    {
        pcPainter->setPen(m_cPenL[dir]);
        if (m_cConfig.getShowMVOrigin())
        {
            pcPainter->setBrush(m_cCircleLFill[dir]);
            pcPainter->drawEllipse((QPointF)cCenter, 1.5, 1.5);
        }
        pcPainter->drawLine(cCenter, cCenter + QPoint(pcMV.getHor(), pcMV.getVer()) * dScale / 4);
    }
}
