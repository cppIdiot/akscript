#include "windlg.h"
#include "ui_windlg.h"

winDlg::winDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::winDlg)
{
    ui->setupUi(this);
}

winDlg::~winDlg()
{
    delete ui;
}

void winDlg::on_buttonBox_clicked(QAbstractButton *button)
{
    if(ui->buttonBox->button(QDialogButtonBox::Ok) == button)
    {
        QMessageBox::information(this, "更改成功", "您已成功更改窗口名称");
        emit winSend(ui->winText->text());
        this->close();
    }

    else if(ui->buttonBox->button(QDialogButtonBox::Cancel) == button)
    {
        this->close();
    }
}
