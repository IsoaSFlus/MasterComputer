#include "setnamedialog.h"
#include "ui_setnamedialog.h"

SetNameDialog::SetNameDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetNameDialog)
{
    mcus = MCUs::mcus();

    ui->setupUi(this);
    ui->lineEdit->setText(mcus->mcu[0]->getName());
    ui->lineEdit_2->setText(mcus->mcu[1]->getName());
    ui->lineEdit_3->setText(mcus->mcu[2]->getName());
    ui->lineEdit_4->setText(mcus->mcu[3]->getName());
}

SetNameDialog::~SetNameDialog()
{
    delete ui;
}

void SetNameDialog::accept()
{
    mcus->mcu[0]->setName(ui->lineEdit->text());
    mcus->mcu[1]->setName(ui->lineEdit_2->text());
    mcus->mcu[2]->setName(ui->lineEdit_3->text());
    mcus->mcu[3]->setName(ui->lineEdit_4->text());
    QDialog::accept();
}
