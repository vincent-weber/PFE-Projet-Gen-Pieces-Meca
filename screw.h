#ifndef SCREW_H
#define SCREW_H

#include "generator.h"

class Screw : public Generator
{
private:
    float body_height = -1;
    float body_width = -1;
    float head_height = -1;
    float head_width = -1;
    int body_precision = -1;
public:
    Screw();
    std::random_device rd;
    void generate(QString screw_part) override;

    void set_body_height(float body_height) {
        this->body_height = body_height;
    }
    void set_body_width(float body_width) {
        this->body_width = body_width;
    }
    void set_head_height(float head_height) {
        this->head_height = head_height;
    }
    void set_head_width(float head_width) {
        this->head_width = head_width;
    }
    void set_body_precision(int body_precision) {
        this->body_precision = body_precision;
    }
};

#endif // SCREW_H
