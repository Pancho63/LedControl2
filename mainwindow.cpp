#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QSettings>

bool selection[24];
int  selectionCh[24];
bool visibles[24];
QString messagesOsc[6];
QString namesSlider[6];
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


    readSettings();

    ui->label_1->setText(namesSlider[0]);
    ui->label_2->setText(namesSlider[1]);
    ui->label_3->setText(namesSlider[2]);
    ui->label_4->setText(namesSlider[3]);
    ui->label_5->setText(namesSlider[4]);
    ui->label_6->setText(namesSlider[5]);

    connect (group,                   SIGNAL(buttonToggled(int,bool)), this, SLOT(selected(int,bool)));
    connect (ui->pushButton_Deselect, SIGNAL(pressed()), this,               SLOT(reset()));
    connect (ui->pushButton_AllZero,  SIGNAL(pressed()), this,               SLOT(raz()));

    connect (ui->verticalSlider,   SIGNAL(sliderMoved(int)), this, SLOT(red(int)));
    connect (ui->verticalSlider_2, SIGNAL(sliderMoved(int)), this, SLOT(green(int)));
    connect (ui->verticalSlider_3, SIGNAL(sliderMoved(int)), this, SLOT(blue(int)));
    connect (ui->verticalSlider_4, SIGNAL(sliderMoved(int)), this, SLOT(white(int)));
    connect (ui->verticalSlider_5, SIGNAL(sliderMoved(int)), this, SLOT(amber(int)));
    connect (ui->verticalSlider_6, SIGNAL(sliderMoved(int)), this, SLOT(strobe(int)));
    connect (ui->verticalSlider_7, SIGNAL(sliderMoved(int)), this, SLOT(master(int)));

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

void MainWindow::red(int value)
{
    unsigned short int shValue = value;
    for (int i=0; i<24 ; i++)
    {
       if (selection[i])
       {int ch = group->button(i)->text().toInt();
           Message msg("/device"); msg.pushStr(messagesOsc[0].toStdString()); msg.pushInt32(ch); msg.pushInt32(shValue); sendOSC(msg);
       }
}}

void MainWindow::green(int value)
{
    unsigned short int shValue = value;
    for (int i=0; i<24 ; i++)
    {
       if (selection[i])
       {int ch = group->button(i)->text().toInt();
           Message msg("/device"); msg.pushStr(messagesOsc[1].toStdString()); msg.pushInt32(ch); msg.pushInt32(shValue); sendOSC(msg);
       }
}}

void MainWindow::blue(int value)
{
    unsigned short int shValue = value;
    for (int i=0; i<24 ; i++)
    {
       if (selection[i])
       {int ch = group->button(i)->text().toInt();
           Message msg("/device"); msg.pushStr(messagesOsc[2].toStdString()); msg.pushInt32(ch); msg.pushInt32(shValue); sendOSC(msg);
       }
}}

void MainWindow::white(int value)
{
    unsigned short int shValue = value;
    for (int i=0; i<24 ; i++)
    {
       if (selection[i])
       {int ch = group->button(i)->text().toInt();
           Message msg("/device"); msg.pushStr(messagesOsc[3].toStdString()); msg.pushInt32(ch); msg.pushInt32(shValue); sendOSC(msg);
       }
}}

void MainWindow::amber(int value)
{
    unsigned short int shValue = value;
    for (int i=0; i<24 ; i++)
    {
       if (selection[i])
       {int ch = group->button(i)->text().toInt();
           Message msg("/device"); msg.pushStr(messagesOsc[4].toStdString()); msg.pushInt32(ch); msg.pushInt32(shValue); sendOSC(msg);
       }
}}

void MainWindow::strobe(int value)
{
    unsigned short int shValue = value;
    for (int i=0; i<24 ; i++)
    {
       if (selection[i])
       {int ch = group->button(i)->text().toInt();
           Message msg("/device"); msg.pushStr(messagesOsc[5].toStdString()); msg.pushInt32(ch); msg.pushInt32(shValue); sendOSC(msg);
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
    ui->pushButton_0->setChecked(vrai);
    ui->pushButton_1->setChecked(vrai);
    ui->pushButton_2->setChecked(vrai);
    ui->pushButton_3->setChecked(vrai);
    ui->pushButton_4->setChecked(vrai);
}

void MainWindow::line2(bool vrai)
{
    ui->pushButton_5->setChecked(vrai);
    ui->pushButton_6->setChecked(vrai);
    ui->pushButton_7->setChecked(vrai);
    ui->pushButton_8->setChecked(vrai);
    ui->pushButton_9->setChecked(vrai);
}

void MainWindow::line3(bool vrai)
{
    ui->pushButton_10->setChecked(vrai);
    ui->pushButton_11->setChecked(vrai);
    ui->pushButton_12->setChecked(vrai);
    ui->pushButton_13->setChecked(vrai);
    ui->pushButton_14->setChecked(vrai);
}

void MainWindow::line4(bool vrai)
{
    ui->pushButton_15->setChecked(vrai);
    ui->pushButton_16->setChecked(vrai);
    ui->pushButton_17->setChecked(vrai);
    ui->pushButton_18->setChecked(vrai);
    ui->pushButton_19->setChecked(vrai);
}

void MainWindow::line5(bool vrai)
{
    ui->pushButton_20->setChecked(vrai);
    ui->pushButton_21->setChecked(vrai);
    ui->pushButton_22->setChecked(vrai);
    ui->pushButton_23->setChecked(vrai);
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

    for (int i=0; i<24 ; i++)
    {
       if (selection[i])
       {int ch = group->button(i)->text().toInt();
          Message  msg("/device");  msg.pushStr(messagesOsc[0].toStdString());  msg.pushInt32(ch);  msg.pushInt32(0);  sendOSC(msg);
          Message msg1("/device"); msg1.pushStr(messagesOsc[1].toStdString()); msg1.pushInt32(ch); msg1.pushInt32(0); sendOSC(msg1);
          Message msg2("/device"); msg2.pushStr(messagesOsc[2].toStdString()); msg2.pushInt32(ch); msg2.pushInt32(0); sendOSC(msg2);
          Message msg3("/device"); msg3.pushStr(messagesOsc[3].toStdString()); msg3.pushInt32(ch); msg3.pushInt32(0); sendOSC(msg3);
          Message msg4("/device"); msg4.pushStr(messagesOsc[4].toStdString()); msg4.pushInt32(ch); msg4.pushInt32(0); sendOSC(msg4);
          Message msg5("/device"); msg5.pushStr(messagesOsc[5].toStdString()); msg5.pushInt32(ch); msg5.pushInt32(0); sendOSC(msg5);
          Message msg6("/circ/level");                                         msg6.pushInt32(ch); msg6.pushInt32(0); sendOSC(msg6);
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

    settings.setValue("name0", namesSlider[0]);
    settings.setValue("name1", namesSlider[1]);
    settings.setValue("name2", namesSlider[2]);
    settings.setValue("name3", namesSlider[3]);
    settings.setValue("name4", namesSlider[4]);
    settings.setValue("name5", namesSlider[5]);

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
    for (int i=0; i<24 ; i++)
    group->button(i)->setVisible(visibles[i]);
    }

    messagesOsc[0]=settings.value("msg0", "/COLOUR/RED"   ).toString();
    messagesOsc[1]=settings.value("msg1", "/COLOUR/GREEN" ).toString();
    messagesOsc[2]=settings.value("msg2", "/COLOUR/BLUE"  ).toString();
    messagesOsc[3]=settings.value("msg3", "/COLOUR/WHITE" ).toString();
    messagesOsc[4]=settings.value("msg4", "/COLOUR/AMBER" ).toString();
    messagesOsc[5]=settings.value("msg5", "/EFFECT/STROBE").toString();

    namesSlider[0]=settings.value("name0", "Rouge ").toString();
    namesSlider[1]=settings.value("name1", " Vert ").toString();
    namesSlider[2]=settings.value("name2", " Bleu ").toString();
    namesSlider[3]=settings.value("name3", "Blanc ").toString();
    namesSlider[4]=settings.value("name4", "Ambre ").toString();
    namesSlider[5]=settings.value("name5", "Strobe").toString();

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
    if (event->key()== 87) red(65280);
    if (event->key()== 88) green(65280);
    if (event->key()== 67) blue(65280);
    if (event->key()== 86) white(65280);
    if (event->key()== 66) amber(65280);
    if (event->key()== 78) strobe(65280);
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
    if (event->key()== 87) red(0);
    if (event->key()== 88) green(0);
    if (event->key()== 67) blue(0);
    if (event->key()== 86) white(0);
    if (event->key()== 66) amber(0);
    if (event->key()== 78) strobe(0);
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
    }

    for (int i=0 ; i<6 ; i++)
    {
    messagesOsc[i] = dial->lineList->at(i)->text();
    }

    for (int i=0 ; i<6 ; i++)
    {
    namesSlider[i] = dial->lineTxtList->at(i)->text();
    }

    ui->label_1->setText(namesSlider[0]);
    ui->label_2->setText(namesSlider[1]);
    ui->label_3->setText(namesSlider[2]);
    ui->label_4->setText(namesSlider[3]);
    ui->label_5->setText(namesSlider[4]);
    ui->label_6->setText(namesSlider[5]);

    for (int i=0; i<24 ; i++)
    {
    visibles[i] = dial->checkList->at(i)->checkState();
    group->button(i)->setVisible(visibles[i]);
    }

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
}
