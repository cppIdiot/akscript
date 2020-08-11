#include "timerecorddlg.h"
#include "ui_timerecorddlg.h"

timeRecordDlg::timeRecordDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::timeRecordDlg)
{
    ui->setupUi(this);
    ButtonG->addButton(ui->noButton, 0);
    ButtonG->addButton(ui->yesButton, 1);
    timer1 = new QTimer;
    step = 0;
    isStart = false;
    ui->endr->setEnabled(false);
    connect(timer1, SIGNAL(timeout()), this, SLOT(updateTime()));

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
    QString name = ui->levelName->text().remove(QRegularExpression("[ ]")).toUpper();
    QString ctime = ui->costTime->text().remove(QRegularExpression("[ ]"));
    QString cHeal = ui->costHeal->text().remove(QRegularExpression("[ ]"));
    bool ok1, ok2;
    ctime.toInt(&ok1);
    cHeal.toInt(&ok2);
    if(!ok1 || !ok2){
        QMessageBox::critical(this, "数据异常", "没有记录数据, 请检查字段输入的值是否正确");
        return ;
    }
    if(ui->buttonBox->button(QDialogButtonBox::Ok) == button)
    {
        configInWrite->beginGroup(name);
        configInWrite->setValue("levelCostTime", ctime.toInt() + 5);
        configInWrite->setValue("costHeal", cHeal.toInt());
        switch(ButtonG->checkedId()){
            case 0:
                configInWrite->setValue("ISMO", 0);break;
            case 1:
                configInWrite->setValue("ISMO", 1);break;
        }
        configInWrite->endGroup();
        QMessageBox::information(this, "记录成功", "信息已经成功记录到: " + path + "/levelTime.ini");
        //delete configInWrite;

        emit sendAddInfo();
        this->exec();
    }

    else if(ui->buttonBox->button(QDialogButtonBox::Cancel) == button)
    {
        this->close();
    }
}

void timeRecordDlg::updateTime(){
    step++;
    ui->REtime->setText(QString::number(step));
}

void timeRecordDlg::on_startr_clicked()
{
    if(!isStart){
        timer1->start(1000);
        ui->startr->setDisabled(true);
        ui->endr->setEnabled(true);
    }
    isStart = !isStart;
}

void timeRecordDlg::on_endr_clicked()
{
    ui->endr->setDisabled(true);
    ui->startr->setEnabled(true);
    timer1->stop();
    ui->costTime->setText(QString::number(step));
    step = 0;
    ui->REtime->setText("计时处");
    isStart = false;
}
