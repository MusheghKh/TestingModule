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

    void on_button_3_1_clicked();

    void on_button_3_2_clicked();

    void on_button_3_3_clicked();

    void on_button_4_1_clicked();

    void on_button_4_2_clicked();

    void on_button_4_3_clicked();

    void on_button_4_4_clicked();

    void on_startButton_1_clicked();

private:
    Ui::MainWindow *ui;

    QString openSelectFileDialog();
};

#endif // MAINWINDOW_H
