#ifndef OBJECTTABLEMODEL_H
#define OBJECTTABLEMODEL_H

#include <QAbstractTableModel>
#include <QNetworkReply>

class ObjectTableModel : public QAbstractTableModel
{
    Q_OBJECT
    struct MyObject {
        QString name;
        qint16 version;
        qint32 size;
        QString hash;
    };

public:
    explicit ObjectTableModel(QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    void update(QNetworkReply* reply); // update data list

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
    QList<MyObject> myObjects = {{"zsy", -1, -1, "xx"}};
    const QStringList fields = {"name", "version", "size", "hash"};
    QNetworkAccessManager *dataRefresher;
};

#endif // OBJECTTABLEMODEL_H
