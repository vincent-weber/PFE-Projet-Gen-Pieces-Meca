#ifndef SCREW_H
#define SCREW_H

#include "generator.h"

/**
 * @brief The Screw class, représente les vis que l'on peut attacher sur les points d'ancrage. Cette pièce ne contient aucun point
 * d'ancrage, on ne peut rien attacher dessus.
 */
class Screw : public Generator
{
private:
    /**
     * @brief Tous les paramètres de la vis
     */
    float body_height = -1;
    float body_width = -1;
    float head_height = -1;
    float head_width = -1;
    int head_precision = -1;
    int body_precision = -1;

public:
    Screw();
    std::random_device rd;

    void generateParams(QString screw_part) override;
    void generateRules(QString screw_part) override;
    void set_rotation(QString screw_part) override;
    void set_center() override;
    void set_anchor_points() override;
    QVector<AnchorPoint*> choose_anchor_points() override;

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

    float get_body_height() {
        return body_height;
    }
    float get_head_height(){
        return head_height;
    }
};

#endif // SCREW_H
