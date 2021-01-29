#include "parser.h"

Parser::Parser(QString sentence){
    this->sentence = sentence;
}

//Mot possible cyl, cen, rot.
void Parser::reader(){

    int i = 0;
    int j = 0;

    QChar c, cc;


    while(i < sentence.size()){
        QString test = "";
        c = sentence.at(i);

        //Recupere les informations du cylindre;
        if(c == 'c' && sentence.at(i+1) == 'y'){
            j = i + 4;
            QVector<float> param = getParam(&j);
            i = j;
            qDebug() << "Cylindre :" << param;
        }
        if(c == 'c' && sentence.at(i+1) == 'e'){
            j = i + 4;
            QVector<float> param = getParam(&j);
            i = j;
            qDebug() << "Centre :" << param;
        }
        if(c == 'r'){
            j = i + 4;
            QVector<float> param = getParam(&j);
            i = j;
            qDebug() << "Rotation :" << param;
        }
        i++;
    }
}

QVector<float> Parser::getParam(int *index){
    QVector<float> param;
    int j = *index;
    QChar cc = sentence.at(j);
    QString test = "";

    while(sentence.at(j) != ')'){
        cc = sentence.at(j); j++;
        if(cc == ',') {
            param.push_back(test.toFloat()); //rad, longueur
            test = "";
        }
        else {
            test += cc;
        }
    }
    param.push_back(test.toFloat()); //prec

    return param;
}
