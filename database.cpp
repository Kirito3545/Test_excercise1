#include "database.h"


DataBase::DataBase(QString host,QString port,QString dbName,QString username,QString passwd)
{
    m_db = QSqlDatabase::addDatabase("QPSQL");
    m_db.setHostName(host);//("127.0.0.1");
    m_db.setPort(port.toInt());//(5432);
    m_db.setDatabaseName(dbName);//("postgres");
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

bool DataBase::isExistsDb(QString table_name)
{
    QSqlQuery query = QSqlQuery(m_db);
    try{
         QString queryStr = "SELECT EXISTS \
         SELECT FROM information_schema.tables ( \
         WHERE  table_schema = 'public'\
         AND    table_name   = '" + table_name+ "')";


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

        QMessageBox succes;
        succes.setText("Exception handle! Please create a table");
        succes.setIcon(QMessageBox::Information);
        succes.exec();
    }
    while (query.next())
    {
        qDebug() << query.record();
    }
    return true;
}
QString DataBase::getContent(QString db_name)
{
    QSqlQuery query("SELECT * FROM " + db_name);
    QString result;
    while (query.next()) {
        auto const id = query.value(0).toInt();
        auto const name = query.value(1).toString();
        auto const body = query.value(2).toString();
        qInfo() << query.value(0).toString().toLocal8Bit() << query.value(1).toString().toLocal8Bit() << query.value(2).toString();
        qDebug() << id << name << body << '\n';
        result.append(id);
        result.append(name);
        result.append(body);
    }
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
