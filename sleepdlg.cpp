#include "sleepdlg.h"
#include "ui_sleepdlg.h"

sleepDlg::sleepDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::sleepDlg)
{
    ui->setupUi(this);
}

sleepDlg::~sleepDlg()
{
    delete ui;
}

void sleepDlg::on_buttonBox_clicked(QAbstractButton *button)
{
    bool ok;
    QString str = ui->sleepSec->text().remove(QRegularExpression("[ ]"));
    str.toInt(&ok);
    if(!ok || str == ""){
        QMessageBox::critical(this, "数据异常", "请检查数据类型或者字段是否准确");
        return ;
    }
    if(ui->buttonBox->button(QDialogButtonBox::Ok) == button)
    {
        QMessageBox::information(this, "更改成功", "您已成功更改鼠标事件时间间隔");
        emit sleepSend(str);
        this->close();
    }

    else if(ui->buttonBox->button(QDialogButtonBox::Cancel) == button)
    {
        this->close();
    }
}
