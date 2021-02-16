#include "anchorpoint.h"

AnchorPoint::AnchorPoint()
{

}

AnchorPoint::AnchorPoint(QVector3D c, QVector3D d, float max_accepted_size) : coords(c), direction(d), max_accepted_size(max_accepted_size) {
    is_active = true;
}
