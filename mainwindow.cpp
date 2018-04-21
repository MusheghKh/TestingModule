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

    ChartsHelper chartsHelper = ChartsHelper("title2");
    chartsHelper.appendPart("first", 17.4);
    chartsHelper.appendSlicePart("seconf", 38.2);
    chartsHelper.appendPart("final", 44.4);
    ui->horizontalLayout11->addWidget(chartsHelper.biuldChart());

    ram = ProcessUtil::getSystemRam();
}

MainWindow::~MainWindow()
{
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

    showProcessData(process.processId());
}

void MainWindow::showProcessData(qint64 processId){
    QMap<QString, QString> data = ProcessUtil::getProcessData(processId);

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

}
