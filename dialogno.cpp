#include "dialogno.h"
#include "ui_dialogno.h"
#include <QDebug>


extern int  selectionCh[14];
extern bool exist;


DialogNo::DialogNo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogNo)
{
    ui->setupUi(this);

    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(close()));
    connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(close()));



    spinList = new  QList<QSpinBox*>;
    spinList->append(ui->spinBox);
    spinList->append(ui->spinBox_2);
    spinList->append(ui->spinBox_3);
    spinList->append(ui->spinBox_4);
    spinList->append(ui->spinBox_5);
    spinList->append(ui->spinBox_6);
    spinList->append(ui->spinBox_7);
    spinList->append(ui->spinBox_8);
    spinList->append(ui->spinBox_9);
    spinList->append(ui->spinBox_10);
    spinList->append(ui->spinBox_11);
    spinList->append(ui->spinBox_12);
    spinList->append(ui->spinBox_13);
    spinList->append(ui->spinBox_14);


    for (int i=0; i<14 ; i++)
    {
      spinList->at(i)->setValue(selectionCh[i]);
    }


}

DialogNo::~DialogNo()
{
    delete ui;
}


void DialogNo::closeEvent(QCloseEvent *)
{
    exist=false;
}
