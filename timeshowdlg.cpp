#include "timeshowdlg.h"
#include "ui_timeshowdlg.h"

timeShowDlg::timeShowDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::timeShowDlg)
{
    ui->setupUi(this);
    ui->timeData->setText("");
    QString path = QCoreApplication::applicationDirPath();
    QSettings *configInWrite = new QSettings(path + "/levelTime.ini", QSettings::IniFormat);
    configInWrite->beginGroup("LEVELCONFIG");
    QStringList result = configInWrite->allKeys();
    foreach (QString key, result) {
        ui->timeData->append(key + " : " + configInWrite->value(key).toString() + "(s)\n");
    }
}

timeShowDlg::~timeShowDlg()
{
    delete ui;
}

void timeShowDlg::on_pushButton_clicked()
{
    ui->timeData->setText("");
    QString path = QCoreApplication::applicationDirPath();
    QSettings *configInWrite = new QSettings(path + "/levelTime.ini", QSettings::IniFormat);
    configInWrite->beginGroup("LEVELCONFIG");
    QStringList result = configInWrite->allKeys();
    foreach (QString key, result) {
        ui->timeData->append(key + " : " + configInWrite->value(key).toString() + "(s)\n");
    }
}

void timeShowDlg::on_pushButton_2_clicked()
{
    QString path = QCoreApplication::applicationDirPath();
    QSettings *configInWrite = new QSettings(path + "/levelTime.ini", QSettings::IniFormat);
    configInWrite->beginGroup("LEVELCONFIG");
        if(configInWrite->contains(ui->delKey->text())){
            configInWrite->remove(ui->delKey->text());
            QMessageBox::information(this, "删除成功", "已找到所要删除的关卡，请按刷新按钮");
            ui->delKey->setText("");
            this->exec();
        }
        else{
            QMessageBox::information(this, "删除失败", "未找到所要删除的关卡");
            this->exec();
        }
}
