#include "calculate.h"
#include "ui_calculate.h"
#include "angle.h"
#include "globals.h"
#include "myglwidget.h"
#include "mainwindow.h"
#include <QVector3D>
#include <QtMath>
#include <QtOpenGL>
#include <QtWidgets>
#include <QGLWidget>
#include <QtGui/QMouseEvent>




Calculate::Calculate(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Calculate)
{
    ui->setupUi(this);

    fullscreen = false;

    connect(ui->set_target, SIGNAL(clicked()),this, SLOT(set_target_fun()));

    connect(ui->calculate, SIGNAL(clicked()),this, SLOT(calculate_fun()));

    connect(ui->addtarget,SIGNAL(clicked()),this,SLOT(addTarget()));

    connect(ui->myGLWidget,SIGNAL(xRotationChanged(int)),ui->xRotSlider,SLOT(setValue(int)));

    connect(ui->myGLWidget,SIGNAL(yRotationChanged(int)),ui->yRotSlider,SLOT(setValue(int)));

    connect(ui->myGLWidget,SIGNAL(zRotationChanged(int)),ui->zRotSlider,SLOT(setValue(int)));

    connect(ui->CalculatePath,SIGNAL(clicked()),this,SLOT(addPath_bt_clicked()));

}


void Calculate::set_target_fun()
{
    QString tmp;
    ui->x_tinput->setText(tmp.setNum(3+0.5*qSin(2)*qCos(3)));
    ui->y_tinput->setText(tmp.setNum(3+0.5*qSin(2)*qSin(3)));
    ui->z_tinput->setText(tmp.setNum(3+0.5*qCos(2)));

    ui->x_tinput_2->setText(tmp.setNum(3+0.5*qSin(5)*qCos(6)));
    ui->y_tinput_2->setText(tmp.setNum(3+0.5*qSin(5)*qSin(6)));
    ui->z_tinput_2->setText(tmp.setNum(3+0.5*qCos(5)));

    ui->x_tinput_3->setText(tmp.setNum(3+0.5*qSin(7)*qCos(8)));
    ui->y_tinput_3->setText(tmp.setNum(3+0.5*qSin(7)*qSin(8)));
    ui->z_tinput_3->setText(tmp.setNum(3+0.5*qCos(7)));
}
void Calculate::calculate_fun()
{
    QString target_x1,target_y1,target_z1;
    QString target_x2,target_y2,target_z2;
    QString target_x3,target_y3,target_z3;

    target_x1 = ui->x_tinput->toPlainText();
    target_y1 = ui->y_tinput->toPlainText();
    target_z1 = ui->z_tinput->toPlainText();

    target_x2 = ui->x_tinput_2->toPlainText();
    target_y2 = ui->y_tinput_2->toPlainText();
    target_z2 = ui->z_tinput_2->toPlainText();

    target_x3 = ui->x_tinput_3->toPlainText();
    target_y3 = ui->y_tinput_3->toPlainText();
    target_z3 = ui->z_tinput_3->toPlainText();

    QVector3D point1,point2,point3;
    point1.setX(target_x1.toDouble());
    point1.setY(target_y1.toDouble());
    point1.setZ(target_z1.toDouble());

    point2.setX(target_x2.toDouble());
    point2.setY(target_y2.toDouble());
    point2.setZ(target_z2.toDouble());

    point3.setX(target_x3.toDouble());
    point3.setY(target_y3.toDouble());
    point3.setZ(target_z3.toDouble());


    cal_angle.calculate_new_targets(point1,nPoint1);
    cal_angle.calculate_new_targets(point2,nPoint2);
    cal_angle.calculate_new_targets(point3,nPoint3);

    ui->listRotation->addItem("Target1 in FrameCS = ( "+QString::number(nPoint1.x())+" , "+QString::number(nPoint1.y())+" , "+QString::number(nPoint1.z())+" )");
    ui->listRotation->addItem("Target2 in FrameCS = ( "+QString::number(nPoint2.x())+" , "+QString::number(nPoint2.y())+" , "+QString::number(nPoint2.z())+" )");
    ui->listRotation->addItem("Target3 in FrameCS = ( "+QString::number(nPoint3.x())+" , "+QString::number(nPoint3.y())+" , "+QString::number(nPoint3.z())+" )");


//    for (int i = 0;i!= 3;i++)
//    {
//        for (int j = 0;j!= 3;j++)
//        {
//            tmpPoint.setX(1+0.2*qSin(i)*qCos(j));
//            tmpPoint.setY(1+0.3*qSin(i)*qSin(j));
//            tmpPoint.setZ(1+0.4*qCos(i));
//            cal_angle.targets.push_back(tmpPoint);
//        }
//    }


    std::vector<QString> rotation_angle12 = cal_angle.calculate_point_angle(nPoint1,nPoint2);
    std::vector<QString>::iterator it12 = rotation_angle12.begin();
    ui->listRotation->addItem("Target 1 to target 2: ( Pitch = "+*it12+" , Roll = " +*(it12++)+" )");

    std::vector<QString> rotation_angle23 = cal_angle.calculate_point_angle(nPoint2,nPoint3);
    std::vector<QString>::iterator it23 = rotation_angle23.begin();
    ui->listRotation->addItem("Target 2 to target 3: ( Pitch = "+*it23+" , Roll = " +*(it23++)+" )");

    std::vector<QString> rotation_angle13 = cal_angle.calculate_point_angle(nPoint1,nPoint3);
    std::vector<QString>::iterator it13 = rotation_angle13.begin();
    ui->listRotation->addItem("Target 1 to target 3: ( Pitch = "+*it13+" , Roll = " +*(it13++)+" )");

}

void Calculate::addTarget()
{

    cal_angle.targets.push_back(nPoint1);
    cal_angle.targets.push_back(nPoint2);
    cal_angle.targets.push_back(nPoint3);


}
void Calculate::addPath_bt_clicked()
{
    cal_path_count ++ ;
    if (cal_path_count/2)

        cal_path = TRUE;
    else
        cal_path = FALSE;

}

void Calculate::keyPressEvent(QKeyEvent *e)
{
    switch(e->key())
    {
        //F1键为全屏和普通屏显示切换键
        case Qt::Key_F1:
            fullscreen = !fullscreen;
            if(fullscreen)
                showFullScreen();
            else
            {
                showNormal();
            }
            break;
        //Ese为退出程序键
        case Qt::Key_Escape:
            close();
    }
}

Calculate::~Calculate()
{
    delete ui;
}


