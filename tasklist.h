#ifndef TASKLIST_H
#define TASKLIST_H

#include <QWidget>
#include "tasktablemodel.h"

namespace Ui {
class TaskList;
}

class TaskList : public QWidget
{
    Q_OBJECT
public:
    explicit TaskList(QWidget *parent = nullptr);
    ~TaskList();

public slots:
    void newTask(QString name, QNetworkReply *reply, qint16 state, qint32 totalSize);
    void update();

private:
    Ui::TaskList *ui;
    TaskTableModel tasks;
};

#endif // TASKLIST_H
