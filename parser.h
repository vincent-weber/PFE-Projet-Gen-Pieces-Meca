#ifndef PARSER_H
#define PARSER_H

#include <QString>
#include <QDebug>
#include <QVector>



#include "cylinder.h"

class Parser
{
public:
    Parser(QString sentence);

    QString sentence;
    std::vector<Cylinder*> cylinders;

    void reader();
    QVector<QVector<float>> getCylinder(int *index);
    QVector<float> getParam(int *index);
};

#endif // PARSER_H
