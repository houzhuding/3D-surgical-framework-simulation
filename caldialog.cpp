#include "caldialog.h"
#include "ui_caldialog.h"

calDialog::calDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::calDialog)
{
    ui->setupUi(this);
}

calDialog::~calDialog()
{
    delete ui;
}

void calDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()){
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;

    }
}
