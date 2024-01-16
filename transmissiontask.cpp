#include "transmissiontask.h"

TransmissionTask::TransmissionTask()
{
}

TransmissionTask::TransmissionTask(QString name, QNetworkReply *reply, qint8 state, qint64 totalSize)
{
    this->name = name;
    this->reply = reply;
    this->state = state;
    this->totalSize = totalSize;
    connect(reply, &QNetworkReply::uploadProgress, this, &TransmissionTask::updateProgress);
    connect(reply, &QNetworkReply::downloadProgress, this, &TransmissionTask::updateProgress);
    connect(reply, &QNetworkReply::finished, this, &TransmissionTask::finished);
}

TransmissionTask::~TransmissionTask()
{
}

QString TransmissionTask::getName(){
    return name;
}
qint8 TransmissionTask::getState(){
    return state;
}
qint64 TransmissionTask::getTotalSize()
{
    return totalSize;
}
qint64 TransmissionTask::getDoneSize()
{
    return doneSize;
}

void TransmissionTask::finished()
{
    state += 1;
}

void TransmissionTask::updateProgress(qint64 done, qint64 total)
{
    if (done != 0) doneSize = done;
}
