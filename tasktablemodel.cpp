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

    return myTasks.size();
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
                return myTasks[index.row()].name;
                break;
            case 1: // latest version
                return states[myTasks[index.row()].state];
                break;
            case 2: // size of file
                return QString("%1 / %2").arg(myTasks[index.row()].doneSize).arg(myTasks[index.row()].totalSize);
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
