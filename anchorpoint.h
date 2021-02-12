#ifndef ANCHORPOINT_H
#define ANCHORPOINT_H

#include <QVector3D>

class AnchorPoint
{
public:

    QVector3D coords;
    QVector3D direction;
    QVector3D rotation;
    QVector3D bounding_box;
    AnchorPoint();
    AnchorPoint(QVector3D coords, QVector3D direction, QVector3D rotation, QVector3D bounding_box);
};

#endif // ANCHORPOINT_H
