#include "mainwindow.h"
#include "./ui_mainwindow.h"
// #include "deviceinfo.h"
#include "QFileDialog"
#include <QPdfWriter>
#include <QPainter>
#include "QDesktopServices"
#include "QtPrintSupport/QPrinter"
#include <QTextDocument>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    db=new data1;
    //connect(db, &data::addDeviceToListSignal, this, &MainWindow::onAddDeviceToList);

    // Retrieve data from the database and store it in the DeviceInfo::deviceList vector
    std::vector<DeviceInfo*> retrievedDevices = db->RetrieveData();

    for (DeviceInfo* device : retrievedDevices)
    {
        connect(this,&MainWindow::addDeviceToListSignal, device, &DeviceInfo::addDeviceToList);
        emit addDeviceToListSignal(*device);
        disconnect(this,&MainWindow::addDeviceToListSignal, device, &DeviceInfo::addDeviceToList);
        // DeviceInfo::deviceList.push_back(device);
    }


    int count=0;
    for (DeviceInfo* device : DeviceInfo::deviceList)
    {

        qDebug() << "Device Name: " << device->getDeviceName();
        qDebug() << "Serial Number: " << device->getSerialNumber();
        qDebug() << "Assigned To: " << device->getAssignedTo();
        qDebug() << "Location: " << device->getLocation();
        qDebug()<<++count;
        qDebug() << "----------------------------";
    }

     ui->Location->setPlaceholderText("select");
    ui->Location->addItem("Pune");
    ui->Location->addItem("Hydrabad");

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_SaveB_clicked()
{
    // Get values from UI elements
    QString deviceName = ui->DeviceName->toPlainText();
    QString serialNumber = ui->SerialNo->toPlainText();
    QString assignedTo = ui->AssignedTo->toPlainText();
    QString location = ui->Location->currentText();
    // QString imagePath = filePath;

    // Create a new DeviceInfo object
    newDevice = new DeviceInfo();
    newDevice->setDeviceName(deviceName);
    newDevice->setSerialNumber(serialNumber);
    newDevice->setAssignedTo(assignedTo);
    newDevice->setLocation(location);
    newDevice->setImagePath(filePath);


    qDebug() << newDevice->getDeviceName();
    connect(this,&MainWindow::addDeviceToListSignal, newDevice, &DeviceInfo::addDeviceToList);
    connect(this,&MainWindow::addDeviceToListSignal,db,&data1::InsertData);
    emit addDeviceToListSignal(*newDevice);

    // Optionally, you can clear the UI elements after saving
    ui->DeviceName->clear();
    ui->SerialNo->clear();
    ui->AssignedTo->clear();
    ui->Location->clear();
    ui->notification1->clear();

}


void MainWindow::on_SelectImg_clicked()
{
    // Open a file dialog to select an image file
     filePath = QFileDialog::getOpenFileName(this, "Open Image", "", "Image Files (*.png *.jpg *.bmp)");

    // Check if a file was selected
    if (!filePath.isEmpty()) {
        // Do something with the file path, e.g., display it in a QLabel
        ui->notification1->setText("Selected Image: " + filePath);
        // You can also load and display the image using QPixmap or QImage
        // QPixmap image(filePath);
        // ui->label->setPixmap(image);
    } else {
        ui->notification1->setText("No image selected.");
    }
}


// void MainWindow::on_GenerateB_clicked()
// {

//     // Get values from UI elements
//     QString deviceName = ui->DeviceName->toPlainText();
//     QString serialNumber = ui->SerialNo->toPlainText();
//     QString assignedTo = ui->AssignedTo->toPlainText();
//     QString location = ui->Location->currentText();
//     QString imagePath = filePath;


//     QString pdfFileName = "DeviceInformation.pdf";
//     QString pdfFilePath = QDir::currentPath() + "/" + pdfFileName;
//     qDebug() << "PDF File Path: " << pdfFilePath;
//     QPdfWriter pdfWriter(pdfFilePath);


//     pdfWriter.setResolution(300); // Adjust resolution as needed

//     QPainter painter(&pdfWriter);

//     // Use QTextOption to control text alignment
//     QTextOption textOption(Qt::AlignLeft | Qt::AlignTop);
//      QRectF textRect = pdfWriter.pageLayout().paintRect();


//     // Open a text block
//     painter.begin(&pdfWriter);
//     painter.setFont(QFont("Arial", 12));

//     // Add a title
//     painter.drawText(textRect, "Device Information", textOption);

//     // Insert device details
//     textRect.adjust(0, 30, 0, 0); // Adjust vertical position
//     painter.drawText(textRect, "Device Name: " + deviceName, textOption);
//     textRect.adjust(0, 20, 0, 0);
//     painter.drawText(textRect, "Serial Number: " + serialNumber, textOption);
//     textRect.adjust(0, 20, 0, 0);
//     painter.drawText(textRect, "Assigned To: " + assignedTo, textOption);
//     textRect.adjust(0, 20, 0, 0);
//     painter.drawText(textRect, "Location: " + location, textOption);
//     textRect.adjust(0, 20, 0, 0);
//     painter.drawText(textRect, "Image Path: " + imagePath, textOption);

//     // Close the text block
//     painter.end();

//     // Open the generated PDF file
//     QDesktopServices::openUrl(QUrl::fromLocalFile(pdfFilePath));

//     ui->notification1->setText("PDF generated successfully!");
// }








void MainWindow::on_GenerateB_clicked()
{
    // Get values from UI elements
    QString deviceName = ui->DeviceName->toPlainText();
    QString serialNumber = ui->SerialNo->toPlainText();
    QString assignedTo = ui->AssignedTo->toPlainText();
    QString location = ui->Location->currentText();
    QString imagePath = filePath;

   // QString pdfFileName = "DeviceInformation.pdf";
    //QString pdfFilePath = QDir::currentPath() + "/" + pdfFileName;
    QString pdfFilePath=QFileDialog::getSaveFileName(this,tr("Save Pdf"),"Output.pdf",tr("PDF Files(*.pdf"));
    qDebug() << "PDF File Path: " << pdfFilePath;

    // Create a QTextDocument
    QTextDocument document;

    // Use QTextCursor to write content to the document
    QTextCursor cursor(&document);

    // Add a title
    cursor.insertText("Device Information\n\n");

    // Insert device details
    cursor.insertText("Device Name: " + deviceName + "\n");
    cursor.insertText("Serial Number: " + serialNumber + "\n");
    cursor.insertText("Assigned To: " + assignedTo + "\n");
    cursor.insertText("Location: " + location + "\n");
    //cursor.insertText("Image Path: " + imagePath + "\n\n");
    // Insert image
    if (!imagePath.isEmpty()) {
        QTextImageFormat imageFormat;
        imageFormat.setName(imagePath);
        cursor.insertImage(imageFormat);
    }

    // Save the document to a PDF file
    QPdfWriter pdfWriter(pdfFilePath);
    pdfWriter.setResolution(300); // Adjust resolution as needed
    pdfWriter.setPageSize(QPageSize(QPageSize::A4));

    QPainter painter(&pdfWriter);
    document.drawContents(&painter);

    if (painter.end()) {
        // Open the generated PDF file
        QDesktopServices::openUrl(QUrl::fromLocalFile(pdfFilePath));
        ui->notification1->setText("PDF generated successfully!");
    } else {
        qDebug() << "Error saving PDF file. Check the file path and permissions.";
        ui->notification1->setText("Error generating PDF!");
    }
}
