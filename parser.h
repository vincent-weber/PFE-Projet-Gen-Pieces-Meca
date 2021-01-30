#ifndef PARSER_H
#define PARSER_H

#include <QString>
#include <QDebug>
#include <QVector>

class Parser
{
public:
    Parser(QString sentence);

    QString sentence;

    void reader();
    QVector<QVector<float>> getCylinder(int *index);
    QVector<float> getParam(int *index);
};

#endif // PARSER_H
