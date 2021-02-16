#ifndef ANCHORPOINT_H
#define ANCHORPOINT_H

#include <QVector3D>

class Generator;

class AnchorPoint
{
public:

    QVector3D coords;
    QVector3D direction;
    float max_accepted_size;

    bool is_active = false;
    Generator* owner_object;
    Generator* attached_object;

    AnchorPoint();
    AnchorPoint(QVector3D coords, QVector3D direction, float max_accepted_size);
};

#endif // ANCHORPOINT_H
