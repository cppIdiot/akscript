#ifndef UPDATEINFO_H
#define UPDATEINFO_H

#include <QDialog>

namespace Ui {
class updateInfo;
}

class updateInfo : public QDialog
{
    Q_OBJECT

public:
    explicit updateInfo(QWidget *parent = 0);
    ~updateInfo();

private:
    Ui::updateInfo *ui;
};

#endif // UPDATEINFO_H
