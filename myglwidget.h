#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#include <QWidget>
#include <QGLWidget>
#include <QOpenGLWidget>
#include "globals.h"

class MyGLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit MyGLWidget(QWidget *parent = 0);
    ~MyGLWidget();
signals:
    //signaling rotation from mouse movement
    void xRotationChanged(int angle);
    void yRotationChanged(int angle);
    void zRotationChanged(int angle);

public slots:
    //slots for xyz_rotation slider
    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);
    void paintGL();


protected:
    void initializeGL();

    void resizeGL(int width,int height);

    QSize minimumSizeHint() const;
    QSize sizeHint() const;
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);


private:
    int xRot;
    int yRot;
    int zRot;

    QPoint lastPos;
    float _scale;

public:
    void draw();
    void addPoint();
    float computeScale(const char* str[4]);
    void  addPath();
    void    addPath_bt_points();






};

#endif // MYGLWIDGET_H
