// #ifndef DEVICEINFO_H
// #define DEVICEINFO_H

// class deviceinfo
// {
// public:
//     deviceinfo();
// };

// #endif // DEVICEINFO_H


// deviceinfo.h
#ifndef DEVICEINFO_H
#define DEVICEINFO_H

#include<QMainWindow>
#include <QDir>
#include <QString>


class DeviceInfo : public QObject {
    Q_OBJECT

public:
    DeviceInfo(QObject *parent = nullptr);
    //DeviceInfo();
    DeviceInfo(const DeviceInfo& other);
    QString getDeviceName() const;
    void setDeviceName(const QString &value);

    QString getSerialNumber() const;
    void setSerialNumber(const QString &value);

    QString getAssignedTo() const;
    void setAssignedTo(const QString &value);

    QString getLocation() const;
    void setLocation(const QString &value);

    QString getImagePath() const;
    void setImagePath(const QString &value);

    // Static vector to store instances of DeviceInfo
    static std::vector<DeviceInfo*> deviceList;


public slots:
    // Static method to add devices to the static vector
    void addDeviceToList(const DeviceInfo& newDevice);


private:
    QString deviceName;
    QString serialNumber;
    QString assignedTo;
    QString location;
    QString imagePath;

};

#endif // DEVICEINFO_H
