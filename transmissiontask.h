#ifndef TRANSMISSIONTASK_H
#define TRANSMISSIONTASK_H

#include <QObject>
#include <QNetworkReply>
#include <QProgressBar>

class TransmissionTask : public QObject
{
    Q_OBJECT
public:
    TransmissionTask();
    TransmissionTask(QString name, QNetworkReply *reply, qint8 state, qint64 totalSize);
    ~TransmissionTask();

    QString getName();
    qint8 getState();
    qint64 getTotalSize();
    qint64 getDoneSize();

    void finished();
    void updateProgress(qint64 done, qint64 total);

    // TODO
//    void stop();
//    void resume();

private:
    QString name;
    QNetworkReply *reply;
    qint8 state;
    qint64 totalSize;
    qint64 doneSize;
};

#endif // TRANSMISSIONTASK_H
