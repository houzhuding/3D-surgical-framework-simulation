#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector3D>
#include <QtMath>
#include "calculate.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    int count;

public slots:
    void add();
    void get();
    void open_caldialog();
private:
    Ui::MainWindow *ui;

    Calculate *caldialog;


};



#endif // MAINWINDOW_H
