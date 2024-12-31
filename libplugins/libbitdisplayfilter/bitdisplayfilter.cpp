#include "bitdisplayfilter.h"
#include "model/modellocator.h"
#include <QDebug>
BitDisplayFilter::BitDisplayFilter(QObject *parent) :
    QObject(parent)
{
    setName("Bit Heatmap Display");
}

bool BitDisplayFilter::init(FilterContext* pcContext)
{
    m_dLCUAvgBit = 0;
    ComSequence* pcSeq = pcContext->pcSequenceManager->getCurrentSequence();
    if(pcSeq == NULL)
        return true;

    foreach( ComFrame* pcFrame, pcSeq->getFramesInDisOrder())
        foreach( ComCU* pcCU, pcFrame->getLCUs() )
            m_dLCUAvgBit += pcCU->getBitCount();
    m_dLCUAvgBit /= pcSeq->getFramesInDisOrder().size()*(pcSeq->getFramesInDisOrder().at(0)->getLCUs().size());

    return true;

}

bool BitDisplayFilter::drawCTU  (FilterContext *, QPainter *pcPainter,
                                ComCU *pcCTU, double, QRect *pcScaledArea)
{
    int iClip = VALUE_CLIP(240,359,pcCTU->getBitCount()/(m_dLCUAvgBit*5.0)*(359-240)+240);

    QColor cFill;
    double dHue = iClip/360.0;
    cFill.setHsvF(dHue, 1.0f, 1.0f, 0.6f);
    pcPainter->setBrush(QBrush(cFill));
    pcPainter->setPen(Qt::NoPen);
    pcPainter->drawRect(*pcScaledArea);
    return true;
}

