#include "keithley.h"
#include <QDebug>

QT_USE_NAMESPACE

Keithley::Keithley(QWidget *parent)
{
    portName = "/dev/ttyUSB0";
    ser = new SerialMaster();
    //connect(runButton, &QPushButton::clicked, this, &Keithley::transaction);
    connect(ser, &SerialMaster::response, this, &Keithley::response);
    connect(ser, &SerialMaster::error, this, &Keithley::processError);
    connect(ser, &SerialMaster::timeout, this, &Keithley::processTimeout);
}

void Keithley::processCommand(const QString &port, const QString &rawCommand)
{
    portName = port;
    types.clear();
    types.append("RAW_COMMAND");
    commands.clear();
    commands.append(rawCommand);
    commandIter = 0;
    nCommands = commands.size();
    emit this->updateProgressBar(0);
    next();
}

void Keithley::clearCommands()
{
    commands.clear();
    types.clear();
    delays.clear();
    commandIter = 0;
    nCommands = 0;
}

void Keithley::addCommand(const QString &command, const QString &type, const int delay)
{
    commands.append(command);
    types.append(type);
    delays.append(delay);
}

void Keithley::startRun(const QString &port, double v_from, double v_to, double v_by)
{
    portName = port;

    clearCommands();
    addCommand(":OUTP:STATE ON", "", 500);

    for (double v = v_from; (int)(v*1000) <= (int)(v_to*1000); v += v_by)
    {
        addCommand(":SOUR:VOLT " + QString::number(v, 'f', 3));
        addCommand(":FETC?", "CURRENT");
    }
    addCommand(":SOUR:VOLT " + QString::number(0.0, 'f', 3));
    addCommand(":OUTP:STATE OFF", "", 500);

    nCommands = commands.size();
    emit this->updateProgressBar(0);
    next();
}

void Keithley::stopRun()
{
    nCommands = 0;
    clearCommands();
    addCommand(":SOUR:VOLT " + QString::number(0.0, 'f', 3)); // this is not a bug, it is needed twice !
    addCommand(":SOUR:VOLT " + QString::number(0.0, 'f', 3));
    addCommand(":OUTP:STATE OFF", "");
    commandIter = 0;
    nCommands = commands.size();
    next();
}


void Keithley::next()
{
    if (commandIter < commands.size()) {
        qDebug() <<  "next: " << commands[commandIter];
        ser->transaction(portName, 1000, delays[commandIter], commands[commandIter]);
        emit this->updateProgressBar(static_cast<int>(commandIter*100.0/nCommands));
    }
    else {
        emit this->done();
        emit this->updateProgressBar(100);
        commands.clear();
        types.clear();
        commandIter = 0;
    }
}

void Keithley::response(const QString& res)
{
    if (!(res.endsWith("\n\n") || res.endsWith("\r\n"))) {
        commandIter--;
        emit this->rawAnswer("<i style=\"color:red\">Incomplete reading:</i> " + res);
    }
    else {
        if (types[commandIter] == "CURRENT") {
            if ((res.startsWith("+") || res.startsWith("-")) && res.indexOf("NADC") > 0) {
                int index = res.indexOf("NADC");
                QString c = res.left(index);
                QString v = commands[commandIter - 1].right(commands[commandIter-1].size() - 11);

                emit this->measurement(v.toDouble(), c.toDouble());
            }
            else {
                commandIter--;
            }
        }
        else if (types[commandIter] == "RAW_COMMAND") {
            if (res.endsWith("\n\n") || res.endsWith("\r\n")) {
                emit this->rawAnswer(res);
            }
            else {
                commandIter--;
            }
        }
    }
    commandIter++;

    next();
}

void Keithley::processError(const QString &s)
{
    qDebug() << "Process Error: " << s;
}

void Keithley::processTimeout(const QString &s)
{
    qDebug() << "Process Timeout: " << s;
}
