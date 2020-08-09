#ifndef TIMESHOWDLG_H
#define TIMESHOWDLG_H

#include <QDialog>
#include <QSettings>
#include <QMessageBox>

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
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::timeShowDlg *ui;
};

#endif // TIMESHOWDLG_H
