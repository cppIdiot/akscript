#include "aboutmedlg.h"
#include "ui_aboutmedlg.h"

aboutmeDlg::aboutmeDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::aboutmeDlg)
{
    ui->setupUi(this);
}

aboutmeDlg::~aboutmeDlg()
{
    delete ui;
}
