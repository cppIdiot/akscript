#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <time.h>
#include <windows.h>
#include <QMessageBox>
#include <QTest>

typedef long int LONG;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
                                          ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->debugtext->hide();

    connect(trd, SIGNAL(sendAddInfo()), this, SLOT(recvAddInfo()));
    connect(tsd, SIGNAL(sendDelInfo()), this, SLOT(recvDelInfo()));

    QString path = QCoreApplication::applicationDirPath();
    QSettings *configInWrite = new QSettings(path + "/levelTime.ini", QSettings::IniFormat);
    QStringList sectionList = configInWrite->childGroups();
    foreach (QString var, sectionList) {
        ui->selectLevevl->addItem(var);
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Exit_clicked(bool checked)
{
    this->close();
    delete ui;
}

void MainWindow::on_Exit_released()
{
    this->close();
    delete ui;
}

void MainWindow::on_reset_clicked(bool checked)
{

    //!该函数需要更改为点击重置之后从文件中读取数据进行填充，包括像素点，窗口名称等字段!

    //全部转为初始设置
    ui->User_60_label->setText("0");
    ui->User_100_label->setText("0");
    ui->User_exp_label->setText("99999");
    ui->User_maxheal_label->setText("131");
    ui->User_stone_label->setText("0");
    ui->User_leftheal_label->setText(ui->User_maxheal_label->text());
}

void MainWindow::on_start_clicked()
{
    time_t timeStart = time(0);
    QString Start = "脚本开始执行，程序于 " + QString::number(timeStart) +" (时间戳)开始任务。";
    ui->result_textarea->setTextColor(Qt::red);
    ui->result_textarea->setText(Start);

    if (findprog())
    {
        start();
        QMessageBox::critical(0,
                              "正常退出", "程序顺利地完成了您所分配的任务。",
                              QMessageBox::Ok | QMessageBox::Default,
                              QMessageBox::Cancel | QMessageBox::Escape, 0);
    }

    time_t timeEnd = time(0);
    QString end = "脚本执行完毕，程序于 " + QString::number(timeEnd) +" (时间戳)完成任务。";
    ui->result_textarea->setTextColor(Qt::red);
    ui->result_textarea->append(end);

}

void MainWindow::clickHere(int x, int y)
{
    QTest::qWait(cSleep * 1000);
    SetCursorPos(x, y);
    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
}

void MainWindow::clickLap(int sign, bool MO)
{
    QTest::qWait(6 * 1000);
    clickHere(select_start_x, select_start_y);
    if (sign == 1)
    {
        clickHere(select_add_x, select_add_y);
        clickHere(select_start_x, select_start_y);
    }
    clickHere(select_go_x, select_go_y);
    QTest::qWait(this->levelCostTime * 1000);
    if (MO == true)
    {
        clickHere(select_start_x, select_start_y);
        QTest::qWait(6000);
    }
    clickHere(select_end_x, select_end_y);
}

void MainWindow::start()
{
    QString path = QCoreApplication::applicationDirPath();
    QSettings *configInWrite = new QSettings(path + "/levelTime.ini", QSettings::IniFormat);

    configInWrite->beginGroup(ui->selectLevevl->itemText(ui->selectLevevl->currentIndex()));
    this->levelCostTime = configInWrite->value("levelCostTime").toInt();
    this->levelCostHeal = configInWrite->value("costHeal").toInt();
    this->Ismo = configInWrite->value("ISMO").toBool();

    int Ttime = 0;
    int loop = 1;
    bool ok[8];

    int _health = ui->User_leftheal_label->text().toInt(&ok[0]);     //用户当前剩余理智
    int _level_cost = this->levelCostHeal;                           //用户当前关卡消耗理智
    int _stone = ui->User_stone_label->text().toInt(&ok[1]);         //用户当前剩余源石
    int MAXHEAL = ui->User_maxheal_label->text().toInt(&ok[2]);      //用户当前等级最大理智
    int add_60 = ui->User_60_label->text().toInt(&ok[3]);            //用户当前剩余60理智合剂数目
    int add_100 = ui->User_100_label->text().toInt(&ok[4]);          //用户当前剩余100理智合剂数目
    int _exp = ui->User_exp_label->text().toInt(&ok[5]);             //用户当前距离升级相差经验数
    int ISMO = this->Ismo;                                           //用户当前关卡是否为剿灭

    for(int i = 0;i < 6;i++){
        if(ok[i] == false){
            QMessageBox::critical(0,
                                  "数据异常！", "请检查你输入数据的正确性。",
                                  QMessageBox::Ok | QMessageBox::Default,
                                  QMessageBox::Cancel | QMessageBox::Escape, 0);
            return ;
        }
    }

    while (1)
    {
        time_t time1 = time(0);
        _health -= _level_cost;
        if (_health >= 0)
        { //判断理智是否扣完
            clickLap(0, ISMO);
            Ttime += divTime(time1);
        }
        else
        { //扣到负数的话，代表已经出现了需要消耗源石的鼠标时间集合情况
            if (add_60 != 0 || add_100 != 0)
            { //先判断是否需要理智合剂的情况
                if (add_60 != 0)
                {
                    add_60--;
                    _health += 60;
                    clickLap(1, ISMO);
                }
                else
                {
                    add_100--;
                    _health += 100;
                    clickLap(1, ISMO);
                }
                //定义第二个时间戳变量进行运算
                Ttime += divTime(time1);
            }
            else
            { //再判断是否需要源石来恢复体力
                if (_stone == 0 && add_60 == 0 && add_100 == 0)
                {
                    break;
                }
                //原石、理智样剂用尽，跳出循环
                _health += MAXHEAL; //!需要优化，根据等级加减对应的理智
                clickLap(1, ISMO);
                _stone -= 1;
                Ttime = 0;
            }
        }
        if (Ttime >= 360)
        { //如果过去了6分钟，理智会自然恢复一点
            _health++;
            Ttime -= 360;
        }
        if (_health >= MAXHEAL)
        { //如果刷一次本之后体力还是在满体力之上，将恢复时间设置为0
            Ttime = 0;
        }
        QString ptr = "第" + QString::number(loop) + "次刷本，本次刷完之后：\n" +
                      "体力剩余: " + QString::number(_health) + "\n" +
                      "源石剩余：" + QString::number(_stone) + "\n" +
                      "60理智合剂剩余：" + QString::number(add_60) + "\n" +
                      "100理智合剂剩余：" + QString::number(add_100) + "\n" + \
                      "恢复理智时间(6:00)：" + QString::number(Ttime) + "(sec)\n";
        ui->result_textarea->setTextColor(Qt::green);
        ui->result_textarea->append(ptr);
        loop++;
    }

}

bool MainWindow::findprog()
{
    HWND id = FindWindow(NULL, handle);
    if (id == 0)
    {
        QMessageBox::critical(0,
                              "窗体未找到!", "请检查是否填写了正确的窗体名称！",
                              QMessageBox::Ok | QMessageBox::Default,
                              QMessageBox::Cancel | QMessageBox::Escape, 0);
        return false;
    }
    else
    {
        //找到窗口,直接开始脚本进程
        EnableWindow(id, true);
        SetForegroundWindow(id);
        ShowWindow(id, SW_SHOWNORMAL);
        return true;
    }
}

long int MainWindow::divTime(long int time1)
{
    time_t time2 = time(0);
    return time2 - time1;
}

inline bool isUnsignedInt(QString str){
    for(int i = 0;i < str.length();i++){
        if(str[i] < '0' || str[i] > '9'){
            return false;
        }
    }
    return true;
}


void MainWindow::on_pixelButton_clicked()
{
    connect(pd, SIGNAL(pixelSend(QString)), this, SLOT(pixelRecv(QString)));
    pd->show();
}

void MainWindow::on_cSleepButton_clicked()
{
    connect(sd, SIGNAL(sleepSend(QString)), this, SLOT(sleepRecv(QString)));
    sd->show();
}

void MainWindow::on_windowButton_clicked()
{
    connect(wd, SIGNAL(winSend(QString)), this, SLOT(winRecv(QString)));
    wd->show();
}

void MainWindow::on_LevelTimeRecord_clicked()
{
    trd->show();
}

void MainWindow::on_levelTimeShow_clicked()
{
    tsd->show();
}

void MainWindow::on_helpButton_clicked()
{
    hd->open();
}

void MainWindow::on_aboutButton_clicked()
{
    abd->open();
}

void MainWindow::on_input_clicked()
{

}

void MainWindow::on_output_clicked()
{

}

void MainWindow::pixelRecv(QString data){
    QString str[8];
    for(int i = 0;i < 8;i++){
        str[i] = data.section(' ', i, i);
    }
    select_start_x = str[0].toInt();
    select_start_y = str[1].toInt();
    select_go_x = str[2].toInt();
    select_go_y = str[3].toInt();
    select_end_x = str[4].toInt();
    select_end_y = str[5].toInt();
    select_add_x = str[6].toInt();
    select_add_y = str[7].toInt();
}

void MainWindow::on_debugbutt_clicked()
{
    ui->debugtext->show();
    QString debuginform = "当前像素点信息为:\
            \nselect_start_x: " + QString::number(select_start_x) + \
            "\nselect_start_y: " + QString::number(select_start_y) + \
            "\nselect_go_x: " + QString::number(select_go_x) + \
            "\nselect_go_y: " + QString::number(select_go_y) + \
            "\nselect_end_x: " + QString::number(select_end_x) + \
            "\nselect_end_y: " + QString::number(select_end_y) + \
            "\nselect_add_x: " + QString::number(select_add_x) + \
            "\nselect_add_y: " + QString::number(select_add_y) + \
            "\ncSleep: " + QString::number(cSleep) + \
            "\nhandle: " + QString::fromStdWString(handle) + \
            "\n当前工作路径为(exe文件所在路径, ini文件正常情况下也会在这个文件夹内): \n" + QCoreApplication::applicationDirPath();
    ui->debugtext->setText(debuginform);
}

void MainWindow::on_updateinfo_clicked()
{
    ud->show();
}

void MainWindow::sleepRecv(QString data){
    cSleep = data.toInt();
}

void MainWindow::winRecv(QString data){
    handle = reinterpret_cast<LPCWSTR>(data.utf16());
}

void MainWindow::recvAddInfo(){
    ui->selectLevevl->clear();
    QString path = QCoreApplication::applicationDirPath();
    QSettings *configInWrite = new QSettings(path + "/levelTime.ini", QSettings::IniFormat);
    QStringList sectionList = configInWrite->childGroups();
    foreach (QString var, sectionList) {
        ui->selectLevevl->addItem(var);
    }
}

void MainWindow::recvDelInfo(){
    ui->selectLevevl->clear();
    QString path = QCoreApplication::applicationDirPath();
    QSettings *configInWrite = new QSettings(path + "/levelTime.ini", QSettings::IniFormat);
    QStringList sectionList = configInWrite->childGroups();
    foreach (QString var, sectionList) {
        ui->selectLevevl->addItem(var);
    }
}
