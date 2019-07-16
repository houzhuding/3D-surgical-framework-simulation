#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "angle.h"
#include "globals.h"
#include <QtMath>
#include <QVector3D>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    count = 0;
    ui->setupUi(this); //为指定控件设定用户界面
    ui->close->setText("Close");//设置按键上显示的文本
    ui->load->setText("Load Coordinates");
    ui->getdata->setText("Save Coordinates");


    connect(ui->load, SIGNAL(clicked()), this, SLOT(add()));
    connect(ui->getdata, SIGNAL(clicked()), this, SLOT(get()));
    connect(ui->calculate_angle, SIGNAL(clicked()),this, SLOT(open_caldialog()));
}

void MainWindow::add()
{
    QString tmp;
    count = count+1;
    ui->x_input->setText(tmp.setNum(0));
    ui->y_input->setText(tmp.setNum(1));
    ui->z_input->setText(tmp.setNum(0));

    ui->x_input_2->setText(tmp.setNum(1));
    ui->y_input_2->setText(tmp.setNum(1));
    ui->z_input_2->setText(tmp.setNum(0));

    ui->x_input_3->setText(tmp.setNum(0.5));
    ui->y_input_3->setText(tmp.setNum(1));
    ui->z_input_3->setText(tmp.setNum(-1));

    ui->x_entry->setText(tmp.setNum(1));
    ui->y_entry->setText(tmp.setNum(1));
    ui->z_entry->setText(tmp.setNum(1));

    ui->x_cannula->setText(tmp.setNum(-1));
    ui->y_cannula->setText(tmp.setNum(-1));
    ui->z_cannula->setText(tmp.setNum(-1));

    ui->x_target1->setText(tmp.setNum(3));
    ui->y_target1->setText(tmp.setNum(3));
    ui->z_target1->setText(tmp.setNum(3));
}

void MainWindow::get()
{
    QString marker_x1,marker_y1,marker_z1;
    QString marker_x2,marker_y2,marker_z2;
    QString marker_x3,marker_y3,marker_z3;

    QString entry_x,entry_y,entry_z;
    QString cannula_x,cannula_y,cannula_z;
    QString target1_x,target1_y,target1_z;

    marker_x1 = ui->x_input->toPlainText();
    marker_y1 = ui->y_input->toPlainText();
    marker_z1 = ui->z_input->toPlainText();

    marker_x2 = ui->x_input_2->toPlainText();
    marker_y2 = ui->y_input_2->toPlainText();
    marker_z2 = ui->z_input_2->toPlainText();

    marker_x3 = ui->x_input_3->toPlainText();
    marker_y3 = ui->y_input_3->toPlainText();
    marker_z3 = ui->z_input_3->toPlainText();

    entry_x = ui->x_entry->toPlainText();
    entry_y = ui->y_entry->toPlainText();
    entry_z = ui->z_entry->toPlainText();

    cannula_x = ui->x_cannula->toPlainText();
    cannula_y = ui->y_cannula->toPlainText();
    cannula_z = ui->z_cannula->toPlainText();

    target1_x = ui->x_target1->toPlainText();
    target1_y = ui->y_target1->toPlainText();
    target1_z = ui->z_target1->toPlainText();

    ui->listMarkers->addItem("Marker 1 = ( "+marker_x1+" , " +marker_y1+" , "+marker_z1+" )");
    ui->listMarkers->addItem("Marker 2 = ( "+marker_x2+" , " +marker_y2+" , "+marker_z2+" )");
    ui->listMarkers->addItem("Marker 3 = ( "+marker_x3+" , " +marker_y3+" , "+marker_z3+" )");



    ui->listKeypoints->addItem("Entry Point    =   ( "+entry_x+" , "+entry_y+" , "+entry_z+" )");
    ui->listKeypoints->addItem("Cannula Point = ( "+cannula_x+" , "+cannula_y+" , "+cannula_z+" )");

    /******Calculate the FrameCS******/
    float mx1 = marker_x1.toFloat();
    float my1 = marker_y1.toFloat();
    float mz1 = marker_z1.toFloat();

    float mx2 = marker_x2.toFloat();
    float my2 = marker_y2.toFloat();
    float mz2 = marker_z2.toFloat();

    float mx3 = marker_x3.toFloat();
    float my3 = marker_y3.toFloat();
    float mz3 = marker_z3.toFloat();

    float ex = entry_x.toFloat();
    float ey = entry_y.toFloat();
    float ez = entry_z.toFloat();

    float cx = cannula_x.toFloat();
    float cy = cannula_y.toFloat();
    float cz = cannula_z.toFloat();

    float tx1 = target1_x.toFloat();
    float ty1 = target1_y.toFloat();
    float tz1 = target1_z.toFloat();



    QVector3D marker1(mx1,my1,mz1);
    QVector3D marker2(mx2,my2,mz2);
    QVector3D marker3(mx3,my3,mz3);

    QVector3D entry(ex,ey,ez);
    QVector3D cannula(cx,cy,cz);
    QVector3D tar1(tx1,ty1,tz1);

    QVector3D nX; // Define new x axis direction
    QVector3D nZ; // Define new z axis direction
    QVector3D midV;

    nX = operator-(marker2,marker1);
    nX.normalize();
    midV = operator+(marker1,marker2);
    midV.operator /=(2);

    nZ = operator-(midV,marker3);
    nZ.normalize();

    QVector3D nY = QVector3D::crossProduct(nZ,nX);// cross product to get new Y axis direction

    ui->listMarkers->addItem("FrameCS x = ( "+QString::number(nX.x())+" , " +QString::number(nX.y())+" , "+QString::number(nX.z())+" )");
    ui->listMarkers->addItem("FrameCS y = ( "+QString::number(nY.x())+" , " +QString::number(nY.y())+" , "+QString::number(nY.z())+" )");
    ui->listMarkers->addItem("FrameCS z = ( "+QString::number(nZ.x())+" , " +QString::number(nZ.y())+" , "+QString::number(nZ.z())+" )");

    cal_angle.x_axis = nX;
    cal_angle.y_axis = nY;
    cal_angle.z_axis = nZ;
    cal_angle.entry = entry;


    QVector3D nC ;
    QVector3D nT1;

    cal_angle.calculate_new_cannula(cannula,nC);
    cal_angle.calculate_new_targets(tar1,nT1);

    cal_angle.cannula = nC;

    ui->listKeypoints->addItem("Cannula in FrameCS = ( "+QString::number(nC.x())+" , "+QString::number(nC.y())+" , "+QString::number(nC.z())+" )");
//    ui->listKeypoints->addItem("Target1 in FrameCS = ( "+QString::number(nT1.x())+" , "+QString::number(nT1.y())+" , "+QString::number(nT1.z())+" )");

}

void MainWindow::open_caldialog()
{
    caldialog = new Calculate();

    caldialog->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

