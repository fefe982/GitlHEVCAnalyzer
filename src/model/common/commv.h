#ifndef COMMV_H
#define COMMV_H

#include "gitldef.h"
#include <qmath.h>
class ComMV
{
public:
    explicit ComMV() : m_iRefPoc(0), m_iHor(0), m_iVer(0) {}
    explicit ComMV(int iHor, int iVer) : m_iRefPoc(0), m_iHor(iHor), m_iVer(iVer) {}
    explicit ComMV(int iRefPoc, int iHor, int iVer) : m_iRefPoc(iRefPoc), m_iHor(iHor), m_iVer(iVer) {}

    int getLengthSquare() const
    {
        return (m_iHor * m_iHor + m_iVer * m_iVer);
    }

    double getLength() const
    {
        return qSqrt(m_iHor * m_iHor + m_iVer * m_iVer);
    }

    double getAngle() const
    {
        return qAtan2(m_iVer, m_iHor);
    }

    ComMV operator - (const ComMV& other) const
    {
        return ComMV(m_iHor - other.m_iHor, m_iVer - other.m_iVer);
    }

    ComMV operator / (int iScale) const
    {
        return ComMV(m_iHor / iScale, m_iVer / iScale);
    }

    bool isZero() const
    {
        return (m_iHor == 0 && m_iVer == 0);
    }

    int getRefPOC() const { return m_iRefPoc; }
    int getHor() const { return m_iHor; }
    int getVer() const { return m_iVer; }

    void setRefPOC(int iRefPoc) { m_iRefPoc = iRefPoc; }
    void setHor(int iHor) { m_iHor = iHor; }
    void setVer(int iVer) { m_iVer = iVer; }
private:
    int m_iRefPoc;
    int m_iHor;
    int m_iVer;
};

#endif // COMMV_H
