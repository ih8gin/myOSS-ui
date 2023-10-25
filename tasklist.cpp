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
