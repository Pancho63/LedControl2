#ifndef DIALOGNO_H
#define DIALOGNO_H

#include <QDialog>
#include <QSpinBox>

namespace Ui {
class DialogNo;
}

class DialogNo : public QDialog
{
    Q_OBJECT

public:
    explicit DialogNo(QWidget *parent = 0);
     QList<QSpinBox*> *spinList;
    ~DialogNo();

private:
    Ui::DialogNo *ui;


private slots:
    void closeEvent(QCloseEvent *);
};

#endif // DIALOGNO_H
