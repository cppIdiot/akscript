#ifndef TIMERECORDDLG_H
#define TIMERECORDDLG_H

#include <QDialog>
#include <QAbstractButton>
#include <QPushButton>
#include <QSettings>
#include <QMessageBox>

namespace Ui {
class timeRecordDlg;
}

class timeRecordDlg : public QDialog
{
    Q_OBJECT

public:
    explicit timeRecordDlg(QWidget *parent = 0);
    ~timeRecordDlg();

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);

private:
    Ui::timeRecordDlg *ui;
};

#endif // TIMERECORDDLG_H
