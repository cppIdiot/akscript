#include "timerecorddlg.h"
#include "ui_timerecorddlg.h"

timeRecordDlg::timeRecordDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::timeRecordDlg)
{
    ui->setupUi(this);

}

timeRecordDlg::~timeRecordDlg()
{
    delete ui;
}

void timeRecordDlg::on_buttonBox_clicked(QAbstractButton *button)
{
    QString path = QCoreApplication::applicationDirPath();
    QSettings *configInWrite = new QSettings(path + "/levelTime.ini", QSettings::IniFormat);

    //去除空格
    QString name = ui->levelName->text().remove(QRegularExpression("[ ]"));
    QString ctime = ui->costTime->text().remove(QRegularExpression("[ ]"));
    bool ok;
    ctime.toInt(&ok);
    if(!ok){
        QMessageBox::critical(this, "数据异常", "请检查字段输入的值是否正确");
        return ;
    }
    if(ui->buttonBox->button(QDialogButtonBox::Ok) == button)
    {
        configInWrite->beginGroup("LEVELCONFIG");
        configInWrite->setValue(name, ctime.toInt());
        configInWrite->endGroup();
        QMessageBox::information(this, "记录成功", "信息已经成功记录到: " + path + "/levelTime.ini");
        //delete configInWrite;
        this->exec();
    }

    else if(ui->buttonBox->button(QDialogButtonBox::Cancel) == button)
    {
        this->close();
    }
}
