#ifndef PARSER_H
#define PARSER_H

#include <QString>
#include <QDebug>
#include <QVector>



#include "cylinder.h"
#include "sphere.h"
#include "cuboid.h"
#include "primitive.h"
#include "boolean_op.h"

class Parser
{
public:
    Parser(QString sentence);

    QString sentence;
    std::vector<Primitive*> shapes;
    std::vector<Bool_op> ops;

    void reader();
    QVector<QVector<float>> getGeo(int *index);
    QVector<float> getParam(int *index);
};

#endif // PARSER_H
