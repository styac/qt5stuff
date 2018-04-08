
#include "QyStyleOptionController.h"

QT_BEGIN_NAMESPACE

QyStyleOptionController::QyStyleOptionController()
    : QStyleOptionComplex(Version, SO_Slider)
    , orientation(Qt::Horizontal)
    , slotSize(16*16) // -- not needed
    , arcBegin(270*16 - slotSize) // -- not needed
    , qycStyle(QyC_HalfGauge) // TODO make a property
{
}

QyStyleOptionController::QyStyleOptionController(int version)
    : QStyleOptionComplex(version, SO_Slider)
    , orientation(Qt::Horizontal)
    , slotSize(16*16)
    , arcBegin(270*16 - slotSize )
{
}

QT_END_NAMESPACE
