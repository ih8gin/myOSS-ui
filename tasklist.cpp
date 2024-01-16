#include "tasklist.h"
#include "ui_tasklist.h"

TaskList::TaskList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TaskList)
{
    ui->setupUi(this);

    ui->tableView->setModel(&tasks);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->verticalHeader()->setVisible(false);
}

TaskList::~TaskList()
{
    delete ui;
}

void TaskList::newTask(QString name, QNetworkReply *reply, qint16 state, qint32 totalSize)
{
    tasks.newTask(name, reply, state, totalSize);
}

void TaskList::update()
{
    ui->tableView->viewport()->update();
}
