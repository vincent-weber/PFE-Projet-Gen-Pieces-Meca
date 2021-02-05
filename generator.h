#ifndef GENERATOR_H
#define GENERATOR_H

#include <QHash>
#include <random>
#include <QDebug>
#include <QVector3D>
#include <QStringList>
#include "util.h"

class Generator
{
public:
    QString sentence;
    virtual void createRules() = 0;
    virtual void generate(QString part) = 0;
    static void initRules();
    static QHash<QString, QVector<QString>> rules;

    void createLeafRules(QString primitive_type, QString in, QVector3D param, QVector3D c, QVector3D rot);
    void computeSentence();
};

#endif // GENERATOR_H
