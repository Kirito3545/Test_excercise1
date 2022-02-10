//#include "mainwidget.h"
//#include "ui_mainwidget.h"
//#include <QDebug>
//#include <QMessageBox>
//#include <QFileDialog>
//#include <QtSql/QSqlError>
//#include <QtSql/QSqlRecord>

//MainWidget::MainWidget(QWidget *parent)
//    : QMainWindow(parent)
//    , ui(new Ui::MainWidget)
//{
//    ui->setupUi(this);




//    try {

//            db = QSqlDatabase::addDatabase("QPSQL");
//            db.setHostName("127.0.0.1");
//            db.setPort(5432);
//            db.setDatabaseName("postgres");
//            db.setUserName("postgres");
//            db.setPassword("123456");
//            if (!db.open()){
//                qDebug() << db.lastError().text();
//            }
//            else {
//                qDebug() << "Success!";

//            }


//           QSqlQuery query("SELECT * FROM files_arc");
//           //query.first();
//           //auto response = query.value(0).toString();
//           //qDebug() << response;
//           while (query.next()) {
//               auto const id = query.value(0).toInt();
//               auto const name = query.value(1).toString();
//               auto const price = query.value(2).toString();
//               qInfo() << query.value(0).toString().toLocal8Bit()<< query.value(1).toString().toLocal8Bit()<< query.value(2).toString();
//               qDebug() << id << name << price << '\n';
//           }

////           if (db.transaction()) {
////               QSqlQuery query;
////               query.prepare("INSERT INTO PRODUCTS(ID, NAME, PRICE) VALUES(:ID, :NAME, :PRICE)");
////               query.bindValue(":ID", 4);
////               query.bindValue(":NAME", "D");
////               query.bindValue(":PRICE", "4.4");
////               query.exec();
////               db.commit();
////               qDebug() << db.lastError();
////           }


//       } catch (std::exception const& e) {

//       }

//    connect( ui->pushButton,&QPushButton::clicked,this,&MainWidget::on_pushButton_clicked);
//}

//MainWidget::~MainWidget()
//{
//    delete ui;
//}


//void MainWidget::on_pushButton_clicked()
//{
//    try
//    {
//    QString fileName = QFileDialog::getOpenFileName(this,
//        tr("Open Text file"), "", tr("All Files (*.*)"));
//    QFile file(fileName);
//    if (!file.open(QFile::ReadOnly)) {
//     qDebug() << "Could not open file for reading";
//     return;
//    }
//    //fill it by some data
//     QByteArray ba = file.readAll();
//     // Read from file

//     //qDebug()<< ba.toHex();

//    /*SELECT EXISTS (
//     SELECT FROM information_schema.tables
//     WHERE  table_schema = 'public'
//     AND    table_name   = 'files_arc'
//     );*/
//     QSqlQuery query = QSqlQuery(db);
//     QString queryStr = "SELECT EXISTS ( \
//             SELECT FROM information_schema.tables \
//             WHERE  table_schema = 'public'\
//             AND    table_name   = 'files_arc' \
//             );";
//     if (!query.exec(queryStr))
//     {
//         qDebug() << query.lastError().databaseText();
//         qDebug() << query.lastError().driverText();
//         return;//TODO: try catch
//     }
//     qDebug() << "Table exists" << '\n';
//     QSqlQuery qry;

//     //creation files_arc table query
//     /* create table FILES_ARC(fileID serial primary key,
//      * name varchar(255) not null,body bytea);
//      * */
//     qry.prepare("INSERT INTO files_arc(fileID, name, body) VALUES(:ID, :NAME, :BODY)");
//     qry.bindValue(":ID", 39);
//     //qry.bindValue(":ID",44);
//     qry.bindValue(":NAME",fileName);
//     qry.bindValue(":BODY",ba);

//     if (qry.exec())
//         {
//         qDebug()<<"success!! added record" << '\n';
//             QMessageBox succes;
//             succes.setText("file" + fileName + " added!");
//             succes.setIcon(QMessageBox::Information);
//             succes.exec();
//         }
//     while(query.next()){
//         qDebug() << query.record();
//         }

//    QSqlQuery query1 = QSqlQuery(db);
//    if (!query1.exec("select * from files_arc")){
//        qDebug() << query1.lastError().databaseText();
//        qDebug() << query1.lastError().driverText();
//        return;
//    }
//    while(query1.next()){
//        qDebug() << query1.record();
//        }

//    file.close();
//}
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


//    db = QSqlDatabase::addDatabase("QPSQL");
//    db.setHostName(ui->lineEditHost->text());//("127.0.0.1");
//    db.setPort(ui->lineEditPort->text().toInt());//(5432);
//    db.setDatabaseName(ui->lineEditDBName->text());//("postgres");
//    db.setUserName(ui->lineEditUserName->text());//("postgres");
//    db.setPassword(ui->lineEditPasswd->text());//

//        try
//        {
//            if (!db.open())
//                throw false;
//        }
//        catch (bool&)
//        {
//            qDebug() << "Exception handled " << '\n';
//            qDebug() << db.lastError().text() << '\n';
//            //
//            QMessageBox fail;
//            fail.setText("Exception handle! ");
//            fail.setIcon(QMessageBox::Information);
//            fail.exec();
//            exit(0);
//        }





//        QSqlQuery query = QSqlQuery(db);
//        QString queryStr = "SELECT EXISTS ( \
//             SELECT FROM information_schema.tables \
//             WHERE table_schema = 'public'\
//             AND    table_name   = 'files_arc' \
//             );";
//        if (!query.exec(queryStr))
//        {
//            qDebug() << query.lastError().databaseText();
//            qDebug() << query.lastError().driverText();

//            QMessageBox succes;
//            succes.setText("Exception handle! ");
//            succes.setIcon(QMessageBox::Information);
//            succes.exec();
//        }

//        QSqlQuery query1("SELECT * FROM files_arc");
//        while (query1.next()) {
//            auto const id = query.value(0).toInt();
//            auto const name = query.value(1).toString();
//            auto const body = query.value(2).toString();
//            qInfo() << query1.value(0).toString().toLocal8Bit() << query.value(1).toString().toLocal8Bit() << query.value(2).toString();
//            qDebug() << id << name << body << '\n';
//        }






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
    //TODO:  make QLineText tableName      send this code to another button SLOT
    QString tableName = "files_arc1hlkjhl";
    if (!db->isExistsDb(tableName))
        qDebug() << "table Not Exists\n";


    qDebug()<<db->getContent(tableName);
}


void MainWidget::on_pushButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open Text file"), "..", tr("All Files (*.*)"));
    QFile file(fileName);
    QByteArray fileBody;
    try
    {
        if (!file.open(QFile::ReadOnly))
        {
            throw false;
        }

        file.close();
        //fill it by some data
        fileBody = file.readAll();
        // Read from file
        file.close();
    }

    catch (bool&)
    {

        qDebug() << "Could not open file for read";

    }



   // ui->tableVi

//        QSqlQuery query = QSqlQuery(db);
//        QString queryStr = "SELECT EXISTS ( \
//                 SELECT FROM information_schema.tables \
//                 WHERE  table_schema = 'public'\
//                 AND    table_name   = 'files_arc' \
//                 );";
//        if (!query.exec(queryStr))
//        {
//            qDebug() << query.lastError().databaseText();
//            qDebug() << query.lastError().driverText();

//        }
//        qDebug() << "Table exists" << '\n';
//        QSqlQuery qry;

//        //creation files_arc table query
//        /* create table FILES_ARC(fileID serial primary key,
//         * name varchar(255) not null,body bytea);
//         * */
//        qry.prepare("INSERT INTO files_arc(fileid,name, body) VALUES( :NAME, :BODY)");
//        //qry.bindValue(":ID", 33);
//        qry.bindValue(":NAME", fileName);
//        qry.bindValue(":BODY", ba);


//        if (qry.exec())
//        {
//            qDebug() << "success!! added record" << '\n';
//            QMessageBox succes;
//            succes.setText("file" + fileName + " added!");
//            succes.setIcon(QMessageBox::Information);
//            succes.exec();
//        }

//        while (qry.next())
//        {
//            qDebug() << qry.record();
//        }




//        QSqlQuery query1 = QSqlQuery(db);
//        if (!query1.exec("select * from files_arc"))
//        {
//            qDebug() << query1.lastError().databaseText();
//            qDebug() << query1.lastError().driverText();
//            return;
//        }
//        while (query1.next())
//        {
//            qDebug() << query1.record();
//        }


}

