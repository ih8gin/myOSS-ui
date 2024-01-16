#include "tasktablemodel.h"

TaskTableModel::TaskTableModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

QVariant TaskTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    switch(role) {
        case Qt::DisplayRole:
            if(orientation==Qt::Horizontal && section>=0 && section<=columnCount())
                return fields.at(section);
            break;
        default:
            break;
    }

    return QAbstractItemModel::headerData(section, orientation, role);
}

int TaskTableModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return tasks.size();
}

int TaskTableModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return fields.size();
}

QVariant TaskTableModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid() || index.column()>=columnCount() || index.row()>=rowCount()) return QVariant();

    switch(role){
        case Qt::DisplayRole:
            switch(index.column())
            {
            case 0: // name of file
                return tasks[index.row()]->getName();
                break;
            case 1: // trasnsmission state
                return states[tasks[index.row()]->getState()];
                break;
            case 2: // progress bar
//                return tasks[index.row()]->progress;
                return QString("%1 / %2").arg(tasks[index.row()]->getDoneSize()).arg(tasks[index.row()]->getTotalSize());
                break;

            default:
                return QVariant();
                break;
            }

            break;
        case Qt::TextAlignmentRole:
            return Qt::AlignCenter;
            break;
        default:
            return QVariant();
            break;
    }
}

int TaskTableModel::newTask(QString name, QNetworkReply* reply, qint16 state, qint32 totalSize)
{
    TransmissionTask* task = new TransmissionTask(name, reply, state, totalSize);
    beginResetModel();
    tasks.append(task);
    endResetModel();
    qDebug()<<"new transmission task for " << name << " added.";
    return tasks.size();
}
