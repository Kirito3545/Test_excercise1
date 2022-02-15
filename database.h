#ifndef DATABASE_H
#define DATABASE_H
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

class DataBase
{
public:
    DataBase();
    DataBase(QString host, QString port, QString dbName,QString username,QString passwd);
    bool isExistsDb(QString table_name);
    QString getSizeOfRecord( QString record_name);
    QString getContent(QString db_name);
    QString getResponse(QSqlQuery query);   //creation files_arc table query
    bool createFileRecord(QString fileName, QByteArray fileBody);
    bool checkDb(QString db_name);
    bool addRecord(QString table_name,QString filename, QByteArray fileBody);
    bool createTable(QString table_name);
    //QString getTesponse(QString & result, QSqlQuery query);
private:
    QSqlDatabase m_db ;
};

#endif // DATABASE_H
