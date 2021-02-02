// Basé sur :
// CC-BY Edouard.Thiel@univ-amu.fr - 22/01/2019

#ifndef GLAREA_H
#define GLAREA_H

#include <QKeyEvent>
#include <QTimer>
#include <QElapsedTimer>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>

#include "cylinder.h"
#include "sphere.h"
#include "cuboid.h"
#include "grammar.h"
#include "parser.h"
#include "screw.h"

class GLArea : public QOpenGLWidget,
               protected QOpenGLFunctions
{
    Q_OBJECT

public:
    explicit GLArea(QWidget *parent = nullptr);
    ~GLArea() override;

protected slots:
    void onTimeout();
    void runGram();

protected:
    void initializeGL() override;
    void doProjection();
    void resizeGL(int w, int h) override;
    void paintGL() override;
    void keyPressEvent(QKeyEvent *ev) override;
    void keyReleaseEvent(QKeyEvent *ev) override;
    void mousePressEvent(QMouseEvent *ev) override;
    void mouseReleaseEvent(QMouseEvent *ev) override;
    void mouseMoveEvent(QMouseEvent *ev) override;

private:
    float xRot=20.0f, yRot=0.0f, zRot=0.0f;
    float xPos=0.0f,  yPos=0.0f, zPos=-50.0f;
    QTimer *timer = nullptr;
    QElapsedTimer elapsedTimer;
    float dt = 0;
    float windowRatio = 1.0f;
    QPoint lastPos;

    QOpenGLShaderProgram *program_simple_color;
    QOpenGLShaderProgram *program_texture;
    QOpenGLBuffer vbo_axes;
    QOpenGLBuffer vbo_sol;
    QOpenGLBuffer vbo_screw;
    QOpenGLTexture *textures[1];

    std::vector<QOpenGLBuffer> vbos;
    std::vector<Shape3D*> shapes;

    Screw screw;

    void makeGLObjects();
    void tearGLObjects();
    void render_shape_color(QOpenGLBuffer& vbo, QMatrix4x4& projectionMatrix, QMatrix4x4& viewMatrix, int nb_vert_faces, int nb_vert_lines);
};

#endif // GLAREA_H
