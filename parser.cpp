#include "parser.h"

Parser::Parser(QString sentence){
    this->sentence = sentence;
}

//Mot possible cyl, cen, rot.
//float rad, float diam, float prec, V3 c, V3 rot
void Parser::reader(){

    int i = 0;
    while(i < sentence.size()){

        //Recupere les informations du cylindre;
        if(sentence.at(i) == 'c' && sentence.at(i+1) == 'y'){
            QVector<QVector<float>> params = getGeo(&i);
            qDebug() << "Cylindre :" << params[0] << ", de centre" << params[1] << ", avec une rotation de" << params[2];
            Cylinder *cyl = new Cylinder(params[0][0], params[0][1], params[0][2],
                                V3(params[1][0], params[1][1], params[1][2]),
                                V3(params[2][0], params[2][1], params[2][2]));
            cyls_screw.push_back(cyl);
        }

        //Recupere les informations du cube
        if(sentence.at(i) == 'c' && sentence.at(i+1) == 'u'){
            qDebug() << "Cube ";
            QVector<QVector<float>> params = getGeo(&i);
            Cuboid *cub = new Cuboid(params[0][0], params[0][1], params[0][2],
                    V3(params[1][0], params[1][1], params[1][2]),
                    V3(params[2][0], params[2][1], params[2][2]));
            cyls_screw.push_back(cub);
        }

        //Recupere les informations d'une sphere
        if(sentence.at(i) == 's' && sentence.at(i+1) == 'p'){
            qDebug() << "Sphere";
            QVector<QVector<float>> params = getGeo(&i);
            qDebug() << "Sphere :" << params[0] << ", de centre" << params[1] << ", avec une rotation de" << params[2];
            Sphere *sph = new Sphere(params[0][0], params[0][1], params[0][2],
                    V3(params[1][0], params[1][1], params[1][2]),
                    V3(params[2][0], params[2][1], params[2][2]));
            cyls_screw.push_back(sph);
        }

        if (sentence.at(i) == '+'){
            ops.push_back(UNION);
        }
        i++;
    }
}

QVector<QVector<float>> Parser::getGeo(int *index){

    QVector<QVector<float>> params;
    params.push_back(getParam(index));
    *index += 2;
    params.push_back(getParam(index));
    *index += 1;
    params.push_back(getParam(index));
    return params;
}

QVector<float> Parser::getParam(int *index){
    *index += 4;
    QVector<float> param;
    QChar currChar = sentence.at(*index);
    QString currParam = "";

    while(sentence.at(*index) != ')'){
        currChar = sentence.at(*index);
        *index += 1;
        if(currChar == ',') {
            param.push_back(currParam.toFloat()); //1, 2
            currParam = "";
        }
        else {
            currParam += currChar;
        }
    }
    param.push_back(currParam.toFloat()); //3
    return param;
}
