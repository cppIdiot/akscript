#ifndef PIXELDLG_H
#define PIXELDLG_H

#include <QDialog>
#include <QAbstractButton>

namespace Ui {
class pixelDlg;
}

class pixelDlg : public QDialog
{
    Q_OBJECT

public:
    explicit pixelDlg(QWidget *parent = 0);
    ~pixelDlg();

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);

signals:
    void pixelSend(QString data);

private:
    Ui::pixelDlg *ui;
};

#endif // PIXELDLG_H
