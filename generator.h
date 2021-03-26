#ifndef GENERATOR_H
#define GENERATOR_H

#include <QHash>
#include <random>
#include <QDebug>
#include <QVector3D>
#include <QStringList>
#include "util.h"
#include "anchorpoint.h"

/**
 * @brief The AnchorPointType enum
 * Enum dont chaque entree encode la manière de créer et de sélectionner les points d'ancrage
 * pour les pièces mécaniques
 */
enum AnchorPointType {
    BOX_GRID_3X3_SYMMETRIC,
    BOX_GRID_3X3_RANDOM,
    BOX_ONE_FACE_ALIGNED,
    BOX_ANGLES,
    BOX_EDGE,

    PIPE_ENDS,

    ENGINE_ALIGNED_ALL,
    ENGINE_ALTERNATED_ALL,
    ENGINE_ALIGNED_RANDOM,
    ENGINE_ALTERNATED_RANDOM,

    HINGE_ANGLES_4,
    HINGE_GRID_3X3,
    HINGE_RANDOM,

    PLANKS_ALL_HINGES,
    PLANKS_RANDOM_HINGES,

    NO_ANCHOR_POINTS,
    UNDEFINED
};

/**
 * @brief The Generator class
 * Classe abstraite de base de laquelle dérive toutes les pièces mécaniques
 */
class Generator
{
public:

    /**
     * @brief base_sentence Phrase de base de l'objet, contient tous les nons terminaux tirés aléatoirement qui vont
     * régir la création de l'objet. Ne pas modifier ce paramètre.
     */
    QString base_sentence;

    /**
     * @brief sentence Contient la phrase globale de l'objet, qui sera changée en une succession de primitives séparées
     * par des opérations booléennes par computeSentence(), à donner ensuite en entrée au Parser.
     */
    QString sentence;

    /**
     * @brief generator_name nom de la pièce mécanique, donner le même nom que dans le dictionnaire.
     * Donnée dans le constructeur de chaque pièce mécanique.
     */
    QString generator_name;

    /**
     * @brief primitives_str liste contenant les portions de la phrase de base,
     * données en entrées à generateParams, set_rotation et generateRules
     */
    QStringList primitives_str;

    /**
     * @brief max_size valeur définissant une taille maximale pour chaque pièce mécanique
     * sémantique dépendante de l'objet.
     */
    float max_size;
    /**
     * @brief min_size valeur définissant une taille minimale pour chaque pièce mécanique
     * sémantique dépendante de l'objet
     */
    float min_size;

    /**
     * @brief center position du centre de la pièce dans l'espace global
     */
    QVector3D center;

    /**
     * @brief rotation valeur encodant la rotation pour la portion de pièce mécanique en cours.
     * Les pièces mécaniques actuelles ne gèrent que les rotations par pas de PI/2
     */
    QVector3D rotation;

    /**
     * @brief direction la direction vers laquelle la pièce pointe.
     * sémantique dépendante de l'objet. Est déterminé par le point d'ancrage auquel est attaché
     * l'objet. Les rotations des différentes parties de l'objet dépendent de la valeur de ce paramètre.
     * Sa valeur est déterminée automatiquement lors de l'appel à set_prev_anchor_point.
     */
    QVector3D direction;

    /**
     * @brief set_rotation détermine la rotation pour la pièce mécanique donnée en paramètre.
     * @param part doit être une entrée de la QStringList primitives_str de l'objet (portion de phrase de base)
     */
    virtual void set_rotation(QString part) = 0;

    /**
     * @brief set_center détermine une valeur de centre spécifique à la pièce, souvent en fonction du point d'ancrage
     * sur lequel la pièce est attachée
     */
    virtual void set_center() = 0;

    /**
     * @brief set_anchor_points remplit la liste anchor_points en fonction de la valeur de anch_type pour l'objet
     */
    virtual void set_anchor_points() = 0;

    /**
     * @brief set_prev_anchor_point permet de spécifier le point d'ancrage sur lequel la nouvelle pièce sera attachée.
     * Définit aussi la valeur du paramètre direction.
     * @param anchor_point pointeur vers le point d'ancrage d'une pièce préexistante
     */
    void set_prev_anchor_point(AnchorPoint* anchor_point);

    /**
     * @brief choose_anchor_points permet de choisir un certain nombre de points d'ancrage de la pièce selon une stratégie
     * définie par anch_type. Utilisée pour déterminer les points d'ancrage sur lesquels attacher de nouvelles pièces.
     * @return liste de pointeurs contenant les points d'ancrage sélectionnés.
     */
    virtual QVector<AnchorPoint*> choose_anchor_points() = 0;

    /**
     * @brief min_distance_between_anchor_points à supprimer ?
     */
    const float min_distance_between_anchor_points = 0.003f;

    /**
     * @brief get_max_possible_size renvoie la taille maximale autorisée pour la création de la pièce. Renvoie soit la valeur par défaut
     * de max_size de l'objet, soit la taille maximale autorisée par le point d'ancrage sur lequel est attachée la pièce.
     * @return soit max_size, soit anchor_point_prev_lvl.max_size
     */
    float get_max_possible_size();

    /**
     * @brief rd_gen générateur aléatoire
     */
    std::random_device rd_gen;

    /**
     * @brief anchor_points liste des points d'ancrage de l'objet. Liste à 2 dimensions pour permettre dans une certaine mesure
     * de "classer" les points d'ancrage pour faciliter la sélection (choose_anchor_points) par la suite. Le anch_type BOX_GRID_3X3_SYMMETRIC
     * est un exemple d'utilisation de la double dimensionnalité de ce paramètre.
     *
     */
    QVector<QVector<AnchorPoint>> anchor_points;

    /**
     * @brief anchor_point_prev_lvl pointeur vers le point d'ancrage sur lequel est attaché l'objet.
     */
    AnchorPoint* anchor_point_prev_lvl = nullptr;

    /**
     * @brief anch_type spécifie la manière de créer et de sélectionner les points d'ancrage de la pièce.
     * Valeur définie en fonction de la phrase de base de l'objet.
     */
    AnchorPointType anch_type = UNDEFINED;



    /**
     * @brief initRules initialise le dictionnaire
     */
    static void initRules();

    /**
     * @brief createParams détermine la phrase de base de l'objet (base_sentence) aléatoirement en parcourant$
     * les valeurs possibles dans le dictionnaire
     */
    void createParams();

    /**
     * @brief recurs appelée par createParams, détermine une phrase de base aléatoire en fonction de generator_name
     * @param in generator_name de la pièce
     * @return la phrase de base, base_sentence
     */
    QString recurs(QString in);

    /**
     * @brief generateParams génère les paramètres spécifiques à la pièce
     * @param part une entrée de primitives_str
     */
    virtual void generateParams(QString part) = 0;

    /**
     * @brief generateRules génère les règles finales de la pièce dans le dictionnaire.
     * Plus précisément, renseigne le dictionnaire avec les attributs des primitives_str de la pièce,
     * soit des suites de primitives avec leurs paramètres séparées par des opérations booléennes
     *
     * @param part une entrée de primitives_str
     */
    virtual void generateRules(QString part) = 0;

    /**
     * @brief rules règles du dictionnaire qui peuvent être modifiées
     */
    static QHash<QString, QVector<QString>> rules;

    /**
     * @brief base_rules règles de base du dictionnaire, sans terminaux.
     * permet de réinitialiser le dictionnaire pour supprimer les terminaux créés par generateRules.
     */
    static QHash<QString, QVector<QString>> base_rules;

    /**
     * @brief computeParameter fonction pour déterminer la valeur d'un paramètre d'une pièce, soit aléatoirement
     * si sa valeur est -1, soit en ne la changeant pas si cette dernière a été forcée manuellement.
     * Il existe une version pour les paramètres flottants et une autre pour les entiers.
     * @param param le paramètre dont on veut calculer la valeur
     * @param rd pour l'aléatoire
     * @param min borne minimale pour la valeur
     * @param max borne maximale pour la valeur
     * @return la valeur du paramètre généré.
     */
    float computeParameter(float param, std::random_device &rd, float min, float max);
    int computeParameter(int param, std::random_device &rd, int min, int max);


    /**
     * @brief createLeafRulesSingle à appeler dans generateRules, créé un terminal qui n'est qu'une seule primitive (pas d'op booléennes)
     * @param primitive_type cub, cyl ou sph selon la primitive
     * @param in le non terminal pour lequel créer le terminal correspondant
     * @param param les paramètres de la primitive
     * @param c le centre de la primitive
     * @param rot la rotation de la primitive
     */
    void createLeafRulesSingle(QString primitive_type, QString in, QVector<float> param, QVector3D c, QVector3D rot);
    /**
     * @brief createLeafRulesMultiple à appeler dans generateRules, créé un terminal qui est une combinaison de primitives par opérations booléennes
     * @param primitives liste des primitives ordonnées à générer
     * @param op_bools liste d'opérations booléennes à effectuer entre les primitives (taille de cette liste = taille de primitives - 1)
     * @param params liste des paramètres de chaque primitive
     * @param centers liste des centres de chaque primitive
     * @param rots liste des rotations de chaque primitive
     * @return la chaîne de caractères correspondant au terminal
     */
    QString createLeafRulesMultiple(QVector<QString>& primitives, QString op_bools, QVector<QVector<float>>& params, QVector<QVector3D>& centers, QVector<QVector3D>& rots);

    /**
     * @brief computeSentence transforme sentence avec tous les terminaux générés par generateRules
     */
    void computeSentence();
};

#endif // GENERATOR_H
