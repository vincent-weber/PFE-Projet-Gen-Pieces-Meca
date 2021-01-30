#include "parser.h"

Parser::Parser(QString sentence){
    this->sentence = sentence;
}

//Mot possible cyl, cen, rot.
void Parser::reader(){

    int i = 0;
    while(i < sentence.size()){

        //Recupere les informations du cylindre;
        if(sentence.at(i) == 'c' && sentence.at(i+1) == 'y'){
            QVector<QVector<float>> params = getCylinder(&i);
            qDebug() << "Cylindre :" << params[0] << ", de centre" << params[1] << ", avec une rotation de" << params[2];
        }
        i++;
    }
}

QVector<QVector<float>> Parser::getCylinder(int *index){

    QVector<QVector<float>> params;
    params.push_back(getParam(index)); params.push_back(getParam(index)); params.push_back(getParam(index));
    return params;
}

QVector<float> Parser::getParam(int *index){
    *index += 4;
    QVector<float> param;
    QChar cc = sentence.at(*index);
    QString test = "";

    while(sentence.at(*index) != ')'){
        cc = sentence.at(*index); *index += 1;
        if(cc == ',') {
            param.push_back(test.toFloat()); //1, 2
            test = "";
        }
        else {
            test += cc;
        }
    }
    param.push_back(test.toFloat()); //3

    *index += 2;
    return param;
}
