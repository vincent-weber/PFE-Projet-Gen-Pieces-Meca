#include "anchorpoint.h"

AnchorPoint::AnchorPoint()
{

}

AnchorPoint::AnchorPoint(QVector3D c, QVector3D d, QVector3D r, QVector3D bb) : coords(c), direction(d), rotation(r), bounding_box(bb) {}
