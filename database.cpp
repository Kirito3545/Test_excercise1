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

bool DataBase::addRecord(QString table_name,QString filename, QByteArray fileBody)
{
    //creation files_arc table query
     /* create table FILES_ARC(fileID serial primary key,
      * name varchar(255) not null,body bytea);
      * */

    //adding record into table with table_name
    QSqlQuery qry;
    qry.prepare("INSERT INTO "+table_name+"(name, body) VALUES(:NAME, :BODY)");
     //qry.bindValue(":ID", 39);
     //qry.bindValue(":ID",44);
     qry.bindValue(":NAME",filename);
     qry.bindValue(":BODY",fileBody);

     if (!qry.exec())
     {
     qDebug()<<"fail!! record not added" << '\n';
         QMessageBox fail;
         fail.setText("file" + filename + "not added!");
         fail.setIcon(QMessageBox::Critical);
         fail.exec();
         return false;
     }

    this->getContent(table_name);
    return true;
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
        qDebug() << "sendig qury: " << queryStr;


        if (!query.exec(queryStr))
        {
            throw false;

        }
    }
    catch (bool&)
    {
        qDebug() << query.lastError().databaseText();
        qDebug() << query.lastError().driverText();
        qDebug() << "Can't find " << table_name << "table\n";

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

bool DataBase::createTable(QString table_name)
{
    QSqlQuery query = QSqlQuery(m_db);
    try{
         QString queryStr = "create  table "+table_name+"(name varchar(255) not null,body bytea);";
        qDebug() << "sendig query: " << queryStr;

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
        succes.setText("Exception handle! Error " + table_name);
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
QString DataBase::getContent(QString table_name)
{
    QSqlQuery query("SELECT name, pg_column_size(body) FROM "+table_name+";");

    QString result;
    QString outOfTable;
    QSqlRecord record = query.record();
    while (query.next())
    {
        for (int num = 0; num < record.count(); ++num)
        {
            outOfTable+=record.fieldName(num)+'='+ query.value(num).toString()+'\n';
            qDebug() <<  outOfTable;
            result+=outOfTable;
        }
    }
    return result;
}

bool DataBase::createFileRecord(QString fileName, QByteArray fileBody)
{
    QSqlQuery qry;

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


QString DataBase::getSizeOfRecord( QString table_name)
{
    QSqlQuery query = QSqlQuery(m_db);
    try{
         QString queryStr = "SELECT name, concat(length(body) / 1048576.0, ' MB') FROM "+table_name+";";


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
        succes.setText("Exception handle! Can't get from "+table_name+")");
        succes.setIcon(QMessageBox::Critical);
        succes.exec();
    }

    return this->getResponse(query);
}

QString DataBase::getResponse(QSqlQuery query)
{
    QString result;
    QString outOfTable;
    QSqlRecord record = query.record();
    result+="List of files:\n";
    while (query.next())
    {
        result+="  Record:\n";
        result+=record.fieldName(0)+'='+ query.value(0).toString()+'\n';
        result+="size="+query.value(1).toString()+'\n';
 //     result+="size="+query.value(1).toString()+'\n';
        qDebug() <<  result;
    }
    return result;
}
