#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QComboBox>
#include <QSpinBox>
#include <QLineEdit>
#include <QPushButton>
#include <keithley.h>
#include <graph.h>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

private slots:
    //void transaction();
    void showResponse(const QString &s);
    //void processError(const QString &s);
    //void processTimeout(const QString &s);
    void addMeasurement(double v, double c);
    void updateProgressBar(int value);

    void on_pushButton_send_command_clicked();

    void on_pushButton_start_run_clicked();

    void on_pushButton_clear_plot_clicked();

    void on_pushButton__stop_run_clicked();

    void on_pushButton_reload_clicked();

private:
    void setControlsEnabled(bool enable);
    QString setFileName();
    QFile* file;
    QTextStream* stream;

private:

    Keithley* keithley;
    graph* gr;

};

#endif // MAINWINDOW_H
