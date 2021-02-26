#include "piston.h"

Piston::Piston()
{
    generator_name = "Piston";
    center = QVector3D(0,0,0);
    rotation = QVector3D(0,0,0);
}

void Piston::generateParams(QString part){
    if(part == "Box"){
        Box *box = new Box;
        box->createParams();
        piston_str += box->primitives_str;
        parts_generators.push_back(box);
    }
    else if(part == "Pipe"){
        Pipe *pipe = new Pipe;
        pipe->createParams();
        piston_str += pipe->primitives_str;
        parts_generators.push_back(pipe);
    }
    else if(part == "Screw"){
        Screw *screw = new Screw;
        screw->createParams();
        piston_str += screw->primitives_str;
        parts_generators.push_back(screw);
    }
}

void Piston::set_rotation(QString screw_part){

}

void Piston::set_center(){

}

void Piston::set_anchor_points(){

}

void Piston::generateRules(QString part){
    qDebug() << __FUNCTION__ << parts_generators.size();

    for(int i = 0; i < parts_generators.size(); i++){
        for (int k = 0 ; k < parts_generators[i]->primitives_str.size() ; ++k) {
            parts_generators[i]->generateRules(parts_generators[i]->primitives_str.at(k));

        }
    }
}
