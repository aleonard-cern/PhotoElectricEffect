#ifndef KEITHLEY_H
#define KEITHLEY_H

#include <serialmaster.h>
#include <QVector>
#include <QString>

class Keithley : public QObject
{
    Q_OBJECT

private:
    SerialMaster* ser;
    QVector<QString> commands;
    QVector<QString> types;
    QVector<int> delays;
    int commandIter;
    int nCommands;
    QString portName;
    void clearCommands();
    void addCommand(const QString &command, const QString &type, const int delay = 200);


    void next();



private slots:
    void response(const QString &s);
    void processError(const QString &s);
    void processTimeout(const QString &s);

public:
    Keithley(QWidget *parent);
    void processCommand(const QString &port, const QString &rawCommand);
    void startRun(const QString &port, double v_from, double v_to, double v_by);
    void stopRun();
    void setVoltage(double v);

signals:
    void measurement(double v, double c);
    void updateProgressBar(int value);
    void rawAnswer(const QString &s);
    void done();


};

#endif // KEITHLEY_H
