#ifndef TASKTABLEMODEL_H
#define TASKTABLEMODEL_H

#include <QAbstractTableModel>
#include <transmissiontask.h>
#include <QTimer>

class TaskTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit TaskTableModel(QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    int newTask(QString name, QNetworkReply *reply, qint16 state, qint32 totalSize); // add new task to list
    int loadHistory(); // load history task from memory

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
//    QList<TransmissionTask> tasks = {{"nn", nullptr, 1, 10}};
    QList<TransmissionTask*> tasks;
    const QStringList fields = {"name", "state", "progress"};
    const QStringList states = {"downloading", "downloaded", "uploading", "uploaded"};
};

#endif // TASKTABLEMODEL_H
