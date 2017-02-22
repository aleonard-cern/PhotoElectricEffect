#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSerialPortInfo>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->progressBar->setValue(0);

    const auto infos = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info : infos)
        ui->comboBox_serial_ports->addItem(info.portName());

    keithley = new Keithley(this);
    gr = new graph(ui->qcp_gr, "Current vs. Tension", "Tension (V)", "Current (µA)");
    //gr->adjustPlot(-1, 1);

    connect(keithley, &Keithley::measurement, this, &MainWindow::addMeasurement);
    connect(keithley, &Keithley::updateProgressBar, this, &MainWindow::updateProgressBar);
    connect(keithley, &Keithley::rawAnswer, this, &MainWindow::showResponse);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addMeasurement(double v, double c)
{
    gr->addPoint(v, c*1e6);
}


void MainWindow::showResponse(const QString &s)
{
    //ui->textEdit->setText(s);
    ui->textEdit->append(s);
}
/*
void MainWindow::transaction()
{

}
void MainWindow::processError(const QString &s)
{

}

void MainWindow::processTimeout(const QString &s)
{

}
*/

void MainWindow::updateProgressBar(int value)
{
    ui->progressBar->setValue(value);
}

void MainWindow::on_pushButton_send_command_clicked()
{
    QString portName = ui->comboBox_serial_ports->currentText();
    QString command = ui->lineEdit_command->text();
    if (portName == "" || command == "") {
        ui->textEdit->setText("Invalid port name or command");
        return;
    }

    keithley->processCommand(portName, command);
}

void MainWindow::on_pushButton_start_run_clicked()
{
    QString portName = ui->comboBox_serial_ports->currentText();
    double v_from = ui->doubleSpinBox_v_from->value();
    double v_to = ui->doubleSpinBox_v_to->value();
    double v_by = ui->doubleSpinBox_v_by->value();

    if (portName == "" || v_from >= v_to) {
        ui->textEdit->setText("Invalid port name or run settings");
        return;
    }

    keithley->startRun(portName, v_from, v_to, v_by);
}

void MainWindow::on_pushButton_clear_plot_clicked()
{
    gr->clear();
}

void MainWindow::on_pushButton__stop_run_clicked()
{
    keithley->stopRun();
}
