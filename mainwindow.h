#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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

private:
    Ui::MainWindow *ui;

    QString openSelectFileDialog();

    qint64 pid;
    qint64 pid1;
    qint64 pid2;
    QString ram;

    QTimer* timer = 0;
};

#endif // MAINWINDOW_H
