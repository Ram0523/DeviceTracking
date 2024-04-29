// deviceinfo.cpp
#include "service1.h"


//std::vector<DeviceInfo> DeviceInfo::deviceList;
std::vector<DeviceInfo*> DeviceInfo::deviceList;

DeviceInfo::DeviceInfo(QObject *parent) : QObject(parent) {
    // Initialize any default values if needed

}

// DeviceInfo::DeviceInfo() {
//     // Initialize any default values if needed
// }

DeviceInfo::DeviceInfo(const DeviceInfo& other): QObject(nullptr),
    deviceName(other.deviceName),
    serialNumber(other.serialNumber),
    assignedTo(other.assignedTo),
    location(other.location),
    imagePath(other.imagePath)
{

}
//DeviceName
QString DeviceInfo::getDeviceName() const {
    return deviceName;
}

void DeviceInfo::setDeviceName(const QString &value) {
    deviceName = value;
}

//SerialNumber
QString DeviceInfo::getSerialNumber() const {
    return serialNumber;
}

void DeviceInfo::setSerialNumber(const QString &value) {
    serialNumber = value;
}


//Assigned
QString DeviceInfo::getAssignedTo() const {
    return assignedTo;
}

void DeviceInfo::setAssignedTo(const QString &value) {
    assignedTo = value;
}


//Location
QString DeviceInfo::getLocation() const {
    return location;
}

void DeviceInfo::setLocation(const QString &value) {
    location = value;
}

// void DeviceInfo::dummy(){
//     qDebug() << "Hello Fuck You!!!!!!!!!!!!!!!!";
// }

//Image
QString DeviceInfo::getImagePath() const {
    return imagePath;
}

void DeviceInfo::setImagePath(const QString &value) {
    imagePath = value;
}


// Static method to add devices to the static vector
void DeviceInfo::addDeviceToList(const DeviceInfo& newDevice) {
    DeviceInfo::deviceList.push_back(new DeviceInfo(newDevice));
}
