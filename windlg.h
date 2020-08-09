#ifndef WINDLG_H
#define WINDLG_H

#include <QDialog>
#include <QPushButton>
#include <QAbstractButton>
#include <QMessageBox>

namespace Ui {
class winDlg;
}

class winDlg : public QDialog
{
    Q_OBJECT

public:
    explicit winDlg(QWidget *parent = 0);
    ~winDlg();

signals:
    void winSend(QString data);

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);

private:
    Ui::winDlg *ui;
};

#endif // WINDLG_H
