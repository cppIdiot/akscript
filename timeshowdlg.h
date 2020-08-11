#ifndef TIMESHOWDLG_H
#define TIMESHOWDLG_H

#include <QDialog>
#include <QSettings>
#include <QMessageBox>
#include <QTableView>
#include <QHeaderView>
#include <QStandardItemModel>

#include "timerecorddlg.h"

namespace Ui {
class timeShowDlg;
}

class timeShowDlg : public QDialog
{
    Q_OBJECT

public:
    explicit timeShowDlg(QWidget *parent = 0);
    ~timeShowDlg();

private slots:
    void on_delButton_clicked();

    void on_flushT_clicked();

signals:
    void sendDelInfo();     //当删除操作完成时给主窗口发送一个信号

private:
    Ui::timeShowDlg *ui;

};

#endif // TIMESHOWDLG_H
