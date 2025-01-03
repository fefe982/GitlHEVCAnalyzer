#ifndef ABSTRACTFILTER_H
#define ABSTRACTFILTER_H
#include <QString>
#include <QPainter>
#include <QtPlugin>
#include "model/common/comsequence.h"

class SequenceManager;
class DrawEngine;
class YUV420RGBBuffer;
class FilterLoader;
class SelectionManager;

/*!
 * \brief The FilterContext class
 * Parameters which will be sent to the filter plgins in AbstractFilter Interface
 * Basically it is just pointers to the objects in model, indicating the state of the system.
 */
struct FilterContext
{
    SequenceManager* pcSequenceManager;     /// sequences
    DrawEngine* pcDrawEngine;               /// draw engine
    YUV420RGBBuffer* pcBuffer;              /// yuv and rgb buffer
    FilterLoader* pcFilterLoader;           /// filter loader (all filters are here)
    SelectionManager* pcSelectionManager;   /// selection helper function
};

/*!
 * \brief The AbstractFilter class
 * Interface of the filter plugins
 */
class AbstractFilter {
public:
    AbstractFilter() {
        m_bEnable = false;
        m_strName = "UNKNOWN";
    }

    virtual ~AbstractFilter() {}

    /*!
     * \brief init is called as soon as loaded in
     * \param pcContext \see FilterContext
     * \return
     */
    virtual bool init([[maybe_unused]] FilterContext* pcContext) {
        return true;
    }

    /*!
     * \brief uninit is called before unload
     * \param pcContext \see FilterContext
     * \return
     */
    virtual bool uninit([[maybe_unused]] FilterContext* pcContext) {
        return true;
    }

    /*!
     * \brief config is called when user push the 'config' button in user interface (or 'config' command in command line)
     *        Generally, we suggest a GUI here for adjusting the parameters for filters.
     * \param pcContext \see FilterContext
     * \return
     */
    virtual bool config([[maybe_unused]] FilterContext* pcContext) {
        return true;
    }

    /*!
     * \brief drawFrame is called for every frame
     * \param pcContext \see FilterContext
     * \param pcPainter the QPainter of the QPixmap object which is being displayed on screen
     * \param pcSequence sequence which is selected as the currently displaying one
     * \param iPoc the POC of currently displaying frame (begin with 0)
     * \return true - success   false - fail
     */
    virtual bool drawFrame([[maybe_unused]] FilterContext* pcContext, [[maybe_unused]] QPainter* pcPainter,
        [[maybe_unused]] ComFrame* pcFrame, [[maybe_unused]] double dScale, [[maybe_unused]] QRect* pcScaledArea) {
        return true;
    }




    /*!
     * \brief drawTile is called for every frame
     * \param pcContext \see FilterContext
     * \param pcPainter the QPainter of the QPixmap object which is being displayed on screen
     * \param pcSequence sequence which is selected as the currently displaying one
     * \param iPoc the POC of currently displaying frame (begin with 0)
     * \return true - success   false - fail
     */
    virtual bool drawTile([[maybe_unused]] FilterContext* pcContext, [[maybe_unused]] QPainter* pcPainter, [[maybe_unused]] ComTile* pcTile, [[maybe_unused]] double dScale, [[maybe_unused]] QRect* pcScaledArea) {
        return true;
    }



    /*!
     * \brief drawCTU is called for each CTU (Coding Tree Unit, i.e. LCU)
     * \param pcContext \see FilterContext
     * \param pcPainter the QPainter of the QPixmap object which is being displayed on screen
     * \param pcCU the CTU(i.e. LCU) to be draw
     * \param dScale the scale of current display
     * \param pcScaledArea the scaled size of current PU
     * \return
     */
    virtual bool drawCTU([[maybe_unused]] FilterContext* pcContext, [[maybe_unused]] QPainter* pcPainter,
        [[maybe_unused]] ComCU* pcCTU, [[maybe_unused]] double dScale, [[maybe_unused]] QRect* pcScaledArea) {
        return true;
    }


    /*!
     * \brief drawCU is called for each leaf CU (each leaf node of the Coding Tree Unit )
     * \param pcContext \see FilterContext
     * \param pcPainter the QPainter of the QPixmap object which is being displayed on screen
     * \param pcCU the CU to be draw
     * \param dScale the scale of current display
     * \param pcScaledArea the scaled size of current PU
     * \return
     */
    virtual bool drawCU([[maybe_unused]] FilterContext* pcContext, [[maybe_unused]] QPainter* pcPainter,
        [[maybe_unused]] ComCU* pcCU, [[maybe_unused]] double dScale, [[maybe_unused]] QRect* pcScaledArea) {
        return true;
    }

    /*!
     * \brief drawPU
     * \param pcContext \see FilterContext
     * \param pcPainter the QPainter of the QPixmap object which is being displayed on screen
     * \param pcPU the PU to be draw
     * \param dScale the scale of current display
     * \param pcScaledArea the scaled size of current PU
     * \return
     */
    virtual bool drawPU([[maybe_unused]] FilterContext* pcContext, [[maybe_unused]] QPainter* pcPainter,
        [[maybe_unused]] ComPU* pcPU, [[maybe_unused]] double dScale, [[maybe_unused]] QRect* pcScaledArea) {
        return true;
    }

    /*!
     * \brief drawTU
     * \param pcContext \see FilterContext
     * \param pcPainter the QPainter of the QPixmap object which is being displayed on screen
     * \param pcTU the TU to be draw
     * \param dScale the scale of current display
     * \param pcScaledArea the scaled size of current PU
     * \return
     */
    virtual bool drawTU([[maybe_unused]] FilterContext* pcContext, [[maybe_unused]] QPainter* pcPainter,
        [[maybe_unused]] ComTU* pcTU, [[maybe_unused]] double dScale, [[maybe_unused]] QRect* pcScaledArea) {
        return true;
    }



    /*!
     * \brief mousePress when user press mouse button on the dispalyed frame
     * \param pcContext \see FilterContext
     * \param pcPainter the QPainter of the QPixmap object which is being displayed on screen
     * \param pcUnscaledPos position in the unscaled frame
     * \param pcScaledPos position in the scaled frame
     * \param dScale the scale of current display
     * \param eMouseBtn mouse button that is pressed
     * \return
     */
    virtual bool mousePress([[maybe_unused]] FilterContext* pcContext, [[maybe_unused]] QPainter* pcPainter, [[maybe_unused]] ComFrame* pcFrame,
        [[maybe_unused]] const QPointF* pcUnscaledPos, [[maybe_unused]] const QPointF* pcScaledPos,
        [[maybe_unused]] double dScale, [[maybe_unused]] Qt::MouseButton eMouseBtn) {
        return true;
    }

    /*!
     * \brief keyPress when user press a key
     * \param pcContext \see FilterContext
     * \param pcPainter the QPainter of the QPixmap object which is being displayed on screen
     * \param iKeyPressed position in the unscaled frame
     * \return
     */
    virtual bool keyPress([[maybe_unused]] FilterContext* pcContext, [[maybe_unused]] QPainter* pcPainter, [[maybe_unused]] ComFrame* pcFrame,
        [[maybe_unused]] int iKeyPressed) {
        return true;
    }

    const QString& getName() const { return m_strName; }
    void setName(QString strName) { m_strName = strName; }


    bool getEnable()const { return m_bEnable; }
    void setEnable(bool bEnable) { m_bEnable = bEnable; }

private:
    /*! This is the filter name displayed in the user interface
     */
    QString m_strName;
    /*! This is the switch for turn off or on this filter
     *  false - this filter will not be applied
     *  true  - this filter will be applied
     */
    bool m_bEnable;
};

/// This is required by the Qt plugin system.
Q_DECLARE_INTERFACE(AbstractFilter, "cn.edu.sysu.gitl.gitlhevcanalyzer.AbstractFilter")
Q_DECLARE_METATYPE(AbstractFilter*)

#endif // ABSTRACTFILTER_H
