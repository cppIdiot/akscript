#ifndef TIMERECORDDLG_H
#define TIMERECORDDLG_H

#include <QDialog>
#include <QAbstractButton>
#include <QPushButton>
#include <QSettings>
#include <QMessageBox>
#include <QButtonGroup>
#include <QTimer>

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

    void updateTime();

    void on_startr_clicked();

    void on_endr_clicked();

private:
    Ui::timeRecordDlg *ui;

    QButtonGroup *ButtonG = new QButtonGroup(this);

    QTimer* timer1;

    int step;

    bool isStart;

signals:

    void sendAddInfo();     //给主窗口发送添加信息时候的更新信号
};

#endif // TIMERECORDDLG_H
