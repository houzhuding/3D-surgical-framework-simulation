#ifndef CALDIALOG_H
#define CALDIALOG_H

#include <QMainWindow>

namespace Ui {
class calDialog;
}

class calDialog : public QMainWindow
{
    Q_OBJECT

public:
    explicit calDialog(QWidget *parent = 0);
    ~calDialog();

private:
    Ui::calDialog *ui;

private slots:
    void calculate();

};

#endif // CALDIALOG_H
