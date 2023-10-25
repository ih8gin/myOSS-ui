#include "objectlist.h"
#include "ui_objectlist.h"
#include "objecttablemodel.h"
#include <QFileDialog>

#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QMessageBox>

ObjectList::ObjectList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ObjectList)
{
    ui->setupUi(this);

    ui->tableView->setModel(&objects);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->verticalHeader()->setVisible(false);

    refresher = new QNetworkAccessManager(this);
    connect(refresher,&QNetworkAccessManager::finished,&objects,&ObjectTableModel::update);
    uploader = new QNetworkAccessManager(this);
    connect(uploader,&QNetworkAccessManager::finished,this,&ObjectList::uploadFinished);
    downloader = new QNetworkAccessManager(this);
    connect(downloader,&QNetworkAccessManager::finished,this,&ObjectList::downloadFinished);

    // default server url
    ui->url->setPlainText("http://localhost:55550");
}

ObjectList::~ObjectList()
{
    delete ui;
}

void ObjectList::on_btnRefresh_clicked()
{
    QString apiServerURL = ui->url->toPlainText();
    QNetworkRequest req;
    req.setUrl(QUrl(apiServerURL.append("/versions")));
    req.setAttribute(QNetworkRequest::RedirectionTargetAttribute, true);
    refresher->post(req, QByteArray());
}


void ObjectList::on_btnDownload_clicked()
{
    QModelIndexList selectedRows = ui->tableView->selectionModel()->selectedRows();
    const QModelIndex &index = selectedRows[0];
    QAbstractItemModel *model = ui->tableView->model();
    QString name = model->data(model->index(index.row(), 0)).toString();
    int version = model->data(model->index(index.row(), 1)).toInt();
//        int size = model->data(model->index(index.row(), 2)).toInt();
//        QString hash = model->data(model->index(index.row(), 3)).toString();

    QString downloadDir = QFileDialog::getExistingDirectory(this, "choose download directory");
    downloadFile = new QFile(downloadDir.append(QString("/%1").arg(name)));
    downloadFile->open(QIODevice::WriteOnly);

    QNetworkRequest req;
    req.setUrl(QUrl(ui->url->toPlainText().append("/objects/").append(name).append("?version=").append(QString::number(version))));
//    qDebug()<<downloadDir.append('/').append(name);
//    qDebug()<<req.url();

    downloadReply = downloader->get(req);
    connect((QIODevice *)downloadReply,SIGNAL(readyRead()), this, SLOT(readContent()));

}


void ObjectList::on_btnUpload_clicked()
{
    QString uploadFileName = QFileDialog::getOpenFileName(this, "choose file to upload");
    QFileInfo fileInfo(uploadFileName);

    uploadFile = new QFile(uploadFileName);
    uploadFile->open(QIODevice::ReadOnly);
    QCryptographicHash sha256(QCryptographicHash::Sha256);
    sha256.addData(uploadFile);

    QNetworkRequest req;
    req.setUrl(QUrl(ui->url->toPlainText().append(QString("/objects/%1").arg(fileInfo.fileName()))));
    req.setRawHeader("Digest", "SHA-256="+sha256.result().toBase64());
//    qDebug()<<req.rawHeader("Digest");

    uploadFile->close();
    uploadFile = new QFile(uploadFileName);
    uploadFile->open(QIODevice::ReadOnly);
    uploadReply = uploader->put(req, uploadFile->readAll());
}

void ObjectList::uploadFinished(QNetworkReply* reply)
{

    if(reply->error() != QNetworkReply::NoError)
    {
        qDebug()<<"state code: "<<reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        QMessageBox::critical(NULL, tr("Error"), "Upload Failed!!!");
    } else {
        qDebug()<<"Upload Success.";
    }
    reply->deleteLater();
    //        uploadFile->flush();
    uploadFile->close();
}

void ObjectList::downloadFinished(QNetworkReply* reply)
{

    if(reply->error() != QNetworkReply::NoError)
    {
        qDebug()<<"state code: "<<reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        QMessageBox::critical(NULL, tr("Error"), "Download Failed!!!");
    } else {
        qDebug()<<"Download Success.";
    }
    reply->deleteLater();
    downloadFile->flush();
    downloadFile->close();
}


void ObjectList::readContent()
{
    downloadFile->write(downloadReply->readAll());
}
