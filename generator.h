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
    QStringList primitives_str;
    const float min_distance_between_anchor_points = 0.003f;
    float max_size;

    QVector3D center;
    QVector3D rotation;
    QVector3D direction;
    virtual void set_rotation(QString screw_part) = 0;
    virtual void set_center() = 0;
    virtual void set_anchor_points() = 0;
    void set_prev_anchor_point(AnchorPoint* anchor_point);
    float get_max_possible_size();

    std::random_device rd_gen;
    QVector<QVector<AnchorPoint>> anchor_points;
    AnchorPoint* anchor_point_prev_lvl = nullptr;

    QString base_sentence;
    QString sentence;
    QString generator_name;

    virtual void generateParams(QString part) = 0;
    virtual void generateRules(QString part) = 0;
    static void initRules();
    static QHash<QString, QVector<QString>> rules;


    void createParams();
    float computeParameter(float param, std::random_device &rd, float min, float max);
    int computeParameter(int param, std::random_device &rd, int min, int max);
    QString createLeafRulesMultiple(QVector<QString>& primitives, QString op_bools, QVector<QVector<float>>& params, QVector<QVector3D>& centers, QVector<QVector3D>& rots);
    void createLeafRulesSingle(QString primitive_type, QString in, QVector<float> param, QVector3D c, QVector3D rot);
    void computeSentence();
};

#endif // GENERATOR_H
