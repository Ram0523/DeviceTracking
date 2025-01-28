#ifndef DATA1_H
#define DATA1_H

#include <QObject>
#include <QDir>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include "../Service1/service1.h"

class data1 : public QObject
{
    Q_OBJECT
public:
    data1();
    ~data1();

    bool OpenConnection();
    bool CloseConnection();
    bool CreateTable();
    bool InsertData(const DeviceInfo& newDevice);
    std::vector<DeviceInfo*> RetrieveData();

private:
    QSqlDatabase base;
};

#endif // DATA1_H
