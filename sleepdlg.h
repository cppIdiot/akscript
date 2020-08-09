#ifndef SLEEPDLG_H
#define SLEEPDLG_H

#include <QDialog>
#include <QAbstractButton>
#include <QPushButton>
#include <QMessageBox>

namespace Ui {
class sleepDlg;
}

class sleepDlg : public QDialog
{
    Q_OBJECT

public:
    explicit sleepDlg(QWidget *parent = 0);
    ~sleepDlg();

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);


signals:
    void sleepSend(QString data);

private:
    Ui::sleepDlg *ui;
};

#endif // SLEEPDLG_H
