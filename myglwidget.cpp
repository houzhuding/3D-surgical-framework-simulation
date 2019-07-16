#include <QtOpenGL>
#include <QtWidgets>

#include <QtGui/QMouseEvent>
#include "mainwindow.h"
#include "myglwidget.h"
#include "globals.h"


MyGLWidget::MyGLWidget(QWidget *parent)
    :QGLWidget(QGLFormat(QGL::SampleBuffers),parent)
{
    xRot = 0;
    yRot = 0;
    zRot = 0;

}

MyGLWidget::~MyGLWidget()
{

}
QSize MyGLWidget::minimumSizeHint() const
{
    return QSize(50,50);
}

QSize MyGLWidget::sizeHint() const
{
    return QSize(400,400);

}

static void qNormalizeAngle(int &angle)
{
    while (angle < 0)
        angle += 360*32;
    while (angle > 360)
        angle -= 360*32;
}
void MyGLWidget::setXRotation(int angle)
{
    qNormalizeAngle(angle);
    if(angle != xRot){
        xRot = angle;
        emit xRotationChanged(angle);
        updateGL();
    }
}
void MyGLWidget::setYRotation(int angle)
{
    qNormalizeAngle(angle);
    if(angle != yRot){
        yRot = angle;
        emit yRotationChanged(angle);

        updateGL();
    }
}
void MyGLWidget::setZRotation(int angle)
{
    qNormalizeAngle(angle);
    if(angle != zRot){
        zRot = angle;
        emit zRotationChanged(angle);
        updateGL();
    }
}
void MyGLWidget::initializeGL()
{
    qglClearColor(Qt::black);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glShadeModel(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    static GLfloat lightPosition[4] = {0,0,10,1.0};
    glLightfv(GL_LIGHT0,GL_POSITION,lightPosition);


}

void MyGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -10.0);
    glRotatef(xRot / 4.0, 1.0, 0.0, 0.0);
    glRotatef(yRot / 4.0, 0.0, 1.0, 0.0);
    glRotatef(zRot / 4.0, 0.0, 0.0, 1.0);
    draw();

    if(cal_path_count == 1)
    {
         addPath();
    }
    if(cal_path_count == 2)
    {
        addPath_bt_points();
    }
    update();
}

void MyGLWidget::resizeGL(int width, int height)
{
    int side = qMin(width, height);
   // glViewport((width - side) / 2, (height - side) / 2, side, side);
    glViewport((width - 800) / 2, (height - 800) / 2, 800, 800);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
#ifdef QT_OPENGL_ES_1
    glOrthof(-2, +2, -2, +2, 1.0, 15.0);
#else
    glOrtho(-2, +2, -2, +2, 1.0, 15.0);
#endif
    glMatrixMode(GL_MODELVIEW);
}

void MyGLWidget::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
}

void MyGLWidget::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();

    if (event->buttons() & Qt::LeftButton) {
        setXRotation(xRot + 8 * dy);
        setYRotation(yRot + 8 * dx);
    } else if (event->buttons() & Qt::RightButton) {
        setXRotation(xRot + 8 * dy);
        setZRotation(zRot + 8 * dx);
    }

    lastPos = event->pos();
}

void MyGLWidget::draw()
{
    //Draw Frame CS

    qglColor(Qt::red);
    glBegin(GL_LINES);
          glVertex3f(0,0,0);
          glVertex3f(1,0,0);
          glVertex3f(1,0,0);
          glVertex3f(0.8,0.1,0);
          glVertex3f(0.8,-0.1,0);
          glVertex3f(1,0,0);
    glEnd();

    glBegin(GL_LINES);
          glVertex3f(0,0,0);
          glVertex3f(0,1,0);
          glVertex3f(0,1,0);
          glVertex3f(0.1,0.8,0);
          glVertex3f(-0.1,0.8,0);
          glVertex3f(0,1,0);
    glEnd();

    glBegin(GL_LINES);
          glVertex3f(0,0,0);
          glVertex3f(0,0,1);
          glVertex3f(0,0,1);
          glVertex3f(0.1,0,0.8);
          glVertex3f(-0.1,0,0.8);
          glVertex3f(0,0,1);
    glEnd();

    QPainterPath path;
//    glDisable(GL_LIGHTING);
    QFont font("Arial", 1);

    path.addText(QPointF(-2, 0), QFont("Arial", 1), QString(tr("O")));
    path.addText(QPointF(21, 1), QFont("Arial", 1), QString(tr("X")));
    path.addText(QPointF(-1, -21), QFont("Arial", 1), QString(tr("Y")));

    QList<QPolygonF> poly = path.toSubpathPolygons();
    for (QList<QPolygonF>::iterator i = poly.begin(); i != poly.end(); i++){
        glBegin(GL_LINE_LOOP);
        for (QPolygonF::iterator p = (*i).begin(); p != i->end(); p++)
            glVertex3f(p->rx()*0.05f, -p->ry()*0.05f, 0);
        glEnd();
    }
 //   glEnable(GL_LIGHTING);

//    const char* STRS[4] = {"O", "X", "Y", "Z"};

//    _scale = computeScale(STRS);

    //Draw the strings along the sides of a square
//    glScalef(_scale, _scale, _scale);
//    glColor3f(0.3f, 1.0f, 0.3f);
//    for(int i = 0; i < 4; i++) {
//        glPushMatrix();
//        glRotatef(90 * i, 0, 1, 0);
//        glTranslatef(0, 0, 1.5f / _scale);
//        t3dDraw3D(STRS[i], 0, 0, 0.2f);
//        glPopMatrix();
//    }


    glEnable(GL_PROGRAM_POINT_SIZE_EXT);
    glPointSize(5);
    qglColor(Qt::blue);
    glBegin(GL_LINES);
          glVertex3f(0,0,0);
          glVertex3f(cal_angle.cannula.x(),cal_angle.cannula.y(),cal_angle.cannula.z());
    glEnd();

    qglColor(Qt::green);


    for (std::vector<QVector3D>::iterator it = cal_angle.targets.begin();it !=cal_angle.targets.end();++it)
        {
                    glBegin(GL_POINTS);
                    QVector3D tmp = *it;
                    //glVertex3f(0,0,0);
                    glVertex3f(tmp.x(),tmp.y(),tmp.z());
                    glEnd();
         }

}

float MyGLWidget::computeScale(const char* strs[4])
{

        return 2.6f  ;
 }


void MyGLWidget::addPath()
{

    qglColor(Qt::yellow);
    glBegin(GL_LINES);
          glVertex3f(cal_angle.cannula.x(),cal_angle.cannula.y(),cal_angle.cannula.z());
          glVertex3f(cal_angle.cannula.x(),0,cal_angle.cannula.z());
          glVertex3f(cal_angle.cannula.x(),0,cal_angle.cannula.z());
          glVertex3f(0,0,0);
    glEnd();
}
void MyGLWidget::addPath_bt_points()
{

    qglColor(Qt::yellow);

    std::vector<QVector3D>::iterator it = cal_angle.targets.begin();
    QVector3D tmp_cannula = cal_angle.cannula;
    QVector3D tmp_target1 = *it;

    glBegin(GL_LINES);
        glVertex3f(tmp_cannula.x(),tmp_cannula.y(),tmp_cannula.z());
        glVertex3f(tmp_target1.x(),tmp_target1.y(),tmp_target1.z());
    glEnd();

    for (;it !=cal_angle.targets.end()-1;++it)
        {
                    glBegin(GL_LINES);
                    QVector3D tmp = *it;
                    QVector3D tmp2 = *(it+1);
                    glVertex3f(tmp.x(),tmp.y(),tmp.z());
                    glVertex3f(tmp2.x(),tmp2.y(),tmp2.z());
                    glEnd();
         }
}
