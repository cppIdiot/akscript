#ifndef HELPDLG_H
#define HELPDLG_H

#include <QDialog>

namespace Ui {
class helpDlg;
}

class helpDlg : public QDialog
{
    Q_OBJECT

public:
    explicit helpDlg(QWidget *parent = 0);
    ~helpDlg();

private:
    Ui::helpDlg *ui;
};

#endif // HELPDLG_H
