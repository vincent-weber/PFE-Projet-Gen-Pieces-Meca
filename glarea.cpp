// Basé sur :
// CC-BY Edouard.Thiel@univ-amu.fr - 22/01/2019

#include <QDebug>
#include <QSurfaceFormat>
#include <QMatrix4x4>
#include <QRegularExpression>

#include "glarea.h"

GLArea::GLArea(QWidget *parent) :
    QOpenGLWidget(parent)
{
    QSurfaceFormat sf;
    sf.setDepthBufferSize(24);
    sf.setSamples(16);
    setFormat(sf);

    setEnabled(true);                   // événements clavier et souris
    setFocusPolicy(Qt::StrongFocus);    // accepte focus
    setFocus();                         // donne le focus

    timer = new QTimer(this);
    timer->setInterval(50);           // msec
    connect (timer, SIGNAL(timeout()), this, SLOT(onTimeout()));
    timer->start();
    elapsedTimer.start();

//    QString test = "Sĥere+head-body*test";
//    QStringList reg = test.split(QRegExp("\\+|\\-|\\*"));
//    qDebug() << reg;


//    shapes.push_back(new Sphere(5,10,20, V3(0,11.5,20), V3(PI/2, PI/2, 0)));
//    shapes.push_back(new Cylinder(7,4,15, V3(0,10,20), V3(PI/2, PI/2, 0)));
//    shapes.push_back(new Cylinder(5,4,20, V3(0,6.5,20), V3(PI/2, PI/2, 0)));

//    shapes = parser.cyls_screw;

//    std::vector<Shape3D*> cyls_screw;
//    cyls_screw.push_back(new Sphere(5,10,20, V3(0,11.5,10), V3(PI/2, PI/2, 0)));
//    cyls_screw.push_back(new Cuboid(2,4,3, V3(0,10,10), V3(PI/2, PI/2, 0)));
//    cyls_screw.push_back(new Cylinder(5,4,20, V3(0,6.5,10), V3(PI/2, PI/2, 0)));

//    std::vector<Bool_op> ops;
//    ops.push_back(UNION);
//    ops.push_back(UNION);

//    screw = Screw(parser.cyls_screw, parser.ops);

    Generator::initRules();

}

GLArea::~GLArea()
{
    delete timer;

    // Contrairement aux méthodes virtuelles initializeGL, resizeGL et repaintGL,
    // dans le destructeur le contexte GL n'est pas automatiquement rendu courant.
    makeCurrent();
    tearGLObjects();
    doneCurrent();
}


void GLArea::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0.5f,0.5f,1.0f,1.0f);
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_CULL_FACE);
    //glFrontFace(GL_CCW);
   // glCullFace(GL_BACK);

    makeGLObjects();

    program_simple_color = new QOpenGLShaderProgram(this);
    program_simple_color->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/simple_color.vsh");
    program_simple_color->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/simple_color.fsh");
    if (! program_simple_color->link()) {  // édition de lien des shaders dans le shader program
        qWarning("Failed to compile and link shader program:");
        qWarning() << program_simple_color->log();
    }

    program_texture = new QOpenGLShaderProgram(this);
    program_texture->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/simple_tex.vsh");
    program_texture->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/simple_tex.fsh");
    if (! program_texture->link()) {  // édition de lien des shaders dans le shader program
        qWarning("Failed to compile and link shader program:");
        qWarning() << program_texture->log();
    }
    program_texture->setUniformValue("texture", 0);
}


void GLArea::makeGLObjects()
{
    qDebug() << __FUNCTION__;
    // Création du sol
    float tailleSol = 20.0f;

    GLfloat vertices_sol[] = {
       -tailleSol, 0.0f,-tailleSol,
       -tailleSol, 0.0f, tailleSol,
        tailleSol, 0.0f, tailleSol,
        tailleSol, 0.0f, tailleSol,
        tailleSol, 0.0f,-tailleSol,
       -tailleSol, 0.0f,-tailleSol
    };

    GLfloat texCoords_sol[] = {
            0.0f, 0.0f,
            0.0f, 1.0f,
            1.0f, 1.0f,
            1.0f, 1.0f,
            1.0f, 0.0f,
            0.0f, 0.0f
        };

    QVector<GLfloat> vertData_sol;
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 3; j++)
            vertData_sol.append(vertices_sol[i*3+j]);
        for (int j = 0; j < 2; j++)
            vertData_sol.append(texCoords_sol[i*2+j]);
    }

    vbo_sol.create();
    vbo_sol.bind();
    vbo_sol.allocate(vertData_sol.constData(), vertData_sol.count() * int(sizeof(GLfloat)));

    QVector<GLdouble> vertData_axes;
    vertData_axes.append(0); vertData_axes.append(10); vertData_axes.append(0); vertData_axes.append(255); vertData_axes.append(0); vertData_axes.append(0);
    vertData_axes.append(5); vertData_axes.append(10); vertData_axes.append(0); vertData_axes.append(255); vertData_axes.append(0); vertData_axes.append(0);
    vertData_axes.append(0); vertData_axes.append(10); vertData_axes.append(0); vertData_axes.append(0); vertData_axes.append(255); vertData_axes.append(0);
    vertData_axes.append(0); vertData_axes.append(15); vertData_axes.append(0); vertData_axes.append(0); vertData_axes.append(255); vertData_axes.append(0);
    vertData_axes.append(0); vertData_axes.append(10); vertData_axes.append(0); vertData_axes.append(0); vertData_axes.append(0); vertData_axes.append(255);
    vertData_axes.append(0); vertData_axes.append(10); vertData_axes.append(5); vertData_axes.append(0); vertData_axes.append(0); vertData_axes.append(255);

    vbo_axes.create();
    vbo_axes.bind();
    vbo_axes.allocate(vertData_axes.constData(), vertData_axes.count() * int(sizeof(GLdouble)));

    for (unsigned i = 0 ; i < shapes.size() ; ++i) {
        shapes[i]->render();
        QOpenGLBuffer vbo;
        vbo.create();
        vbo.bind();
        vbo.allocate(shapes[i]->gl_data.constData(), shapes[i]->gl_data.count() * int(sizeof(GLdouble)));
        vbos.push_back(vbo);
    }

    // Création de textures
    QImage image_sol(":/textures/ground.jpg");
    if (image_sol.isNull())
        qDebug() << "load image ground.jpg failed";
    textures[0] = new QOpenGLTexture(image_sol);
}

void GLArea::prepareMechaParts() {
    for (unsigned i = 0 ; i < mecha_parts.size() ; ++i) {
        mecha_parts[i].render();
        QOpenGLBuffer vbo;
        vbo.create();
        vbo.bind();
        vbo.allocate(mecha_parts[i].gl_data.constData(), mecha_parts[i].gl_data.count() * int(sizeof(GLdouble)));
        vbos_mecha_parts.push_back(vbo);
    }
}


void GLArea::tearGLObjects()
{
    vbo_sol.destroy();
    for (int i = 0; i < 1; i++)
        delete textures[i];
}


void GLArea::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    windowRatio = float(w) / h;
}

void GLArea::render_shape_color(QOpenGLBuffer& vbo, QMatrix4x4& projectionMatrix, QMatrix4x4& viewMatrix, int nb_vert_faces, int nb_vert_lines) {
    vbo.bind();
    program_simple_color->bind();
    QMatrix4x4 modelMatrix;
    modelMatrix.setToIdentity();
    program_simple_color->setUniformValue("projectionMatrix", projectionMatrix);
    program_simple_color->setUniformValue("viewMatrix", viewMatrix);
    program_simple_color->setUniformValue("modelMatrix", modelMatrix);

    program_simple_color->setAttributeBuffer("in_position", GL_DOUBLE, 0, 3, 6 * sizeof(GLdouble));
    program_simple_color->setAttributeBuffer("in_color", GL_DOUBLE, 3 * sizeof(GLdouble), 3, 6 * sizeof(GLdouble));
    program_simple_color->enableAttributeArray("in_position");
    program_simple_color->enableAttributeArray("in_color");

    glDrawArrays(GL_TRIANGLES, 0, nb_vert_faces);
    if (nb_vert_lines != 0)
        glDrawArrays(GL_LINES, nb_vert_faces, nb_vert_faces + nb_vert_lines);

    program_simple_color->disableAttributeArray("in_position");
    program_simple_color->disableAttributeArray("in_color");
    program_simple_color->release();
}


void GLArea::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Matrice de projection
    QMatrix4x4 projectionMatrix;
    projectionMatrix.perspective(45.0f, windowRatio, 1.0f, 1000.0f);

    // Matrice de vue (caméra)
    QMatrix4x4 viewMatrix;
    viewMatrix.translate(xPos, yPos, zPos);
    viewMatrix.rotate(xRot, 1, 0, 0);
    viewMatrix.rotate(yRot, 0, 1, 0);
    viewMatrix.rotate(zRot, 0, 0, 1);

    // Affichage du sol
    vbo_sol.bind();
    program_texture->bind(); // active le shader program du sol

    QMatrix4x4 modelMatrixSol;
    modelMatrixSol.translate(0.0f, 0.0f, 0.0f);
    program_texture->setUniformValue("projectionMatrix", projectionMatrix);
    program_texture->setUniformValue("viewMatrix", viewMatrix);
    program_texture->setUniformValue("modelMatrix", modelMatrixSol);

    program_texture->setAttributeBuffer("in_position", GL_FLOAT, 0, 3, 5 * sizeof(GLfloat));
    program_texture->setAttributeBuffer("in_uv", GL_FLOAT, 3 * sizeof(GLfloat), 2, 5 * sizeof(GLfloat));
    program_texture->enableAttributeArray("in_position");
    program_texture->enableAttributeArray("in_uv");

    textures[0]->bind();
    //glDrawArrays(GL_TRIANGLES, 0, 6);
    textures[0]->release();

    program_texture->disableAttributeArray("in_position");
    program_texture->disableAttributeArray("in_uv");
    program_texture->release();

    //Axes
    render_shape_color(vbo_axes, projectionMatrix, viewMatrix, 0, 6);

    //Shapes de test
    for (unsigned i = 0 ; i < shapes.size() ; ++i) {
        render_shape_color(vbos[i], projectionMatrix, viewMatrix, shapes[i]->nb_vertices_gl_faces, shapes[i]->nb_vertices_gl_lines);
    }

    //Rendu des pièces mécaniques
    for (unsigned i = 0 ; i < mecha_parts.size() ; ++i) {
        render_shape_color(vbos_mecha_parts[i], projectionMatrix, viewMatrix, mecha_parts[i].nb_vertices_gl_faces, mecha_parts[i].nb_vertices_gl_lines);
    }

}


void GLArea::keyPressEvent(QKeyEvent *ev)
{
    float da = 1.0f;

    switch(ev->key()) {
        case Qt::Key_A :
            xRot -= da;
            update();
            break;

        case Qt::Key_Q :
            xRot += da;
            update();
            break;

        case Qt::Key_Z :
            yRot -= da;
            update();
            break;

        case Qt::Key_S :
            yRot += da;
            update();
            break;

        case Qt::Key_E :
            zRot -= da;
            update();
            break;

        case Qt::Key_D :
            zRot += da;
            update();
            break;
    }
}


void GLArea::keyReleaseEvent(QKeyEvent *ev)
{
    qDebug() << __FUNCTION__ << ev->text();
}


void GLArea::mousePressEvent(QMouseEvent *ev)
{
    lastPos = ev->pos();
}


void GLArea::mouseReleaseEvent(QMouseEvent *ev)
{
    ev = nullptr;
}


void GLArea::mouseMoveEvent(QMouseEvent *ev)
{
    int dx = ev->x() - lastPos.x();
    int dy = ev->y() - lastPos.y();

    if (ev->buttons() & Qt::LeftButton) {
        xRot += dy;
        yRot += dx;
        update();
    } else if (ev->buttons() & Qt::RightButton) {
        xPos += dx/10.0f;
        yPos -= dy/10.0f;
        update();
    } else if (ev->buttons() & Qt::MidButton) {
        xPos += dx/10.0f;
        zPos += dy;
        update();
    }

    lastPos = ev->pos();
}


void GLArea::onTimeout()
{
    static qint64 old_chrono = elapsedTimer.elapsed(); // static : initialisation la première fois et conserve la dernière valeur
    qint64 chrono = elapsedTimer.elapsed();
    dt = (chrono - old_chrono) / 1000.0f;
    old_chrono = chrono;
    update();
}


void GLArea::run_gen_screw(){
    mecha_parts.clear();
    vbos_mecha_parts.clear();
    Screw screw_gen;
    //screw_gen.set_body_width(2);
    screw_gen.createParams();
    for (int i = 0 ; i < screw_gen.primitives_str.size() ; ++i) {
        screw_gen.generateRules(screw_gen.primitives_str.at(i));
    }
    screw_gen.computeSentence();

    qDebug() << "PHRASE FINALE : " << screw_gen.sentence;

    Parser parser(screw_gen.sentence);
    parser.reader();

    mecha_parts.push_back(MechanicalPart(parser.shapes, parser.ops));

    prepareMechaParts();
}

void GLArea::run_gen_nut(){
    mecha_parts.clear();
    vbos_mecha_parts.clear();
    Nut nut_gen;
    nut_gen.set_main_cyl_radius(2.5f);
    nut_gen.createParams();
    for (int i = 0 ; i < nut_gen.primitives_str.size() ; ++i) {
        nut_gen.set_rotation(QVector3D(42,42,42), "JFLKSDJF");
        nut_gen.generateRules(nut_gen.primitives_str.at(i));
    }
    nut_gen.computeSentence();

    qDebug() << "PHRASE FINALE : " << nut_gen.sentence;

    Parser parser(nut_gen.sentence);
    parser.reader();

    mecha_parts.push_back(MechanicalPart(parser.shapes, parser.ops));

    prepareMechaParts();
}

void GLArea::run_gen_box(){
    mecha_parts.clear();
    vbos_mecha_parts.clear();
    Box box;
    box.createParams();
    box.computeSentence();
    Parser parser_box(box.sentence);
    parser_box.reader();
    mecha_parts.push_back(MechanicalPart(parser_box.shapes, parser_box.ops));

    //TODO : phrase finale : union de toutes les phrases des pieces individuellement
    Screw sc;
    sc.createParams();

    for (int i = 0 ; i < box.anchor_points.size() ; ++i) {
        for (int j = 0 ; j < box.anchor_points[0].size(); ++j) {
            sc.center = QVector3D(box.anchor_points[i][j].coords - box.anchor_points[i][j].direction*((sc.get_body_height()/2) - sc.get_head_height()/2));
            for (int k = 0 ; k < sc.primitives_str.size() ; ++k) {
                sc.set_rotation(box.anchor_points[i][j].direction, sc.primitives_str.at(k));
                sc.generateRules(sc.primitives_str.at(k));
            }
            sc.sentence = sc.base_sentence;
            sc.computeSentence();
            Parser parser_sc(sc.sentence);
            parser_sc.reader();
            mecha_parts.push_back(MechanicalPart(parser_sc.shapes, parser_sc.ops));
        }
    }

    prepareMechaParts();
}
