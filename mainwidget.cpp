#include "mainwidget.h"
#include "ui_mainwidget.h"
#include <QDebug>
#include <QString>
#include <QMessageBox>
#include <QFileDialog>
#include <QtSql/QSqlError>
#include <QtSql/QSqlRecord>
#include <QDir>
#include <QFileSystemModel>
#include <QFileInfo>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QLabel>


MainWidget::MainWidget(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    ui->formLayout->setContentsMargins(5,5,5,5);
    this->setWindowTitle("SQL Connect Application");

    ui->lineEditHost->setText("127.0.0.1");
    ui->lineEditPort->setText("5432");
    ui->lineEditDBName->setText("postgres");
    ui->lineEditUserName->setText("postgres");
    ui->lineEditPasswd->setText("123456");
    ui->tableNameEdit->setText("files_arc3367890");
    connect(ui->pushButton, &QPushButton::clicked, this,&MainWidget::on_pushButton_clicked);
    connect(ui->pushButtonConnect, &QPushButton::clicked, this,&MainWidget::pushButtonConnectClicked);
}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::pushButtonConnectClicked()
{
    this->db = new DataBase(ui->lineEditHost->text(),
                           ui->lineEditPort->text(),
                           ui->lineEditDBName->text(),
                           ui->lineEditUserName->text(),
                           ui->lineEditPasswd->text());
    //TODO:  make QLineText tableName      send this code to another button SLOT: DONE
    QString tableName = ui->tableNameEdit->text();

    if (!db->isExistsDb(tableName))
    {
        qDebug() << "table Not Exists\n";
        QMessageBox succes;
        succes.setText("table Not Exists");
        succes.setIcon(QMessageBox::Information);
        succes.exec();
        QMessageBox::StandardButton reply;
          reply = QMessageBox::question(this, "Table creation", "Create table " + tableName + "?",
                                        QMessageBox::Yes|QMessageBox::No);
          if (reply == QMessageBox::Yes) {
            qDebug() << "Yes was clicked";
            db->createTable(tableName);
          } else {
            qDebug() << "Yes was *not* clicked";
          }
    }
    QString resultOfTable = db->getContent(tableName);

    qDebug()<<resultOfTable;
    ui->textEdit->setText(resultOfTable);
}


void MainWidget::on_pushButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,"Add file","/home/misha",
        "All Files (*.*)");
    QFile file(fileName);
    QByteArray fileBody;
    try
    {
        if (!file.open(QFile::ReadOnly))
        {
            throw false;
        }
        //fill it by some data
        // Read from file
        fileBody = file.readAll();

        file.close();
    }

    catch (bool&)
    {

        qDebug() << "Could not open file for read";
        QMessageBox succes;
        succes.setText("file Not Exists");
        succes.setIcon(QMessageBox::Information);
        succes.exec();
        return;
    }
    QString table_name = ui->tableNameEdit->text();
    //creation files_arc table query

    if (!(db->addRecord(table_name, fileName, fileBody)))
    {

        qDebug() << "Not recorded to db";
        QMessageBox succes;
        succes.setText("Not recorded to db");
        succes.setIcon(QMessageBox::Information);
        succes.exec();
        return;
    }
    //file.close();

    //getting result of query in our field on form -SELECT id, pg_column_size(id), val, pg_column_size(val) FROM foo;
    QString sizeOfRecord = QString(db->getSizeOfRecord(ui->tableNameEdit->text()));
    QString add = ui->textEdit->toPlainText();
    ui->textEdit->setText(db->getContent(add + '\n' +  ui->lineEditDBName->text()) + " " + sizeOfRecord);
    return;
}

