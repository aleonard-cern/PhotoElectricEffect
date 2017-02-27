#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSerialPortInfo>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    
    ui->progressBar->setValue(0);

    setFileName();
    on_pushButton_reload_clicked();

    keithley = new Keithley(this);
    gr = new graph(ui->qcp_gr, "Current vs. Voltage", "Voltage (V)", "Current (µA)");

    connect(keithley, &Keithley::measurement, this, &MainWindow::addMeasurement);
    connect(keithley, &Keithley::updateProgressBar, this, &MainWindow::updateProgressBar);
    connect(keithley, &Keithley::rawAnswer, this, &MainWindow::showResponse);

}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::setFileName()
{
    //get current time
    QDateTime time = QDateTime::currentDateTime();
    QString timeString = time.toString();
    qDebug() << timeString.replace(":", "_");
    qDebug() << timeString.replace(" ", "_");

    QString fileNameTmp = QStandardPaths::locate(QStandardPaths::DocumentsLocation, QString(), QStandardPaths::LocateDirectory);
    fileNameTmp += "Data_";
    fileNameTmp += timeString;
    fileNameTmp += ".txt";
    qDebug() << "This is the location: ";
    qDebug() << fileNameTmp;
    ui->lineEdit_fileName->setText(fileNameTmp);
    return fileNameTmp;
}

void MainWindow::addMeasurement(double v, double c)
{
    gr->addPoint(v, c*1e6);
    (*stream) << QString::number(v) << " " << QString::number(c*1e6) << "\n";

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
    if (value == 100 && stream != nullptr) {
        delete stream;
        file->close();
        delete file;
    }
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
    QString fileName = setFileName();
    file = new QFile(fileName);

    if (!file->open(QIODevice::ReadWrite | QIODevice::Append)) {
        qDebug() << "Problem opening or creating the file:";
        qDebug() << fileName;
        file->close();
        delete file;
        return;
    }
    stream = new QTextStream(file);


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

void MainWindow::on_pushButton_reload_clicked()
{
    ui->comboBox_serial_ports->clear();
    const auto infos = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info : infos)
        ui->comboBox_serial_ports->addItem(info.portName());
}
