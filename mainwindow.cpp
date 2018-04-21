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
}

MainWindow::~MainWindow()
{
    delete timer;
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
    QProcess process;
    QString path = ui->edit_1_1->text();
    qDebug() << path;
    process.setProgram(path);
    process.start();
    process.waitForStarted();

    pid = process.processId();
    showProcessData();

    process.waitForFinished(-1);
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
    if(timer != 0){
        timer->stop();
        delete timer;
        timer = 0;
    }
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(showProcessData()));
    timer->start(15000);

    clearWidgets(ui->horizontalLayout11);
    QMap<QString, QString> data = ProcessUtil::getProcessData(pid);

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
    ui->horizontalLayout11->addWidget(chartsHelper.biuldChart());

    QTime processCPU = QTime::fromString(data.value("CPUTime"));
    int processCPUTime = processCPU.hour() * 60 + processCPU.minute();
    processCPUTime = processCPUTime * 60 + processCPU.second();

    int idleCPUTime = ProcessUtil::getIdleCPUTime();

    appPart = (processCPUTime / idleCPUTime) * 100;
    systemPart = 100 - appPart;
    chartsHelper.reset("CPU Load");
    chartsHelper.appendSlicePart(QString("%1%").arg(appPart), appPart);
    chartsHelper.appendPart(QString("%1%").arg(systemPart), systemPart);
    ui->horizontalLayout11->addWidget(chartsHelper.biuldChart());
}
