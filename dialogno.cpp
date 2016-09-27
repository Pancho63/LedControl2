#include "dialogno.h"
#include "ui_dialogno.h"
#include <QDebug>
#include <QSettings>


extern int  selectionCh[24];
extern QString messagesOsc[6];
extern QString namesSlider[6];
extern bool visibles[24];
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
    spinList->append(ui->spinBox_1);
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
    spinList->append(ui->spinBox_15);
    spinList->append(ui->spinBox_16);
    spinList->append(ui->spinBox_17);
    spinList->append(ui->spinBox_18);
    spinList->append(ui->spinBox_19);
    spinList->append(ui->spinBox_20);
    spinList->append(ui->spinBox_21);
    spinList->append(ui->spinBox_22);
    spinList->append(ui->spinBox_23);

    for (int i=0; i<24 ; i++)
    {
      spinList->at(i)->setValue(selectionCh[i]);
    }

    checkList = new QList<QCheckBox*>;
    checkList->append(ui->checkBox);
    checkList->append(ui->checkBox_1);
    checkList->append(ui->checkBox_2);
    checkList->append(ui->checkBox_3);
    checkList->append(ui->checkBox_4);
    checkList->append(ui->checkBox_5);
    checkList->append(ui->checkBox_6);
    checkList->append(ui->checkBox_7);
    checkList->append(ui->checkBox_8);
    checkList->append(ui->checkBox_9);
    checkList->append(ui->checkBox_10);
    checkList->append(ui->checkBox_11);
    checkList->append(ui->checkBox_12);
    checkList->append(ui->checkBox_13);
    checkList->append(ui->checkBox_14);
    checkList->append(ui->checkBox_15);
    checkList->append(ui->checkBox_16);
    checkList->append(ui->checkBox_17);
    checkList->append(ui->checkBox_18);
    checkList->append(ui->checkBox_19);
    checkList->append(ui->checkBox_20);
    checkList->append(ui->checkBox_21);
    checkList->append(ui->checkBox_22);
    checkList->append(ui->checkBox_23);

   for (int i=0; i<24 ; i++)
    {
      checkList->at(i)->setChecked(visibles[i]);
    }


    lineList = new QList<QLineEdit*>;
    lineList->append(ui->lineEdit);
    lineList->append(ui->lineEdit_2);
    lineList->append(ui->lineEdit_3);
    lineList->append(ui->lineEdit_4);
    lineList->append(ui->lineEdit_5);
    lineList->append(ui->lineEdit_6);

    for (int i=0; i<6 ; i++)
    {
      lineList->at(i)->setText(messagesOsc[i]);
    }

    lineTxtList = new QList<QLineEdit*>;
    lineTxtList->append(ui->lineEdit_7);
    lineTxtList->append(ui->lineEdit_8);
    lineTxtList->append(ui->lineEdit_9);
    lineTxtList->append(ui->lineEdit_10);
    lineTxtList->append(ui->lineEdit_11);
    lineTxtList->append(ui->lineEdit_12);

    for (int i=0; i<6 ; i++)
    {
      lineTxtList->at(i)->setText(namesSlider[i]);
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
