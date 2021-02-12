#ifndef GENERATOR_H
#define GENERATOR_H

#include <QHash>
#include <random>
#include <QDebug>
#include <QVector3D>
#include <QStringList>
#include "util.h"
#include "anchorpoint.h"

class Generator
{
public:
    QString sentence;
    QString generator_name;
    QVector3D center;
    virtual void generate(QString part) = 0;
    static void initRules();
    static QHash<QString, QVector<QString>> rules;
    std::random_device rd_gen;

    QVector<QVector<AnchorPoint>> anchor_points;

    void createRules();
    float computeParameter(float param, std::random_device &rd, float min, float max);
    int computeParameter(int param, std::random_device &rd, int min, int max);
    QString createLeafRulesMultiple(QVector<QString>& primitives, QString op_bools, QVector<QVector3D>& params, QVector<QVector3D>& centers, QVector<QVector3D>& rots);
    void createLeafRulesSingle(QString primitive_type, QString in, QVector3D param, QVector3D c, QVector3D rot);
    void computeSentence();
};

#endif // GENERATOR_H
