#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QMainWindow>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlTableModel>
#include <QLabel>

//my headers
#include "database.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWidget; }
QT_END_NAMESPACE

class MainWidget : public QMainWindow
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

private slots:
    void on_pushButton_clicked();
    void pushButtonConnectClicked();


private:
    Ui::MainWidget *ui;
    //QSqlDatabase db;
    QSqlTableModel* model;
    DataBase* db;


};
#endif // MAINWIDGET_H
