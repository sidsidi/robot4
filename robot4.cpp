#include "robot4.h"
#include "ui_robot4.h"
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>
#include <QtWidgets>


robot4::robot4(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::robot4)
{
    ui->setupUi(this);

    arduino_is_available = false;
    arduino_port_name = "";
    arduino = new QSerialPort;

    qDebug() << "Liczba dostępnych portow: "<< QSerialPortInfo::availablePorts().length();
    foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()){
        qDebug() << "Ma Vendor ID: "<< serialPortInfo.hasVendorIdentifier();
        if(serialPortInfo.hasVendorIdentifier()){
            qDebug() << "Vendor ID: "<<serialPortInfo.vendorIdentifier();
        }
        qDebug() << "Ma Product ID: "<< serialPortInfo.hasProductIdentifier();
        if(serialPortInfo.hasProductIdentifier()){
            qDebug() << "Product ID: "<<serialPortInfo.productIdentifier();
        }
    }

    foreach (const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()){
        if (serialPortInfo.hasVendorIdentifier() && serialPortInfo.hasProductIdentifier()){
            if(serialPortInfo.vendorIdentifier() == arduino_uno_vendor_id){
                if(serialPortInfo.productIdentifier() == arduino_uno_product_id){
                    arduino_port_name = serialPortInfo.portName();
                    arduino_is_available = true;
                }
            }
        }

    }
    if (arduino_is_available){
        // open and configure serialport

        arduino->setPortName(arduino_port_name);
        arduino->open(QSerialPort::WriteOnly);
        arduino->setBaudRate(QSerialPort::Baud9600);
        arduino->setDataBits(QSerialPort::Data8);
        arduino->setParity(QSerialPort::NoParity);
        arduino->setStopBits(QSerialPort::OneStop);
        arduino->setFlowControl(QSerialPort::NoFlowControl);

    }
    else
        // give error message if not available
        QMessageBox::warning(this, "Error portu", "Nie moge znalezc Arduino UNO");
}

robot4::~robot4()
{
    if (arduino->isOpen()){
        arduino->close();
    }
    delete ui;
}

void robot4::on_horizontalSlider_1_valueChanged(int value)
{
    robot4::updateMotors(QString("A%1").arg(value));
}

void robot4::on_horizontalSlider_2_valueChanged(int value)
{
    robot4::updateMotors(QString("B%1").arg(value));
}

void robot4::on_horizontalSlider_3_valueChanged(int value)
{
    robot4::updateMotors(QString("C%1").arg(value));
}

void robot4::on_horizontalSlider_4_valueChanged(int value)
{
    robot4::updateMotors(QString("D%1").arg(value));
}

void robot4::on_horizontalSlider_5_valueChanged(int value)
{
    robot4::updateMotors(QString("E%1").arg(value));
}

void robot4::on_horizontalSlider_6_valueChanged(int value)
{
    robot4::updateMotors(QString("F%1").arg(value));
}

void robot4::updateMotors(QString command)
{
    if(arduino->isWritable()){
        arduino->write(command.toStdString().c_str());
    }
    else{
        qDebug() << "Nie moglem wyslac sygnalu na port szeregowy";
    }
}
