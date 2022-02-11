#include "database.h"


DataBase::DataBase(QString host,QString port,QString dbName,QString username,QString passwd)
{
    m_db = QSqlDatabase::addDatabase("QPSQL");
    m_db.setHostName(host);
    m_db.setPort(port.toInt());
    m_db.setDatabaseName(dbName);
    m_db.setUserName(username);
    m_db.setPassword(passwd);

    try
    {
        if (!m_db.open())
            throw false;
    }
    catch (bool&)
    {
        qDebug() << "Exception handled " << '\n';
        qDebug() << m_db.lastError().text() << '\n';
        //
        QMessageBox fail;
        fail.setText("Exception handle! ");
        fail.setIcon(QMessageBox::Information);
        fail.exec();
        exit(0);
    }
}

bool DataBase::addRecord(QString filename, QByteArray fileBody)
{
    //creation files_arc table query
     /* create table FILES_ARC(fileID serial primary key,
      * name varchar(255) not null,body bytea);
      * */
    QSqlQuery qry;
    qry.prepare("INSERT INTO files_arc(fileID, name, body) VALUES(:ID, :NAME, :BODY)");
     qry.bindValue(":ID", 39);
     //qry.bindValue(":ID",44);
     qry.bindValue(":NAME",filename);
     qry.bindValue(":BODY",fileBody);

     if (qry.exec())
     {
     qDebug()<<"success!! added record" << '\n';
         QMessageBox succes;
         succes.setText("file" + filename + " added!");
         succes.setIcon(QMessageBox::Information);
         succes.exec();
     }

     while(qry.next()){
         qDebug() << qry.record();
         }

    QSqlQuery query1 = QSqlQuery(m_db);
    if (!query1.exec("select * from files_arc")){
        qDebug() << query1.lastError().databaseText();
        qDebug() << query1.lastError().driverText();
        return true;
    }
    while(query1.next()){
        qDebug() << query1.record();
        }
}

bool DataBase::isExistsDb(QString table_name)
{
    QSqlQuery query = QSqlQuery(m_db);
    try{
         QString queryStr = "SELECT EXISTS \
                 (\
                     SELECT 1\
                     FROM information_schema.tables \
                     WHERE table_schema = 'public'\
                     AND table_name = '"+table_name+"'\
                 )";

         /*
         SELECT EXISTS
         (
             SELECT 1
             FROM information_schema.tables
             WHERE table_schema = 'schema_name'
             AND table_name = 'table_name'
         );*/
         /*

SELECT EXISTS
(
    SELECT 1
    FROM information_schema.tables
    WHERE table_schema = 'schema_name'
    AND table_name = 'table_name'
);*/
        /*SELECT count(*)
         FROM information_schema.TABLES
         WHERE TABLE_NAME = 'table_name';*/
        /*SELECT FROM information_schema.tables WHERE (table_schema = 'public' AND
        table_name   = 'files_arc');*/
                 /*SELECT FROM information_schema.tables WHERE (table_schema = 'public' AND
        table_name   = 'files_arc');*/

        if (!query.exec(queryStr))
        {
            throw false;

        }
    }
    catch (bool&)
    {
        qDebug() << query.lastError().databaseText();
        qDebug() << query.lastError().driverText();
        qDebug() << "Can't create " << table_name << "table\n";

        QMessageBox succes;
        succes.setText("Exception handle! Please create a table " + table_name);
        succes.setIcon(QMessageBox::Information);
        succes.exec();
    }
    int i = 0;
    while (query.next())
    {
        if (!(query.value(i).toInt() ==1)) return false;
        qDebug() << query.value(i).toBool();
        i++;
    }

    return true;
}
QString DataBase::getContent(QString db_name)
{
    QSqlQuery query("SELECT * FROM " + db_name);
    QString result;

//    while (query.next()) {
//        auto const id = query.value(0).toInt();
//        auto const name = query.value(1).toString();
//        auto const body = query.value(2).toString();
//        qInfo() << query.value(0).toString().toLocal8Bit() << query.value(1).toString().toLocal8Bit() << query.value(2).toString();
//        qDebug() << id << name << body << '\n';
//        qDebug() << query.record();
//        result.append(id);
//        result.append(name);
//        result.append(body);
//    }
    /*
QSqlRecord(4)
 0: QSqlField("id", int, tableName: "files_arc", length: 4, generated: yes, typeID: 23, autoValue: false, readOnly: false) "35"
 1: QSqlField("fileid", QString, tableName: "files_arc", length: 255, generated: yes, typeID: 1043, autoValue: false, readOnly: false) "33"
 2: QSqlField("name", QString, tableName: "files_arc", length: 255, generated: yes, typeID: 1043, autoValue: false, readOnly: false) "/home/misha/Test1.1"
 3: QSqlField("body", QByteArray, tableName: "files_arc", generated: yes, typeID: 17, autoValue: false, readOnly: false) "#include \"mainwidget.h\"\n#include \"ui_mainwidget.h\"\n#include <QDebug>\n#include <QtSql/QSqlError>\n#include <QtSql/QSqlRecord>\n\nMainWidget::MainWidget(QWidget *parent)\n    : QMainWindow(parent)\n    , ui(new Ui::MainWidget)\n{\n    ui->setupUi(this);\n\n\n\n\n    try {\n\n            db = QSqlDatabase::addDatabase(\"QPSQL\");\n            db.setHostName(\"127.0.0.1\");\n            db.setPort(5432);\n            db.setDatabaseName(\"postgres\");\n            db.setUserName(\"postgres\");\n            db.setPassword(\"123456\");\n            if (!db.open()){\n                qDebug() << db.lastError().text();\n            }\n            else {\n                qDebug() << \"Success!\";\n\n            }\n\n\n           QSqlQuery query(\"SELECT * FROM test1\");\n           //query.first();\n           //auto response = query.value(0).toString();\n           //qDebug() << response;\n           while (query.next()) {\n               auto const id = query.value(0).toInt();\n               auto const name = query.value(1).toString();\n               auto const price = query.value(2).toString();\n               qInfo() << query.value(0).toString().toLocal8Bit()<< query.value(1).toString().toLocal8Bit()<< query.value(2).toString();\n               qDebug() << id << name << price << '\\n';\n           }\n\n//           if (db.transaction()) {\n//               QSqlQuery query;\n//               query.prepare(\"INSERT INTO PRODUCTS(ID, NAME, PRICE) VALUES(:ID, :NAME, :PRICE)\");\n//               query.bindValue(\":ID\", 4);\n//               query.bindValue(\":NAME\", \"D\");\n//               query.bindValue(\":PRICE\", \"4.4\");\n//               query.exec();\n//               db.commit();\n//               qDebug() << db.lastError();\n//           }\n\n\n       } catch (std::exception const& e) {\n\n       }\n\n    connect( ui->pushButton,&QPushButton::clicked,this,&MainWidget::on_pushButton_clicked);\n}\n\nMainWidget::~MainWidget()\n{\n    delete ui;\n}\n\n\nvoid MainWidget::on_pushButton_clicked()\n{\n    QSqlQuery query = QSqlQuery(db);\n    if (!query.exec(\"select * from test1\")){\n        qDebug() << query.lastError().databaseText();\n        qDebug() << query.lastError().driverText();\n        return;\n    }\n\n    while(query.next()){\n        qDebug() << query.record();\n    }\n}\n"
"\u001933/home/misha/Test1.1\u001A33/home/misha/Test1.1\u001B33/home/m
    */
    QVariantList res;
    while (query.next())
    {
        QVariantMap ent;
        ent["id"] = query.value(0).toInt();
        ent["tableName"] = query.value(1).toString();
        ent["f2"] = query.value(2).toString();
        ent["f3"] = query.value(3).toString();
        ent["f4"] = query.value(4).toString();
        //qDebug() << ent;
        qDebug()<<query.record();
        res.append(ent);
    }
    //qDebug() << res;
    return result;
}

bool DataBase::createFileRecord(QString db_name,QString fileName, QByteArray fileBody)
{
    QSqlQuery qry;

    /* create table FILES_ARC(fileID serial primary key,
     * name varchar(255) not null,body bytea);
     * */
    try
    {
        qry.prepare("INSERT INTO files_arc(name, body) VALUES( :NAME, :BODY)");
        //qry.bindValue(":ID", 33);
        qry.bindValue(":NAME", fileName);
        qry.bindValue(":BODY", fileBody);


        if (!qry.exec())
        {
            throw false;
        }
    }
    catch (bool&)
    {
        qDebug() << "Smthing wrong!! record not added" << '\n';
        QMessageBox fail;
        fail.setText("Smthing wrong !");
        fail.setIcon(QMessageBox::Critical);
        fail.exec();
    }
    qDebug() << "success!! added record" << "file" << fileName << " added!" << '\n';
    while (qry.next())
    {
        qDebug() << qry.record();
    }
    return true;
}


//check db records without try catch
bool DataBase::checkDb(QString db_name)
{
    QSqlQuery query1 = QSqlQuery(m_db);

    if (!query1.exec("select * from " + db_name))
    {
        qDebug() << query1.lastError().databaseText();
        qDebug() << query1.lastError().driverText();
        return false;
    }
    while (query1.next())
    {
        qDebug() << query1.record();
    }
    return true;
}
