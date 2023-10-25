#ifndef OBJECTLIST_H
#define OBJECTLIST_H

#include <QWidget>
#include <QProgressBar>
#include <QFile>
#include "objecttablemodel.h"

namespace Ui {
class ObjectList;
}

class ObjectList : public QWidget
{
    Q_OBJECT

public:
    explicit ObjectList(QWidget *parent = nullptr);
    ~ObjectList();

private slots:
    void on_btnRefresh_clicked();

    void on_btnDownload_clicked();

    void on_btnUpload_clicked();

    void uploadFinished(QNetworkReply* reply);
    void downloadFinished(QNetworkReply* reply);

    void readContent();

private:
    Ui::ObjectList *ui;
    ObjectTableModel objects;
    QNetworkAccessManager *refresher;
    QNetworkAccessManager *downloader;
    QNetworkAccessManager *uploader;
    QNetworkReply *downloadReply;
    QNetworkReply *uploadReply;
    QFile *uploadFile;
    QFile *downloadFile;
    QProgressBar *progressBar;
};

#endif // OBJECTLIST_H
