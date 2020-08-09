#include "updateinfo.h"
#include "ui_updateinfo.h"

updateInfo::updateInfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::updateInfo)
{
    ui->setupUi(this);
}

updateInfo::~updateInfo()
{
    delete ui;
}
