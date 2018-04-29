#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "processutil.h"
#include "chartshelper.h"

#include <QDebug>
#include <QFileDialog>
#include <QDir>
#include <QProcess>
#include <QDateTime>
#include <QMap>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ram = ProcessUtil::getSystemRam();

    ui->info->setText(ProcessUtil::getAllTasks());
}

MainWindow::~MainWindow()
{
    delete process;
    delete process1;
    delete process2;
    delete ui;
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    qDebug() << index;
}

void MainWindow::on_button_1_1_clicked()
{
    ui->edit_1_1->setText(openSelectFileDialog());
}

void MainWindow::on_button_2_1_clicked()
{
    ui->edit_2_1->setText(openSelectFileDialog());
}

void MainWindow::on_button_2_2_clicked()
{
    ui->edit_2_2->setText(openSelectFileDialog());
}

QString MainWindow::openSelectFileDialog()
{
    QString result = QFileDialog::getOpenFileName(
                this,
                "Select .exe file",
                QDir::homePath(),
                "Executable (*.exe)"
            );
    return QDir::toNativeSeparators(result);
}

void MainWindow::on_startButton_1_clicked()
{
    delete process;
    process = new QProcess();
    QString path = ui->edit_1_1->text();
    qDebug() << path;
    process->setProgram(path);
    process->start();
    process->waitForStarted();

    showProcessData();

//    process->waitForFinished(-1);
}

void clearWidgets(QLayout * layout) {
   if (! layout)
      return;
   while (auto item = layout->takeAt(0)) {
      delete item->widget();
      clearWidgets(item->layout());
   }
}

void MainWindow::showProcessData(){
    clearWidgets(ui->horizontalLayout_4);
    if(process == nullptr){
        return;
    }
    QMap<QString, QString> data = ProcessUtil::getProcessData(process->processId());

    const QString& memUsage = data.value("MemUsage");
    QString mem = memUsage.left(memUsage.length() - 1).replace(",", "");
    int memory = mem.toInt();

    double appPart = memory / (1024 * ram.toInt());
    if(appPart == 0){
        appPart = 1;
    }
    double systemPart = 100 - appPart;
    ChartsHelper chartsHelper("RAM Usage");
    chartsHelper.appendSlicePart(QString("%1K").arg(memory), appPart);
    chartsHelper.appendPart(QString("%1K").arg(1024 * ram.toInt() - memory), systemPart);
    ui->horizontalLayout_4->addWidget(chartsHelper.biuldChart());

    QString processCPU = data.value("CPUTime");
    int hour = processCPU.left(2).toInt();
    int minute = processCPU.mid(4, 2).toInt();
    int seconds = processCPU.right(2).toInt();
    int processCPUTime = hour * 60 + minute;
    processCPUTime = processCPUTime * 60 + seconds;

    int idleCPUTime = ProcessUtil::getIdleCPUTime();

    appPart = (processCPUTime / idleCPUTime) * 100;
    systemPart = 100 - appPart;
    QDir dir(process->program());

    chartsHelper.reset("CPU Load");
    chartsHelper.appendSlicePart(QString("%1 %2%").arg(dir.dirName(), QString::number(appPart)), appPart);
    chartsHelper.appendPart(QString("%1%").arg(systemPart), systemPart);
    ui->horizontalLayout_4->addWidget(chartsHelper.biuldChart());
}

void MainWindow::showProcessData2(){
    clearWidgets(ui->horizontalLayout_6);
    if(process1 == nullptr || process2 == nullptr){
        return;
    }
    QMap<QString, QString> data1 = ProcessUtil::getProcessData(process1->processId());
    QMap<QString, QString> data2 = ProcessUtil::getProcessData(process2->processId());

    const QString& memUsage = data1.value("MemUsage");
    int memory1 = memUsage.left(memUsage.length() - 1).replace(",", "").toInt();
    const QString& memUsage2 = data2.value("MemUsage");
    int memory2 = memUsage2.left(memUsage2.length() - 1).replace(",", "").toInt();

    double appPart1 = memory1 / (1024 * ram.toInt());
    if(appPart1 == 0){
        appPart1 = 1;
    }
    double appPart2 = memory2 / (1024 * ram.toInt());
    if(appPart2 == 0){
        appPart2 = 1;
    }
    double systemPart = 100 - appPart1 - appPart2;
    QDir dir1(process1->program());
    QDir dir2(process2->program());
    ChartsHelper chartsHelper("RAM Usage");
    chartsHelper.appendSlicePart(QString("%1 %2K").arg(dir1.dirName(), QString::number(memory1)), appPart1);
    chartsHelper.appendSlicePart(QString("%1 %2K").arg(dir2.dirName(), QString::number(memory2)), appPart2);
    chartsHelper.appendPart(QString("%1K").arg(1024 * ram.toInt() - memory1 - memory2), systemPart);
    ui->horizontalLayout_6->addWidget(chartsHelper.biuldChart());

    QString process1CPU = data1.value("CPUTime");
    int hour = process1CPU.left(2).toInt();
    int minute = process1CPU.mid(4, 2).toInt();
    int seconds = process1CPU.right(2).toInt();

    int process1CPUTime = hour * 60 + minute;
    process1CPUTime = process1CPUTime * 60 + seconds;

    QString process2CPU = data2.value("CPUTime");
    hour = process2CPU.left(2).toInt();
    minute = process2CPU.mid(4, 2).toInt();
    seconds = process2CPU.right(2).toInt();

    int process2CPUTime = hour * 60 + minute;
    process2CPUTime = process2CPUTime * 60 + seconds;

    int idleCPUTime = ProcessUtil::getIdleCPUTime();

    appPart1 = (process1CPUTime / idleCPUTime) * 100;
    systemPart = 100 - appPart1 - appPart2;
    chartsHelper.reset("CPU Load");
    chartsHelper.appendSlicePart(QString("%1 %2%").arg(dir1.dirName(), QString::number(appPart1)), appPart1);
    chartsHelper.appendSlicePart(QString("%1 %2%").arg(dir2.dirName(), QString::number(appPart2)), appPart2);
    chartsHelper.appendPart(QString("%1%").arg(systemPart), systemPart);
    ui->horizontalLayout_6->addWidget(chartsHelper.biuldChart());
}

void MainWindow::on_pushButton_clicked()
{
    showProcessData();
}

void MainWindow::on_startButton_2_clicked()
{
    delete process1;
    delete process2;
    process1 = new QProcess();
    process2 = new QProcess();
    QString path1 = ui->edit_2_1->text();
    QString path2 = ui->edit_2_2->text();
    qDebug() << path1;
    qDebug() << path2;
    process1->setProgram(path1);
    process1->start();
    process1->waitForStarted();

    process2->setProgram(path2);
    process2->start();
    process2->waitForStarted();

    showProcessData2();
}

void MainWindow::on_pushButton_2_clicked()
{
    showProcessData2();
}

void MainWindow::on_pushButton_3_clicked()
{
    ui->info->setText(ProcessUtil::getAllTasks());
}

void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    if(arg1.length() < 1){
        ui->info->setText(ProcessUtil::getAllTasks());
        return;
    }
    ui->info->setText(ProcessUtil::getProcessesByName(arg1));
}
