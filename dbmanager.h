#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QSqlTableModel>
#include <QDebug>

class DbManager
{
public:
    /**
     * @brief Constructor
     *
     * Constructor sets up connection with db and opens it
     * @param path - absolute path to db file
     */
    // DbManager(const QString& path);
    DbManager(const QString& host, const QString& dbname, const QString& pass, const QString& username);

    /**
     * @brief Destructor
     *
     * Close the db connection
     */
    ~DbManager();

    bool isOpen() const;

    /**
     * @brief Creates a new 'people' table if it doesn't already exist
     * @return true - 'people' table created successfully, false - table not created
     */
    bool addReport(const QString& name, int cf);

    /**
     * @brief Remove report from data from db
     * @param id - name of person to remove.
     * @return true - person removed successfully, false - person not removed
     */
    bool removeReport(const QString& id);

    /**
     * @brief Check if person of name "name" exists in db
     * @param name - name of person to check.
     * @return true - person exists, false - person does not exist
     */
    // bool userExists(const QString& name) const;


    /**
     * @brief Remove all persons from db
     * @return true - all persons removed successfully, false - not removed
     */
    // bool removeAllUsers();

private:
    QSqlDatabase m_db;
};

#endif // DBMANAGER_H
