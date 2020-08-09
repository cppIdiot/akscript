#include "helpdlg.h"
#include "ui_helpdlg.h"

helpDlg::helpDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::helpDlg)
{
    ui->setupUi(this);
}

helpDlg::~helpDlg()
{
    delete ui;
}
