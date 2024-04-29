#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "vector"
#include <QObject>

using namespace std;

#include <QMainWindow>

#include "service1.h"
#include "data1.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void addDeviceToListSignal(const DeviceInfo& newDevice);
    // void dummysignal();

private slots:
    void on_SaveB_clicked();
    void on_SelectImg_clicked();
    void on_GenerateB_clicked();

private:
    Ui::MainWindow *ui;
    DeviceInfo *newDevice = nullptr;
    QString filePath;
    data1 *db;
};
#endif // MAINWINDOW_H
