#include "objecttablemodel.h"
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

ObjectTableModel::ObjectTableModel(QObject *parent)
    : QAbstractTableModel(parent)
{

}

QVariant ObjectTableModel::headerData(int section, Qt::Orientation orientation, int role) const
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

int ObjectTableModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return myObjects.size();
}

int ObjectTableModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return fields.size();
}

void ObjectTableModel::update(QNetworkReply* reply)
{
    QList<MyObject> newObjects;
    QByteArray bytes = reply->readAll();
    QList<QByteArray> jsonData = bytes.split('\n');
//    qDebug().noquote()<<"raw data: "<<bytes;
    for (QByteArray &data : jsonData){
        if (data.isEmpty()) continue;
        QJsonParseError jsonError;
        QJsonDocument doucment = QJsonDocument::fromJson(data, &jsonError);
        if (jsonError.error != QJsonParseError::NoError) {
                qDebug() << QStringLiteral("Fail to parse Json");
                qDebug()<<"state code: "<<reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
                qDebug().noquote()<<"raw data: "<<data;
        }
        // parse json
//        struct MyObject {
//                QString name;
//                qint16 version;
//                qint32 size;
//                QString hash;
//        };
        if (doucment.isObject()){
            MyObject newObject;
            QJsonObject obj = doucment.object();
            QJsonValue value;
            if (obj.contains("Name")){
                value = obj.take("Name");
                if (value.isString()){
                    QString data = value.toString();
                    newObject.name = data;
                }
            }
            if (obj.contains("version")){
                value = obj.take("version");
                if (value.isString()){
                    QString data = value.toString();
                    newObject.version = data.toInt();
                }
            }
            if (obj.contains("size")){
                value = obj.take("size");
                if (value.isString()){
                    QString data = value.toString();
                    newObject.size = data.toInt();
                }
            }
            if (obj.contains("Hash")){
                value = obj.take("Hash");
                if (value.isString()){
                    QString data = value.toString();
                    newObject.hash = data;
                }
            }
            newObjects.append(newObject);
        }
    }
    beginResetModel();
    myObjects = newObjects;
    endResetModel();
    reply->deleteLater();
}

QVariant ObjectTableModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid() || index.column()>=columnCount() || index.row()>=rowCount()) return QVariant();

    switch(role){
        case Qt::DisplayRole:
            switch(index.column())
            {
            case 0: // name of file
                return myObjects[index.row()].name;
                    break;
            case 1: // latest version
                    return myObjects[index.row()].version;
                    break;
            case 2: // size of file
                    return myObjects[index.row()].size;
                    break;
            case 3: // hash value
                    return myObjects[index.row()].hash;
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
