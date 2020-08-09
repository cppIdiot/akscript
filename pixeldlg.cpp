#include "pixeldlg.h"
#include "ui_pixeldlg.h"
#include <QMessageBox>
#include <QPushButton>

#include "mainwindow.h"

inline QString delSpace(QString str);

pixelDlg::pixelDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::pixelDlg)
{
    ui->setupUi(this);
}

pixelDlg::~pixelDlg()
{
    delete ui;
}

void pixelDlg::on_buttonBox_clicked(QAbstractButton *button)
{//少一步判断输入数据的正确性
    bool ok[8];
    int flag = 1;
    delSpace(ui->start_x->text()).toInt(&ok[0]);
    delSpace(ui->start_y->text()).toInt(&ok[1]);
    delSpace(ui->go_x->text()).toInt(&ok[2]);
    delSpace(ui->go_y->text()).toInt(&ok[3]);
    delSpace(ui->end_x->text()).toInt(&ok[4]);
    delSpace(ui->end_y->text()).toInt(&ok[5]);
    delSpace(ui->add_x->text()).toInt(&ok[6]);
    delSpace(ui->add_y->text()).toInt(&ok[7]);
    for(int i = 0;i < 8;i++){
            if(ok[i] == false){
                flag = 0;
            }
        }
    if(flag == 0 || delSpace(ui->start_x->text()) == "" ||
            delSpace(ui->start_y->text()) == "" ||
            delSpace(ui->go_x->text()) == "" ||
            delSpace(ui->go_y->text()) == "" ||
            delSpace(ui->end_x->text()) == "" ||
            delSpace(ui->end_y->text()) == "" ||
            delSpace(ui->add_x->text()) == "" ||
            delSpace(ui->add_y->text()) == ""){
        QMessageBox::critical(this, "数据异常", "请检查数据是否填写完整或者数据类型正确");
        return ;
    }
    QString str;
    str += delSpace(ui->start_x->text());
    str += " ";
    str += delSpace(ui->start_y->text());
    str += " ";
    str += delSpace(ui->go_x->text());
    str += " ";
    str += delSpace(ui->go_y->text());
    str += " ";
    str += delSpace(ui->end_x->text());
    str += " ";
    str += delSpace(ui->end_y->text());
    str += " ";
    str += delSpace(ui->add_x->text());
    str += " ";
    str += delSpace(ui->add_y->text());

    if(ui->buttonBox->button(QDialogButtonBox::Ok) == button)
    {
        QMessageBox::information(NULL, "操作成功", "像素点更改成功");
        emit pixelSend(str);
        this->close();
    }

    else if(ui->buttonBox->button(QDialogButtonBox::Cancel) == button)
    {
        this->close();
    }
}

inline QString delSpace(QString str){
    str.remove(QRegularExpression("[ ]"));
            return str;
}
