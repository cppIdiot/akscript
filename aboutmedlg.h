#ifndef ABOUTMEDLG_H
#define ABOUTMEDLG_H

#include <QDialog>

namespace Ui {
class aboutmeDlg;
}

class aboutmeDlg : public QDialog
{
    Q_OBJECT

public:
    explicit aboutmeDlg(QWidget *parent = 0);
    ~aboutmeDlg();

private:
    Ui::aboutmeDlg *ui;
};

#endif // ABOUTMEDLG_H
