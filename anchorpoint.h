#ifndef ANCHORPOINT_H
#define ANCHORPOINT_H

#include <QVector3D>
#include "generator.h"

class AnchorPoint
{
public:

    QVector3D coords;
    QVector3D direction;
    QVector3D rotation;
    QVector3D bounding_box;

    bool is_active = false;
    Generator* owner_object;
    Generator* attached_object;

    AnchorPoint();
    AnchorPoint(QVector3D coords, QVector3D direction, QVector3D rotation, QVector3D bounding_box);
};

#endif // ANCHORPOINT_H
