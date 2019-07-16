#ifndef CALCULATE_H
#define CALCULATE_H

#include <QMainWindow>
#include <QtMath>
#include <QVector3D>
#include "angle.h"
#include <QGLWidget>
#include <QtOpenGL>
#include <QtWidgets>


namespace Ui {
class Calculate;
}

class Calculate : public QMainWindow
{
    Q_OBJECT

public:
    explicit Calculate(QWidget *parent = 0);
    ~Calculate();
    bool fullscreen;
    QVector3D tmpPoint;

private:
    Ui::Calculate *ui;
private slots:
    void set_target_fun();
    void calculate_fun();
    void addTarget();
    void keyPressEvent(QKeyEvent *e);
    void addPath_bt_clicked();
};



#endif // CALCULATE_H

