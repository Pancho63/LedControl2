#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QSettings>

bool selection[24];
int  selectionCh[24];
bool visibles[24];
QString messagesOsc[10];
QString namesSlider[10];
bool visiblesSliders[10];
QString path ;
bool exist = false;



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
path = (QCoreApplication::applicationDirPath()+"/saves/");
    ui->setupUi(this);
    setWindowTitle("");

    QShortcut* shortcutUp =   new QShortcut(QKeySequence(Qt::Key_Up),          this);
    QShortcut* shortcutDown = new QShortcut(QKeySequence(Qt::Key_Down),        this);
    QShortcut* shortcutRec =  new QShortcut(QKeySequence(Qt::SHIFT+Qt::Key_R), this);
    QShortcut* shortcutMod =  new QShortcut(QKeySequence(Qt::SHIFT+Qt::Key_M), this);

    connect (shortcutUp,   SIGNAL(activated()), this, SLOT(prev()));
    connect (shortcutDown, SIGNAL(activated()), this, SLOT(next()));
    connect (shortcutRec,  SIGNAL(activated()), this, SLOT(rec()));
    connect (shortcutMod,  SIGNAL(activated()), this, SLOT(modify()));

        group = new QButtonGroup;
        group->addButton(ui->pushButton_0, 0);
        group->addButton(ui->pushButton_1, 1);
        group->addButton(ui->pushButton_2, 2);
        group->addButton(ui->pushButton_3, 3);
        group->addButton(ui->pushButton_4, 4);
        group->addButton(ui->pushButton_5, 5);
        group->addButton(ui->pushButton_6, 6);
        group->addButton(ui->pushButton_7, 7);
        group->addButton(ui->pushButton_8, 8);
        group->addButton(ui->pushButton_9, 9);
        group->addButton(ui->pushButton_10, 10);
        group->addButton(ui->pushButton_11, 11);
        group->addButton(ui->pushButton_12, 12);
        group->addButton(ui->pushButton_13, 13);
        group->addButton(ui->pushButton_14, 14);
        group->addButton(ui->pushButton_15, 15);
        group->addButton(ui->pushButton_16, 16);
        group->addButton(ui->pushButton_17, 17);
        group->addButton(ui->pushButton_18, 18);
        group->addButton(ui->pushButton_19, 19);
        group->addButton(ui->pushButton_20, 20);
        group->addButton(ui->pushButton_21, 21);
        group->addButton(ui->pushButton_22, 22);
        group->addButton(ui->pushButton_23, 23);
        group->setExclusive(false);

        groupDeGroupe = new QList<QPushButton*>;
        groupDeGroupe->append(ui->pushButton_Group1);
        groupDeGroupe->append(ui->pushButton_Group2);
        groupDeGroupe->append(ui->pushButton_Group3);
        groupDeGroupe->append(ui->pushButton_Group4);
        groupDeGroupe->append(ui->pushButton_Group5);

        groupDeSliders = new QList<QSlider*>;
        groupDeSliders->append(ui->verticalSlider);
        groupDeSliders->append(ui->verticalSlider_2);
        groupDeSliders->append(ui->verticalSlider_3);
        groupDeSliders->append(ui->verticalSlider_4);
        groupDeSliders->append(ui->verticalSlider_5);
        groupDeSliders->append(ui->verticalSlider_6);
        groupDeSliders->append(ui->verticalSlider_7);
        groupDeSliders->append(ui->verticalSlider_8);
        groupDeSliders->append(ui->verticalSlider_9);
        groupDeSliders->append(ui->verticalSlider_10);

        groupDeLabelSlid = new QList<QLabel*>;
        groupDeLabelSlid->append(ui->label_1);
        groupDeLabelSlid->append(ui->label_2);
        groupDeLabelSlid->append(ui->label_3);
        groupDeLabelSlid->append(ui->label_4);
        groupDeLabelSlid->append(ui->label_5);
        groupDeLabelSlid->append(ui->label_6);
        groupDeLabelSlid->append(ui->label_7);
        groupDeLabelSlid->append(ui->label_8);
        groupDeLabelSlid->append(ui->label_9);
        groupDeLabelSlid->append(ui->label_10);


    readSettings();

    ui->label_1->setText(namesSlider[0]);
    ui->label_2->setText(namesSlider[1]);
    ui->label_3->setText(namesSlider[2]);
    ui->label_4->setText(namesSlider[3]);
    ui->label_5->setText(namesSlider[4]);
    ui->label_6->setText(namesSlider[5]);
    ui->label_7->setText(namesSlider[6]);
    ui->label_8->setText(namesSlider[7]);
    ui->label_9->setText(namesSlider[8]);
    ui->label_10->setText(namesSlider[9]);
    ui->label_Master->setText("Master");

    connect (group,                   SIGNAL(buttonToggled(int,bool)), this, SLOT(selected(int,bool)));
    connect (ui->pushButton_Deselect, SIGNAL(pressed()), this,               SLOT(reset()));
    connect (ui->pushButton_AllZero,  SIGNAL(pressed()), this,               SLOT(raz()));

    connect (ui->verticalSlider,   SIGNAL(sliderMoved(int)), this, SLOT(mess1(int)));
    connect (ui->verticalSlider_2, SIGNAL(sliderMoved(int)), this, SLOT(mess2(int)));
    connect (ui->verticalSlider_3, SIGNAL(sliderMoved(int)), this, SLOT(mess3(int)));
    connect (ui->verticalSlider_4, SIGNAL(sliderMoved(int)), this, SLOT(mess4(int)));
    connect (ui->verticalSlider_5, SIGNAL(sliderMoved(int)), this, SLOT(mess5(int)));
    connect (ui->verticalSlider_6, SIGNAL(sliderMoved(int)), this, SLOT(mess6(int)));
    connect (ui->verticalSlider_7, SIGNAL(sliderMoved(int)), this, SLOT(mess7(int)));
    connect (ui->verticalSlider_8, SIGNAL(sliderMoved(int)), this, SLOT(mess8(int)));
    connect (ui->verticalSlider_9, SIGNAL(sliderMoved(int)), this, SLOT(mess9(int)));
    connect (ui->verticalSlider_10, SIGNAL(sliderMoved(int)), this, SLOT(mess10(int)));
    connect (ui->verticalSlider_Master, SIGNAL(sliderMoved(int)), this, SLOT(master(int)));

    connect (ui->pushButton_Group1, SIGNAL(toggled(bool)), this, SLOT(line1(bool)));
    connect (ui->pushButton_Group2, SIGNAL(toggled(bool)), this, SLOT(line2(bool)));
    connect (ui->pushButton_Group3, SIGNAL(toggled(bool)), this, SLOT(line3(bool)));
    connect (ui->pushButton_Group4, SIGNAL(toggled(bool)), this, SLOT(line4(bool)));
    connect (ui->pushButton_Group5, SIGNAL(toggled(bool)), this, SLOT(line5(bool)));

    connect (ui->pushButton_Rec,  SIGNAL(pressed()), this, SLOT(rec()));
    connect (ui->pushButton_Mod,  SIGNAL(pressed()), this, SLOT(modify()));
    connect (ui->pushButton_Prev, SIGNAL(pressed()), this, SLOT(prev()));
    connect (ui->pushButton_Next, SIGNAL(pressed()), this, SLOT(next()));

    connect (ui->pushButton_Edit, SIGNAL(pressed()), this, SLOT(ouvrirDial()));

    for (int j=0; j<4 ; j++)
    {
        if (!(visibles[5*j]) & !(visibles[5*j+1])& !(visibles[5*j+2])& !(visibles[5*j+3])& !(visibles[5*j+4]))
        {groupDeGroupe->at(j)->setVisible(false);}
        else  {groupDeGroupe->at(j)->setVisible(true);}
    }
    if (!(visibles[20]) & !(visibles[21])& !(visibles[22])& !(visibles[23]))
    {groupDeGroupe->at(4)->setVisible(false);}
    else  {groupDeGroupe->at(4)->setVisible(true);}

udpSocketSend = new QUdpSocket(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::selected(int channel,bool vrai)
{
selection[channel] = vrai;
}

void MainWindow::sendOSC(Message msg)
    {
    PacketWriter pw;
    pw.addMessage(msg);
    udpSocketSend->writeDatagram(pw.packetData(), pw.packetSize(), QHostAddress("127.0.0.1"), 7000);
    }

void MainWindow::mess1(int value)
{
    unsigned short int shValue = value;
    for (int i=0; i<24 ; i++)
    {
       if (selection[i])
       {int ch = group->button(i)->text().toInt();
           Message msg("/device"); msg.pushStr(messagesOsc[0].toStdString()); msg.pushInt32(ch); msg.pushInt32(shValue); sendOSC(msg);
       }
}}

void MainWindow::mess2(int value)
{
    unsigned short int shValue = value;
    for (int i=0; i<24 ; i++)
    {
       if (selection[i])
       {int ch = group->button(i)->text().toInt();
           Message msg("/device"); msg.pushStr(messagesOsc[1].toStdString()); msg.pushInt32(ch); msg.pushInt32(shValue); sendOSC(msg);
       }
}}

void MainWindow::mess3(int value)
{
    unsigned short int shValue = value;
    for (int i=0; i<24 ; i++)
    {
       if (selection[i])
       {int ch = group->button(i)->text().toInt();
           Message msg("/device"); msg.pushStr(messagesOsc[2].toStdString()); msg.pushInt32(ch); msg.pushInt32(shValue); sendOSC(msg);
       }
}}

void MainWindow::mess4(int value)
{
    unsigned short int shValue = value;
    for (int i=0; i<24 ; i++)
    {
       if (selection[i])
       {int ch = group->button(i)->text().toInt();
           Message msg("/device"); msg.pushStr(messagesOsc[3].toStdString()); msg.pushInt32(ch); msg.pushInt32(shValue); sendOSC(msg);
       }
}}

void MainWindow::mess5(int value)
{
    unsigned short int shValue = value;
    for (int i=0; i<24 ; i++)
    {
       if (selection[i])
       {int ch = group->button(i)->text().toInt();
           Message msg("/device"); msg.pushStr(messagesOsc[4].toStdString()); msg.pushInt32(ch); msg.pushInt32(shValue); sendOSC(msg);
       }
}}

void MainWindow::mess6(int value)
{
    unsigned short int shValue = value;
    for (int i=0; i<24 ; i++)
    {
       if (selection[i])
       {int ch = group->button(i)->text().toInt();
           Message msg("/device"); msg.pushStr(messagesOsc[5].toStdString()); msg.pushInt32(ch); msg.pushInt32(shValue); sendOSC(msg);
       }
}}
void MainWindow::mess7(int value)
{
    unsigned short int shValue = value;
    for (int i=0; i<24 ; i++)
    {
       if (selection[i])
       {int ch = group->button(i)->text().toInt();
           Message msg("/device"); msg.pushStr(messagesOsc[6].toStdString()); msg.pushInt32(ch); msg.pushInt32(shValue); sendOSC(msg);
       }
}}
void MainWindow::mess8(int value)
{
    unsigned short int shValue = value;
    for (int i=0; i<24 ; i++)
    {
       if (selection[i])
       {int ch = group->button(i)->text().toInt();
           Message msg("/device"); msg.pushStr(messagesOsc[7].toStdString()); msg.pushInt32(ch); msg.pushInt32(shValue); sendOSC(msg);
       }
}}
void MainWindow::mess9(int value)
{
    unsigned short int shValue = value;
    for (int i=0; i<24 ; i++)
    {
       if (selection[i])
       {int ch = group->button(i)->text().toInt();
           Message msg("/device"); msg.pushStr(messagesOsc[8].toStdString()); msg.pushInt32(ch); msg.pushInt32(shValue); sendOSC(msg);
       }
}}
void MainWindow::mess10(int value)
{
    unsigned short int shValue = value;
    for (int i=0; i<24 ; i++)
    {
       if (selection[i])
       {int ch = group->button(i)->text().toInt();
           Message msg("/device"); msg.pushStr(messagesOsc[9].toStdString()); msg.pushInt32(ch); msg.pushInt32(shValue); sendOSC(msg);
       }
}}
void MainWindow::master(int value)
{
    for (int i=0; i<24 ; i++)
    {
       if (selection[i])
       {
           int ch = group->button(i)->text().toInt();
           Message msg("/circ/level"); msg.pushInt32(ch); msg.pushInt32(value); sendOSC(msg);
       }
}}

void MainWindow::reset()
{
    ui->verticalSlider->setValue(0);
    ui->verticalSlider_2->setValue(0);
    ui->verticalSlider_3->setValue(0);
    ui->verticalSlider_4->setValue(0);
    ui->verticalSlider_5->setValue(0);
    ui->verticalSlider_6->setValue(0);
    ui->verticalSlider_7->setValue(0);
    ui->verticalSlider_8->setValue(0);
    ui->verticalSlider_9->setValue(0);
    ui->verticalSlider_10->setValue(0);
    ui->verticalSlider_Master->setValue(0);

    ui->pushButton_0->setChecked(false);
    ui->pushButton_1->setChecked(false);
    ui->pushButton_2->setChecked(false);
    ui->pushButton_3->setChecked(false);
    ui->pushButton_4->setChecked(false);
    ui->pushButton_5->setChecked(false);
    ui->pushButton_6->setChecked(false);
    ui->pushButton_7->setChecked(false);
    ui->pushButton_8->setChecked(false);
    ui->pushButton_9->setChecked(false);
    ui->pushButton_10->setChecked(false);
    ui->pushButton_11->setChecked(false);
    ui->pushButton_12->setChecked(false);
    ui->pushButton_13->setChecked(false);
    ui->pushButton_14->setChecked(false);
    ui->pushButton_15->setChecked(false);
    ui->pushButton_16->setChecked(false);
    ui->pushButton_17->setChecked(false);
    ui->pushButton_18->setChecked(false);
    ui->pushButton_19->setChecked(false);
    ui->pushButton_20->setChecked(false);
    ui->pushButton_21->setChecked(false);
    ui->pushButton_22->setChecked(false);
    ui->pushButton_23->setChecked(false);
    ui->pushButton_Group1->setChecked(false);
    ui->pushButton_Group2->setChecked(false);
    ui->pushButton_Group3->setChecked(false);
    ui->pushButton_Group4->setChecked(false);
    ui->pushButton_Group5->setChecked(false);
}


void MainWindow::line1(bool vrai)
{
    if(visibles[0]) ui->pushButton_0->setChecked(vrai);
    if(visibles[1]) ui->pushButton_1->setChecked(vrai);
    if(visibles[2])ui->pushButton_2->setChecked(vrai);
    if(visibles[3])ui->pushButton_3->setChecked(vrai);
    if(visibles[4]) ui->pushButton_4->setChecked(vrai);
}

void MainWindow::line2(bool vrai)
{
    if(visibles[5]) ui->pushButton_5->setChecked(vrai);
    if(visibles[6]) ui->pushButton_6->setChecked(vrai);
    if(visibles[7]) ui->pushButton_7->setChecked(vrai);
    if(visibles[8]) ui->pushButton_8->setChecked(vrai);
    if(visibles[9]) ui->pushButton_9->setChecked(vrai);
}

void MainWindow::line3(bool vrai)
{
    if(visibles[10]) ui->pushButton_10->setChecked(vrai);
    if(visibles[11]) ui->pushButton_11->setChecked(vrai);
    if(visibles[12]) ui->pushButton_12->setChecked(vrai);
    if(visibles[13]) ui->pushButton_13->setChecked(vrai);
    if(visibles[14]) ui->pushButton_14->setChecked(vrai);
}

void MainWindow::line4(bool vrai)
{
    if(visibles[15]) ui->pushButton_15->setChecked(vrai);
    if(visibles[16]) ui->pushButton_16->setChecked(vrai);
    if(visibles[17]) ui->pushButton_17->setChecked(vrai);
    if(visibles[18]) ui->pushButton_18->setChecked(vrai);
    if(visibles[19]) ui->pushButton_19->setChecked(vrai);
}

void MainWindow::line5(bool vrai)
{
    if(visibles[20]) ui->pushButton_20->setChecked(vrai);
    if(visibles[21]) ui->pushButton_21->setChecked(vrai);
    if(visibles[22]) ui->pushButton_22->setChecked(vrai);
    if(visibles[23]) ui->pushButton_23->setChecked(vrai);
}
void MainWindow::raz()
{
    ui->verticalSlider  ->setValue(0);
    ui->verticalSlider_2->setValue(0);
    ui->verticalSlider_3->setValue(0);
    ui->verticalSlider_4->setValue(0);
    ui->verticalSlider_5->setValue(0);
    ui->verticalSlider_6->setValue(0);
    ui->verticalSlider_7->setValue(0);
    ui->verticalSlider_8->setValue(0);
    ui->verticalSlider_9->setValue(0);
    ui->verticalSlider_10->setValue(0);
    ui->verticalSlider_Master->setValue(0);

    for (int i=0; i<24 ; i++)
    {
       if (selection[i])
       {int ch = group->button(i)->text().toInt();
          Message  msg("/device");  msg.pushStr(messagesOsc[0].toStdString());  msg.pushInt32(ch);   msg.pushInt32(0);   sendOSC(msg);
          Message msg1("/device"); msg1.pushStr(messagesOsc[1].toStdString()); msg1.pushInt32(ch);  msg1.pushInt32(0);  sendOSC(msg1);
          Message msg2("/device"); msg2.pushStr(messagesOsc[2].toStdString()); msg2.pushInt32(ch);  msg2.pushInt32(0);  sendOSC(msg2);
          Message msg3("/device"); msg3.pushStr(messagesOsc[3].toStdString()); msg3.pushInt32(ch);  msg3.pushInt32(0);  sendOSC(msg3);
          Message msg4("/device"); msg4.pushStr(messagesOsc[4].toStdString()); msg4.pushInt32(ch);  msg4.pushInt32(0);  sendOSC(msg4);
          Message msg5("/device"); msg5.pushStr(messagesOsc[5].toStdString()); msg5.pushInt32(ch);  msg5.pushInt32(0);  sendOSC(msg5);
          Message msg6("/device"); msg6.pushStr(messagesOsc[6].toStdString()); msg6.pushInt32(ch);  msg6.pushInt32(0);  sendOSC(msg6);
          Message msg7("/device"); msg7.pushStr(messagesOsc[7].toStdString()); msg7.pushInt32(ch);  msg7.pushInt32(0);  sendOSC(msg7);
          Message msg8("/device"); msg8.pushStr(messagesOsc[8].toStdString()); msg8.pushInt32(ch);  msg8.pushInt32(0);  sendOSC(msg8);
          Message msg9("/device"); msg9.pushStr(messagesOsc[9].toStdString()); msg9.pushInt32(ch);  msg9.pushInt32(0);  sendOSC(msg9);
          Message msg10("/circ/level");                                       msg10.pushInt32(ch); msg10.pushInt32(0); sendOSC(msg10);
       }
}
}

void MainWindow::rec()
{
    Message msg("/pad/record"); msg.pushInt32(1); sendOSC(msg);
}

void MainWindow::modify()
{
    Message msg("/pad/update"); msg.pushInt32(1); sendOSC(msg);
}

void MainWindow::prev()
{
    Message msg("/seq/moins"); msg.pushInt32(1); sendOSC(msg);
}

void MainWindow::next()
{
    Message msg("/seq/plus"); msg.pushInt32(1); sendOSC(msg);
}

void MainWindow::writeSettings()
{
    QSettings settings(path +  "LedControl.ini", QSettings::IniFormat);
    for (int i=0; i<24 ; i++)
    {
    int n = selectionCh[i];
    settings.setValue("ch"+QString::number(i), n);
    settings.setValue("v"+QString::number(i), visibles[i]);
    }
    settings.setValue("msg0", messagesOsc[0]);
    settings.setValue("msg1", messagesOsc[1]);
    settings.setValue("msg2", messagesOsc[2]);
    settings.setValue("msg3", messagesOsc[3]);
    settings.setValue("msg4", messagesOsc[4]);
    settings.setValue("msg5", messagesOsc[5]);
    settings.setValue("msg6", messagesOsc[6]);
    settings.setValue("msg7", messagesOsc[7]);
    settings.setValue("msg8", messagesOsc[8]);
    settings.setValue("msg9", messagesOsc[9]);

    settings.setValue("name0", namesSlider[0]);
    settings.setValue("name1", namesSlider[1]);
    settings.setValue("name2", namesSlider[2]);
    settings.setValue("name3", namesSlider[3]);
    settings.setValue("name4", namesSlider[4]);
    settings.setValue("name5", namesSlider[5]);
    settings.setValue("name6", namesSlider[6]);
    settings.setValue("name7", namesSlider[7]);
    settings.setValue("name8", namesSlider[8]);
    settings.setValue("name9", namesSlider[9]);

    for (int i=0; i<10 ; i++)
    {
    settings.setValue("vS"+QString::number(i), visiblesSliders[i]);
    }

    settings.beginGroup("MainWindow");
    settings.setValue("size", size());
    settings.setValue("pos", pos());
    settings.endGroup();
}

void MainWindow::readSettings()
{
    QSettings settings(path +  "LedControl.ini", QSettings::IniFormat);
    for (int i=0; i<24 ; i++)
    {
    selectionCh[i]=settings.value("ch"+QString::number(i), i+61).toInt();
    group->button(i)->setText(QString::number(selectionCh[i]));
    visibles[i]=settings.value("v"+QString::number(i), true).toBool();
    group->button(i)->setVisible(visibles[i]);
    }

    messagesOsc[0]=settings.value("msg0", "/COLOUR/RED"   ).toString();
    messagesOsc[1]=settings.value("msg1", "/COLOUR/GREEN" ).toString();
    messagesOsc[2]=settings.value("msg2", "/COLOUR/BLUE"  ).toString();
    messagesOsc[3]=settings.value("msg3", "/COLOUR/WHITE" ).toString();
    messagesOsc[4]=settings.value("msg4", "/COLOUR/AMBER" ).toString();
    messagesOsc[5]=settings.value("msg5", "/EFFECT/STROBE").toString();
    messagesOsc[6]=settings.value("msg6", " "  ).toString();
    messagesOsc[7]=settings.value("msg7", " " ).toString();
    messagesOsc[8]=settings.value("msg8", " " ).toString();
    messagesOsc[9]=settings.value("msg9", " ").toString();

    namesSlider[0]=settings.value("name0", "Rouge ").toString();
    namesSlider[1]=settings.value("name1", " Vert ").toString();
    namesSlider[2]=settings.value("name2", " Bleu ").toString();
    namesSlider[3]=settings.value("name3", "Blanc ").toString();
    namesSlider[4]=settings.value("name4", "Ambre ").toString();
    namesSlider[5]=settings.value("name5", "Strobe").toString();
    namesSlider[6]=settings.value("name6", "Autre1").toString();
    namesSlider[7]=settings.value("name7", "Autre2").toString();
    namesSlider[8]=settings.value("name8", "Autre3").toString();
    namesSlider[9]=settings.value("name9", "Autre4").toString();

    for (int i=0; i<10 ; i++)
    {
        visiblesSliders[i]=settings.value("vS"+QString::number(i), true).toBool();
        groupDeSliders->at(i)->setVisible(visiblesSliders[i]);
        groupDeLabelSlid->at(i)->setVisible(visiblesSliders[i]);
    }
    settings.beginGroup("MainWindow");
    resize(settings.value("size", QSize(889, 125)).toSize());
    move  (settings.value("pos",  QPoint(187, 23)).toPoint());
    settings.endGroup();

}

void MainWindow::closeEvent(QCloseEvent *)
{
        writeSettings();
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key()== 87) mess1(65280);
    if (event->key()== 88) mess2(65280);
    if (event->key()== 67) mess3(65280);
    if (event->key()== 86) mess4(65280);
    if (event->key()== 66) mess5(65280);
    if (event->key()== 78) mess6(65280);
    if (event->key()== 44) master(65280);

    if (event->key()== 87) ui->verticalSlider->setValue(65280);
    if (event->key()== 88) ui->verticalSlider_2->setValue(65280);
    if (event->key()== 67) ui->verticalSlider_3->setValue(65280);
    if (event->key()== 86) ui->verticalSlider_4->setValue(65280);
    if (event->key()== 66) ui->verticalSlider_5->setValue(65280);
    if (event->key()== 78) ui->verticalSlider_6->setValue(65280);
    if (event->key()== 44) ui->verticalSlider_7->setValue(65280);
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key()== 87) mess1(0);
    if (event->key()== 88) mess2(0);
    if (event->key()== 67) mess3(0);
    if (event->key()== 86) mess4(0);
    if (event->key()== 66) mess5(0);
    if (event->key()== 78) mess6(0);
    if (event->key()== 44) master(0);

    if (event->key()== 87) ui->verticalSlider->setValue(0);
    if (event->key()== 88) ui->verticalSlider_2->setValue(0);
    if (event->key()== 67) ui->verticalSlider_3->setValue(0);
    if (event->key()== 86) ui->verticalSlider_4->setValue(0);
    if (event->key()== 66) ui->verticalSlider_5->setValue(0);
    if (event->key()== 78) ui->verticalSlider_6->setValue(0);
    if (event->key()== 44) ui->verticalSlider_7->setValue(0);
}

void MainWindow::ouvrirDial()
{ if (!exist)
    {
     dial = new DialogNo();
     dial->show();
     exist=true;
     connect (dial, SIGNAL(accepted()), this, SLOT(maj()));
    }
}

void MainWindow::maj()
{   for (int i=0; i<24 ; i++)
    {
    selectionCh[i] =  dial->spinList->at(i)->value();
    group->button(i)->setText(QString::number(selectionCh[i]));
    visibles[i] = dial->checkList->at(i)->checkState();
    group->button(i)->setVisible(visibles[i]);
    if (!visibles[i]) selection[i]=false;
    }

    for (int i=0 ; i<10 ; i++)
    {
    messagesOsc[i] = dial->lineList->at(i)->text();
    namesSlider[i] = dial->lineTxtList->at(i)->text();
    visiblesSliders[i] = dial->checkSliderList->at(i)->checkState();
    groupDeSliders->at(i)->setVisible(visiblesSliders[i]);
    groupDeLabelSlid->at(i)->setVisible(visiblesSliders[i]);
    }

    ui->label_1->setText(namesSlider[0]);
    ui->label_2->setText(namesSlider[1]);
    ui->label_3->setText(namesSlider[2]);
    ui->label_4->setText(namesSlider[3]);
    ui->label_5->setText(namesSlider[4]);
    ui->label_6->setText(namesSlider[5]);
    ui->label_7->setText(namesSlider[6]);
    ui->label_8->setText(namesSlider[7]);
    ui->label_9->setText(namesSlider[8]);
    ui->label_10->setText(namesSlider[9]);


    for (int j=0; j<4 ; j++)
    {
        if (!(group->button(5*j)->isVisible()) & !(group->button(5*j+1)->isVisible())& !(group->button(5*j+2)->isVisible())& !(group->button(5*j+3)->isVisible())& !(group->button(5*j+4)->isVisible()))
        {groupDeGroupe->at(j)->setVisible(false);}
        else  {groupDeGroupe->at(j)->setVisible(true);}
    }
    if (!(group->button(20)->isVisible()) & !(group->button(21)->isVisible())& !(group->button(22)->isVisible())& !(group->button(23)->isVisible()))
    {groupDeGroupe->at(4)->setVisible(false);}
    else  {groupDeGroupe->at(4)->setVisible(true);}

    writeSettings();
    reset();
}
