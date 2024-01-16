#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->stackedWidget->addWidget(&objectList);
    ui->stackedWidget->addWidget(&taskList);

    //    btnGroup.setExclusive(false);
    btnGroup.addButton(ui->btnObjects, 0);
    btnGroup.addButton(ui->btnTasks, 1);
    connect(&btnGroup, &QButtonGroup::idClicked, ui->stackedWidget, &QStackedWidget::setCurrentIndex);

    // 设置默认选中的页面
    btnGroup.button(0)->setChecked(true);
    ui->stackedWidget->setCurrentIndex(0);

    connect(&objectList, &ObjectList::newTask, &taskList, &TaskList::newTask);
    connect(&objectList, &ObjectList::progressUpdate, &taskList, &TaskList::update);
}

MainWindow::~MainWindow()
{
    delete ui;
}

