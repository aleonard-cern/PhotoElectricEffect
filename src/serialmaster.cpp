#include "serialmaster.h"

#include <QtSerialPort/QSerialPort>
#include <QTime>
#include <QDebug>

QT_USE_NAMESPACE

SerialMaster::SerialMaster(QObject *parent)
    : QThread(parent), waitTimeout(0), delay(200), quit(false)
{
}

SerialMaster::~SerialMaster()
{
    mutex.lock();
    quit = true;
    cond.wakeOne();
    mutex.unlock();
    wait();
}

void SerialMaster::transaction(const QString &portName, int waitTimeout, int delay, const QString &request)
{
    QMutexLocker locker(&mutex);
    this->portName = portName;
    this->waitTimeout = waitTimeout;
    this->request = request;
    this->delay = delay;
    //! [3]
    if (!isRunning())
        start();
    else
        cond.wakeOne();
}

void SerialMaster::run()
{
    bool currentPortNameChanged = false;

    mutex.lock();

    QString currentPortName;
    if (currentPortName != portName) {
        currentPortName = portName;
        currentPortNameChanged = true;
    }

    int currentWaitTimeout = waitTimeout;
    QString currentRequest = request;
    int currentDelay = delay;
    mutex.unlock();

    QSerialPort serial;

    while (!quit) {
        if (currentPortNameChanged) {
            serial.close();
            serial.setPortName(currentPortName);
            serial.setBaudRate(QSerialPort::Baud9600);
            serial.setDataBits(QSerialPort::Data8);
            serial.setParity(QSerialPort::NoParity);
            serial.setStopBits(QSerialPort::OneStop);

            if (!serial.open(QIODevice::ReadWrite)) {
                emit error(tr("Can't open %1, error code %2")
                           .arg(portName).arg(serial.error()));
                return;
            }

        }
        // empty buffer for good measure
        serial.readAll();

        // write request
        currentRequest = currentRequest.trimmed();

        if (currentRequest != "") {

            QByteArray requestData = (currentRequest + "\n").toLocal8Bit();
            serial.write(requestData);
            if (currentRequest.endsWith("?")) {
                if (serial.waitForBytesWritten(waitTimeout)) {
                    QThread::msleep(currentDelay);
                    // read response
                    if (serial.waitForReadyRead(currentWaitTimeout)) {
                        QByteArray responseData = serial.readAll();
                        while (serial.waitForReadyRead(100))
                            responseData += serial.readAll();

                        QString response(responseData);

                        emit this->response(response);
                    }
                    else {
                        emit timeout(tr("Wait read response timeout %1")
                                     .arg(QTime::currentTime().toString()));
                    }
                }
                else {
                    emit timeout(tr("Wait write request timeout %1")
                                 .arg(QTime::currentTime().toString()));
                }
            }
            else {
                if (serial.waitForBytesWritten(1000)) {
                    QThread::msleep(currentDelay);
                    emit this->response("\n\n");
                }
                else {
                    emit timeout(tr("Wait write request timeout %1")
                                 .arg(QTime::currentTime().toString()));
                }
            }
        }
        mutex.lock();
        cond.wait(&mutex);
        if (currentPortName != portName) {
            currentPortName = portName;
            currentPortNameChanged = true;
        } else {
            currentPortNameChanged = false;
        }
        currentWaitTimeout = waitTimeout;
        currentRequest = request;
        currentDelay = delay;
        mutex.unlock();
    }

}
