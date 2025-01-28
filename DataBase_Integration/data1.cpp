#include "data1.h"


data1::data1() {
    base = QSqlDatabase::addDatabase("QSQLITE");
    base.setDatabaseName("base.db");
    if(OpenConnection()){
        CreateTable();
    };

}

data1::~data1(){
    CloseConnection();
}

bool data1::OpenConnection(){
    // Try to open the database
    if (base.open()) {
        qDebug() << "Connection successful";
        return true;
    } else {
        qDebug() << "Connection failed";
        return false;
    }
}

bool data1::CloseConnection(){
    if (base.isOpen()) {
        base.close();
        qDebug() << "Database connection closed";
        return true;
    } else {
        qDebug() << "No active database connection to close";
        return false;
    }
}


bool data1::CreateTable(){
    // SQL query to create table device_details if not exists
    QString createTableQuery = "CREATE TABLE IF NOT EXISTS device_details ("
                               "device_id INTEGER PRIMARY KEY AUTOINCREMENT,"
                               "device_name TEXT NOT NULL,"
                               "serial_number TEXT NOT NULL,"
                               "assigned_to TEXT NOT NULL,"
                               "location TEXT NOT NULL,"
                               "img_path TEXT NOT NULL"
                               ")";
    // Execute the query
    QSqlQuery query;
    if (query.exec(createTableQuery)) {
        qDebug() << "Table created successfully.";
        return true;
    } else {
        qDebug() << "Error creating table: " << query.lastError().text();
        return false;
    }
}

bool data1::InsertData(const DeviceInfo& newDevice){
    // SQL query to insert device details into device_details table
    QString insertQuery = "INSERT INTO device_details (device_name, serial_number, assigned_to, location, img_path) "
                          "VALUES (:device_name, :serial_number, :assigned_to, :location ,:img_path)";

    // Prepare the query
    QSqlQuery query;
    query.prepare(insertQuery);
    query.bindValue(":device_name", newDevice.getDeviceName());
    query.bindValue(":serial_number", newDevice.getSerialNumber());
    query.bindValue(":assigned_to", newDevice.getAssignedTo());
    query.bindValue(":location", newDevice.getLocation());
    query.bindValue(":img_path", newDevice.getImagePath());

    // Execute the query
    if (query.exec()) {
        qDebug() << "Data inserted successfully.";
        return true;
    } else {
        qDebug() << "Error inserting data: " << query.lastError().text();
        return false;
    }
}

std::vector<DeviceInfo*> data1::RetrieveData()
{
    std::vector<DeviceInfo*> deviceList1;
    int count=0;
    if (OpenConnection())
    {
        QSqlQuery query;
        if (query.exec("SELECT device_name, serial_number, assigned_to, location, img_path FROM device_details"))
        {
            while (query.next())
            {
                DeviceInfo* newDevice = new DeviceInfo();
                newDevice->setDeviceName(query.value(0).toString());
                newDevice->setSerialNumber(query.value(1).toString());
                newDevice->setAssignedTo(query.value(2).toString());
                newDevice->setLocation(query.value(3).toString());
                newDevice->setImagePath(query.value(3).toString());
                deviceList1.push_back(newDevice);
                qDebug()<<++count;
            }
        }
        else
        {
            qDebug() << "Error retrieving data: " << query.lastError().text();
        }
    }

    return deviceList1;
}


