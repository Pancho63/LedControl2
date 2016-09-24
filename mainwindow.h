#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QHostAddress>
#include <QShortcut>
#include <QUdpSocket>
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

   void red(int);
   void green(int);
   void blue(int);
   void white(int);
   void amber(int);
   void strobe(int);
   void master(int);

   void line1(bool);
   void line2(bool);
   void line3(bool);

   void rec();
   void modify();
   void prev();
   void next();

   void writeSettings();
   void readSettings();

   void closeEvent(QCloseEvent *);

private:
    Ui::MainWindow *ui;
    QUdpSocket   *udpSocketSend;
    QButtonGroup* group;
    DialogNo *dial;
};

#endif // MAINWINDOW_H
