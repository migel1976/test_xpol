#include "dbmanager.h"

// DbManager::DbManager(const QString &path)
DbManager::DbManager(const QString& host, const QString& dbname, const QString& pass, const QString& username)
{
    m_db = QSqlDatabase::addDatabase("QPSQL");
    m_db.setHostName(host);
    m_db.setDatabaseName(dbname);
    m_db.setPassword(pass);
    m_db.setUserName(username);

    if (!m_db.open())
    {
        qDebug() << "Error: the connection to the database failed";
    }
    else
    {
        qDebug() << "Database: conexion ok";
    }
}

DbManager::~DbManager()
{
    if (m_db.isOpen())
    {
        m_db.close();
    }
}


bool DbManager::addReport(const QString& name)
{
    bool success = false;

    if (!name.isEmpty())
    {
        QSqlQuery queryAdd;
        queryAdd.prepare("INSERT INTO report (name) "
                      "VALUES (?)");
        queryAdd.bindValue(0,name);
        if(queryAdd.exec())
        {
            success = true;
            qWarning() << "Success";
        }
        else
        {
            qWarning() <<"Error adding user:" << queryAdd.lastError();
        }
    }
    else
    {
        qWarning() <<"Error adding user: name cannot be empty";
    }

    return success;
}

bool DbManager::removeReport(const QString& id)
{
    bool success = false;

   // if (userExists(username))
    if(!id.isEmpty())
    {
        // qWarning()<<"id is "<<id;
        QSqlQuery queryDelete;
        queryDelete.prepare("DELETE FROM report WHERE id = :id");
        queryDelete.bindValue(":id", id);
        success = queryDelete.exec();

        if(!success)
            qWarning() << "Delete user failure:" << queryDelete.lastError();
        else
            qWarning() << "User successfully deleted" << id;
    }
    else
    {
        qWarning() << "Error deleting report:id does not exist";
    }
    return success;
}
