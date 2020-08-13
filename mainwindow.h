#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <windows.h>
#include <QSettings>
#include <QFileInfo>
#include "helpdlg.h"
#include "aboutmedlg.h"
#include "pixeldlg.h"
#include "updateinfo.h"
#include "sleepdlg.h"
#include "windlg.h"
#include "timerecorddlg.h"
#include "timeshowdlg.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    int cSleep = 3;

    LPCWSTR handle = L"夜神模拟器";

    //TODO: 点击开始像素点位置
    int select_start_x = 1615;
    int select_start_y = 902;

    //TODO: 开始行动像素点位置
    int select_go_x = 1538;
    int select_go_y = 623;

    //TODO: 作战结束像素点位置(也可以用作升级时像素点位置)
    int select_end_x = 1538;
    int select_end_y = 623;

    //TODO: 补充源石像素点位置
    int select_add_x = 1526;
    int select_add_y = 826;

private slots:

    void on_Exit_clicked(bool checked);

    void on_Exit_released();

    void on_reset_clicked(bool checked);

    void on_start_clicked();

    void clickHere(int x, int y);

    bool findprog();

    void clickLap(int sign, bool MO);

    void start();

    long int divTime(long int time1);

    void on_pixelButton_clicked();

    void on_cSleepButton_clicked();

    void on_windowButton_clicked();

    void on_LevelTimeRecord_clicked();

    void on_levelTimeShow_clicked();

    void on_helpButton_clicked();

    void on_aboutButton_clicked();

    void on_input_clicked();

    void on_output_clicked();

    void pixelRecv(QString data);   //接收函数

    void sleepRecv(QString data);   //接收函数

    void winRecv(QString data);     //接收函数

    void on_debugbutt_clicked();

    void on_updateinfo_clicked();

    void recvDelInfo();     //接收来自显示作战详情窗口的信号用来刷新下拉选框

    void recvAddInfo();     //接受来自记录作战详情子窗口的信号来刷新下拉选框

private:
    Ui::MainWindow *ui;                 //  主界面指针

    helpDlg *hd = new helpDlg(this);    //帮助子界面指针

    aboutmeDlg *abd = new aboutmeDlg(this); //关于我子界面指针

    pixelDlg *pd = new pixelDlg(this);      //更改像素位置界面指针

    updateInfo *ud = new updateInfo(this);  //测试版本更新子界面

    sleepDlg *sd = new sleepDlg(this);      //调整触发鼠标事件时间间隔子界面

    winDlg *wd = new winDlg(this);          //更改窗口名称子界面

    timeRecordDlg *trd = new timeRecordDlg(this);//记录关卡时间信息子界面

    timeShowDlg *tsd = new timeShowDlg(this);   //显示有记录的关卡信息子界面\

    int levelCostTime;

    int levelCostHeal;

    int Ismo;

};

#endif // MAINWINDOW_H
