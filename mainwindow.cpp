#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QSettings>



bool selection[14];
int  selectionCh[14];
QString path ;
bool exist = false;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
path = (QCoreApplication::applicationDirPath()+"/saves/");
    ui->setupUi(this);
    setWindowTitle("");

    QShortcut* shortcutUp = new QShortcut(QKeySequence(Qt::Key_Up), this);
    QShortcut* shortcutDown = new QShortcut(QKeySequence(Qt::Key_Down), this);
    QShortcut* shortcutRec = new QShortcut(QKeySequence(Qt::SHIFT+Qt::Key_R), this);
    QShortcut* shortcutMod = new QShortcut(QKeySequence(Qt::SHIFT+Qt::Key_M), this);

    connect (shortcutUp,   SIGNAL(activated()), this, SLOT(prev()));
    connect (shortcutDown, SIGNAL(activated()), this, SLOT(next()));
    connect (shortcutRec,  SIGNAL(activated()), this, SLOT(rec()));
    connect (shortcutMod,  SIGNAL(activated()), this, SLOT(modify()));

        group = new QButtonGroup;
        group->addButton(ui->pushButton_0);
        group->addButton(ui->pushButton_1);
        group->addButton(ui->pushButton_2);
        group->addButton(ui->pushButton_3);
        group->addButton(ui->pushButton_4);
        group->addButton(ui->pushButton_5);
        group->addButton(ui->pushButton_6);
        group->addButton(ui->pushButton_7);
        group->addButton(ui->pushButton_8);
        group->addButton(ui->pushButton_9);
        group->addButton(ui->pushButton_10);
        group->addButton(ui->pushButton_11);
        group->addButton(ui->pushButton_12);
        group->addButton(ui->pushButton_13);
        group->setExclusive(false);

    readSettings();

    connect (group,             SIGNAL(buttonToggled(int,bool)), this, SLOT(selected(int,bool)));
    connect (ui->pushButton,    SIGNAL(pressed()), this, SLOT(reset()));
    connect (ui->pushButton_16, SIGNAL(pressed()), this, SLOT(raz()));

    connect (ui->verticalSlider,   SIGNAL(sliderMoved(int)), this, SLOT(red(int)));
    connect (ui->verticalSlider_2, SIGNAL(sliderMoved(int)), this, SLOT(green(int)));
    connect (ui->verticalSlider_3, SIGNAL(sliderMoved(int)), this, SLOT(blue(int)));
    connect (ui->verticalSlider_4, SIGNAL(sliderMoved(int)), this, SLOT(white(int)));
    connect (ui->verticalSlider_5, SIGNAL(sliderMoved(int)), this, SLOT(amber(int)));
    connect (ui->verticalSlider_6, SIGNAL(sliderMoved(int)), this, SLOT(strobe(int)));
    connect (ui->verticalSlider_7, SIGNAL(sliderMoved(int)), this, SLOT(master(int)));

    connect (ui->pushButton_14, SIGNAL(toggled(bool)), this, SLOT(line1(bool)));
    connect (ui->pushButton_15, SIGNAL(toggled(bool)), this, SLOT(line2(bool)));
    connect (ui->pushButton_17, SIGNAL(toggled(bool)), this, SLOT(line3(bool)));

    connect (ui->pushButton_18, SIGNAL(pressed()), this, SLOT(rec()));
    connect (ui->pushButton_19, SIGNAL(pressed()), this, SLOT(modify()));
    connect (ui->pushButton_20, SIGNAL(pressed()), this, SLOT(prev()));
    connect (ui->pushButton_21, SIGNAL(pressed()), this, SLOT(next()));

    connect (ui->pushButton_22, SIGNAL(pressed()), this, SLOT(ouvrirDial()));



udpSocketSend = new QUdpSocket(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::selected(int channel,bool vrai)
{channel = 0 - channel - 2;

selection[channel] = vrai;
}

void MainWindow::sendOSC(Message msg)
    {
    PacketWriter pw;
    pw.addMessage(msg);
    udpSocketSend->writeDatagram(pw.packetData(), pw.packetSize(), QHostAddress("127.0.0.1"), 7000);
    }

void MainWindow::red(int value)
{unsigned short int shValue = value;
    for (int i=0; i<14 ; i++)
    {
       if (selection[i])
       {int ch = group->button(-i-2)->text().toInt();
           Message msg("/device"); msg.pushStr("/COLOUR/RED"); msg.pushInt32(ch); msg.pushInt32(shValue); sendOSC(msg);
       }
}}

void MainWindow::green(int value)
{unsigned short int shValue = value;
    for (int i=0; i<14 ; i++)
    {
       if (selection[i])
       {int ch = group->button(-i-2)->text().toInt();
           Message msg("/device"); msg.pushStr("/COLOUR/GREEN"); msg.pushInt32(ch); msg.pushInt32(shValue); sendOSC(msg);
       }
}}

void MainWindow::blue(int value)
{unsigned short int shValue = value;
    for (int i=0; i<14 ; i++)
    {
       if (selection[i])
       {int ch = group->button(-i-2)->text().toInt();
           Message msg("/device"); msg.pushStr("/COLOUR/BLUE"); msg.pushInt32(ch); msg.pushInt32(shValue); sendOSC(msg);
       }
}}

void MainWindow::white(int value)
{unsigned short int shValue = value;
    for (int i=0; i<14 ; i++)
    {
       if (selection[i])
       {int ch = group->button(-i-2)->text().toInt();
           Message msg("/device"); msg.pushStr("/COLOUR/WHITE"); msg.pushInt32(ch); msg.pushInt32(shValue); sendOSC(msg);
       }
}}

void MainWindow::amber(int value)
{unsigned short int shValue = value;
    for (int i=0; i<14 ; i++)
    {
       if (selection[i])
       {int ch = group->button(-i-2)->text().toInt();
           Message msg("/device"); msg.pushStr("/COLOUR/AMBER"); msg.pushInt32(ch); msg.pushInt32(shValue); sendOSC(msg);
       }
}}

void MainWindow::strobe(int value)
{unsigned short int shValue = value;
    for (int i=0; i<14 ; i++)
    {
       if (selection[i])
       {int ch = group->button(-i-2)->text().toInt();
           Message msg("/device"); msg.pushStr("/EFFECT/STROBE"); msg.pushInt32(ch); msg.pushInt32(shValue); sendOSC(msg);
       }
}}
void MainWindow::master(int value)
{
    for (int i=0; i<14 ; i++)
    {
       if (selection[i])
       {int ch = group->button(-i-2)->text().toInt();
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
    ui->pushButton_17->setChecked(false);
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
}
void MainWindow::raz()
{
    ui->verticalSlider->setValue(0);
    ui->verticalSlider_2->setValue(0);
    ui->verticalSlider_3->setValue(0);
    ui->verticalSlider_4->setValue(0);
    ui->verticalSlider_5->setValue(0);
    ui->verticalSlider_6->setValue(0);
    ui->verticalSlider_7->setValue(0);

    for (int i=0; i<14 ; i++)
    {
       if (selection[i])
       {int ch = group->button(-i-2)->text().toInt();
          Message  msg("/device");  msg.pushStr("/COLOUR/RED");    msg.pushInt32(ch);  msg.pushInt32(0);  sendOSC(msg);
          Message msg1("/device"); msg1.pushStr("/COLOUR/GREEN");  msg1.pushInt32(ch); msg1.pushInt32(0); sendOSC(msg1);
          Message msg2("/device"); msg2.pushStr("/COLOUR/BLUE");   msg2.pushInt32(ch); msg2.pushInt32(0); sendOSC(msg2);
          Message msg3("/device"); msg3.pushStr("/COLOUR/WHITE");  msg3.pushInt32(ch); msg3.pushInt32(0); sendOSC(msg3);
          Message msg4("/device"); msg4.pushStr("/COLOUR/AMBER");  msg4.pushInt32(ch); msg4.pushInt32(0); sendOSC(msg4);
          Message msg5("/device"); msg5.pushStr("/EFFECT/STROBE"); msg5.pushInt32(ch); msg5.pushInt32(0); sendOSC(msg5);
      Message msg6("/circ/level"); msg6.pushInt32(ch);             msg6.pushInt32(0);                     sendOSC(msg6);
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
    for (int i=0; i<14 ; i++)
    {int n = selectionCh[i];
    settings.setValue("ch"+QString::number(i), n);
    }
    settings.beginGroup("MainWindow");
    settings.setValue("size", size());
    settings.setValue("pos", pos());
    settings.endGroup();
}

void MainWindow::readSettings()
{
    QSettings settings(path +  "LedControl.ini", QSettings::IniFormat);
    for (int i=0; i<14 ; i++)
    {
    selectionCh[i]=settings.value("ch"+QString::number(i), i+61).toInt();;
    group->button(-i-2)->setText(QString::number(selectionCh[i]));
    }
    settings.beginGroup("MainWindow");
    resize(settings.value("size", QSize(889, 125)).toSize());
    move(settings.value("pos", QPoint(187, 23)).toPoint());
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
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key()== 87) red(0);
    if (event->key()== 88) green(0);
    if (event->key()== 67) blue(0);
    if (event->key()== 86) white(0);
    if (event->key()== 66) amber(0);
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
{       for (int i=0; i<14 ; i++)
    {
    selectionCh[i] =  dial->spinList->at(i)->value();
    group->button(-i-2)->setText(QString::number(selectionCh[i]));
    }
    writeSettings();
}
