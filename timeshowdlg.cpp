#include "timeshowdlg.h"
#include "ui_timeshowdlg.h"

timeShowDlg::timeShowDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::timeShowDlg)
{
    int col = 0, row = 0;
    ui->setupUi(this);
    QStandardItemModel* model = new QStandardItemModel();
    model->setHorizontalHeaderLabels({"关卡名称", "消耗时间", "消耗理智", "是否为剿灭"});
    ui->REtable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    QString path = QCoreApplication::applicationDirPath();
    QSettings *configInWrite = new QSettings(path + "/levelTime.ini", QSettings::IniFormat);
    QStringList sectionList = configInWrite->childGroups();
    QStringList keyList;

    foreach (QString var, sectionList) {
        configInWrite->beginGroup(var);
        model->setItem(row, col, new QStandardItem(var));
        col++;
        model->setItem(row, col, new QStandardItem(configInWrite->value("levelCostTime").toString()));
        col++;
        model->setItem(row, col, new QStandardItem(configInWrite->value("costHeal").toString()));
        col++;
        model->setItem(row, col, new QStandardItem(configInWrite->value("ISMO").toBool() ? "是":"否"));
        row++;
        col = 0;
        configInWrite->endGroup();
        }
    ui->REtable->setModel(model);
    delete configInWrite;
}

timeShowDlg::~timeShowDlg()
{
    delete ui;
}

void timeShowDlg::on_delButton_clicked()
{
    int flag = 0;
    QString path = QCoreApplication::applicationDirPath();
    QSettings *configInWrite = new QSettings(path + "/levelTime.ini", QSettings::IniFormat);
    QStringList sectionList = configInWrite->childGroups();
    foreach (QString var, sectionList) {
        if(var == ui->delKey->text().remove(QRegularExpression("[ ]")).toUpper()){
            configInWrite->remove("/" + var);
            QMessageBox::information(this, "删除成功", "已找到所要删除的关卡，请按刷新按钮");
            ui->delKey->setText("");
            flag = 1;
            this->exec();
        }
    }
    if(flag == 0){
        QMessageBox::information(this, "删除失败", "未找到所要删除的关卡");
        this->exec();
    }
    delete configInWrite;
    emit sendDelInfo();
}

void timeShowDlg::on_flushT_clicked(){
    int col = 0, row = 0;
    QStandardItemModel* model = new QStandardItemModel();
    model->setHorizontalHeaderLabels({"关卡名称", "消耗时间", "消耗理智", "是否为剿灭"});
    ui->REtable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    QString path = QCoreApplication::applicationDirPath();
    QSettings *configInWrite = new QSettings(path + "/levelTime.ini", QSettings::IniFormat);
    QStringList sectionList = configInWrite->childGroups();
    QStringList keyList;

    foreach (QString var, sectionList) {
        configInWrite->beginGroup(var);
        model->setItem(row, col, new QStandardItem(var));
        col++;
        model->setItem(row, col, new QStandardItem(configInWrite->value("levelCostTime").toString()));
        col++;
        model->setItem(row, col, new QStandardItem(configInWrite->value("costHeal").toString()));
        col++;
        model->setItem(row, col, new QStandardItem(configInWrite->value("ISMO").toBool() ? "是":"否"));
        row++;
        col = 0;
        configInWrite->endGroup();
        }

    ui->REtable->setModel(model);
    delete configInWrite;
}
