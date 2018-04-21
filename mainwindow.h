#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QProcess>
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_tabWidget_currentChanged(int index);

    void on_button_1_1_clicked();

    void on_button_2_1_clicked();

    void on_button_2_2_clicked();

    void on_startButton_1_clicked();

    void showProcessData();

    void showProcessData2();

    void on_pushButton_clicked();

    void on_startButton_2_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;

    QString openSelectFileDialog();

    QString ram;

    QProcess* process = nullptr;
    QProcess* process1 = nullptr;
    QProcess* process2 = nullptr;
};

#endif // MAINWINDOW_H
