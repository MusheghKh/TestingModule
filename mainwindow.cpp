#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "processutil.h"
#include "chartshelper.h"

#include <QDebug>
#include <QFileDialog>
#include <QDir>
#include <QProcess>
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ChartsHelper* chartsHelper = new ChartsHelper("some Title Baby");
    chartsHelper->appendSlicePart("first", 17.4);
    chartsHelper->appendPart("seconf", 38.2);
    chartsHelper->appendPart("final", 44.4);

    ui->horizontalLayout11->addWidget(chartsHelper->biuldChart());

    chartsHelper = new ChartsHelper("title2");
    chartsHelper->appendPart("first", 17.4);
    chartsHelper->appendSlicePart("seconf", 38.2);
    chartsHelper->appendPart("final", 44.4);

    ui->horizontalLayout11->addWidget(chartsHelper->biuldChart());


    ProcessUtil::printAllMemeoryInfo();
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

void MainWindow::on_button_3_1_clicked()
{
    ui->edit_3_1->setText(openSelectFileDialog());
}

void MainWindow::on_button_3_2_clicked()
{
    ui->edit_3_2->setText(openSelectFileDialog());
}

void MainWindow::on_button_3_3_clicked()
{
    ui->edit_3_3->setText(openSelectFileDialog());
}

void MainWindow::on_button_4_1_clicked()
{
    ui->edit_4_1->setText(openSelectFileDialog());
}

void MainWindow::on_button_4_2_clicked()
{
    ui->edit_4_2->setText(openSelectFileDialog());
}

void MainWindow::on_button_4_3_clicked()
{
    ui->edit_4_3->setText(openSelectFileDialog());
}

void MainWindow::on_button_4_4_clicked()
{
    ui->edit_4_4->setText(openSelectFileDialog());
}

QString MainWindow::openSelectFileDialog()
{
    return QFileDialog::getOpenFileName(
                this,
                "Select .exe file",
                QDir::homePath(),
                "Executable (*.exe)"
                );
}

void MainWindow::on_startButton_1_clicked()
{
    QProcess* process = new QProcess();
    process->start(ui->edit_1_1->text());

//    process->waitForStarted();
//    qDebug() << QString("Start");
    qint64 start = QDateTime::currentMSecsSinceEpoch();
    qDebug() << start;

    while(true)
    {
        if(process->state() == QProcess::Running)
        {
            qDebug() << QString("Running");
            qDebug() << QDateTime::currentMSecsSinceEpoch() - start;
            break;
        }
    }

    qDebug() << process->program();
    qDebug() << process->processId();

    process->waitForFinished();
    qDebug() << process->exitCode();
}
