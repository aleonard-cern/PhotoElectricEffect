#ifndef SERIALMASTER_H
#define SERIALMASTER_H

#include <QThread>
#include <QMutex>
#include <QWaitCondition>

class SerialMaster : public QThread
{
    Q_OBJECT

public:
    explicit SerialMaster(QObject *parent = nullptr);
    ~SerialMaster();

    void transaction(const QString &portName, int waitTimeout, int delay, const QString &request);
    void run() Q_DECL_OVERRIDE;

signals:
    void response(const QString &s);
    //void requestDone();
    void error(const QString &s);
    void timeout(const QString &s);

private:
    QString portName;
    QString request;
    int waitTimeout;
    int delay;
    QMutex mutex;
    QWaitCondition cond;
    bool quit;
};
#endif // SERIALMASTER_H
