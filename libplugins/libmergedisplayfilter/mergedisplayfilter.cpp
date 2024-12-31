#include "mergedisplayfilter.h"
#include <QRect>

MergeDisplayFilter::MergeDisplayFilter(QObject *parent) :
    QObject(parent)
{
    setName("Merge Mode Display");
}

bool MergeDisplayFilter::drawPU   (FilterContext*, QPainter* pcPainter,
                                   ComPU *pcPU, double,  QRect* pcScaledArea)
{
    int iMergeIndex = pcPU->getMergeIndex();
    if( iMergeIndex == -1 )    ///< -1 = not merge mode for this PU
    {
        //do nothing
    }
    else
    {
        QColor cPUColor = QColor(Qt::green);
        cPUColor.setAlphaF(0.3f);
        pcPainter->setPen(Qt::NoPen);
        pcPainter->setBrush(QBrush(cPUColor));
        pcPainter->drawRect(*pcScaledArea);

    }
    return true;

}
