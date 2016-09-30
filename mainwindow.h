#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QSlider>
#include <QLabel>
#include <QHostAddress>
#include <QShortcut>
#include <QUdpSocket>
#include <QKeyEvent>
#include "dialogno.h"

#include "oscpkt.hh"

using namespace oscpkt;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();



private slots:
   void selected(int,bool);
   void sendOSC(Message);
   void reset();
   void raz();
   void ouvrirDial();
   void maj();

   void mess1(int);
   void mess2(int);
   void mess3(int);
   void mess4(int);
   void mess5(int);
   void mess6(int);
   void mess7(int);
   void mess8(int);
   void mess9(int);
   void mess10(int);
   void master(int);

   void line1(bool);
   void line2(bool);
   void line3(bool);
   void line4(bool);
   void line5(bool);

   void rec();
   void modify();
   void prev();
   void next();

   void writeSettings();
   void readSettings();

private:
    Ui::MainWindow *ui;
    QUdpSocket     *udpSocketSend;
    QButtonGroup   *group;
    DialogNo       *dial;
    QList<QPushButton*> *groupDeGroupe;
    QList<QSlider*> *groupDeSliders;
    QList<QLabel*> *groupDeLabelSlid;


protected:
    void closeEvent(QCloseEvent *);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
};

#endif // MAINWINDOW_H
