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

    void showProcessData(qint64 processId);

private:
    Ui::MainWindow *ui;

    QString openSelectFileDialog();

    QString ram;
};

#endif // MAINWINDOW_H
