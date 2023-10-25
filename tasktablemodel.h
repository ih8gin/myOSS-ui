#ifndef TASKTABLEMODEL_H
#define TASKTABLEMODEL_H

#include <QAbstractTableModel>

class TaskTableModel : public QAbstractTableModel
{
    Q_OBJECT
    struct MyTask{
        QString name;
        qint16 state;
        qint32 totalSize;
        qint32 doneSize;
    };

public:
    explicit TaskTableModel(QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    int newTask(); // add new task to list
    int loadHistory(); // load history task from memory

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
    QList<MyTask> myTasks = {{"nn", 1, 10, 5}};
    const QStringList fields = {"name", "state", "progress"};
    const QStringList states = {"downloading", "downloaded", "uploading", "uploaded"};
};

#endif // TASKTABLEMODEL_H
