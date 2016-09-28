#ifndef DIALOGNO_H
#define DIALOGNO_H

#include <QDialog>
#include <QSpinBox>
#include <QLineEdit>
#include <QCheckBox>

namespace Ui {
class DialogNo;
}

class DialogNo : public QDialog
{
    Q_OBJECT

public:
    explicit DialogNo(QWidget *parent = 0);

     QList<QLineEdit*> *lineList;
     QList<QLineEdit*> *lineTxtList;
     QList<QCheckBox*> *checkList;
     QList<QSpinBox*>  *spinList;

    ~DialogNo();

private:
    Ui::DialogNo *ui;


protected:
    void closeEvent(QCloseEvent *);
};

#endif // DIALOGNO_H
