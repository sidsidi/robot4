#include "robot4.h"
#include "ui_robot4.h"
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>
#include <QtWidgets>

bool rec=0, play=0;
int rec_i=0, play_i=0;
QString rec_tab[1000];

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
    robot4::updateMotors(QString("%1").arg(value+1000));
}

void robot4::on_horizontalSlider_2_valueChanged(int value)
{
    robot4::updateMotors(QString("%1").arg(value+2000));
}

void robot4::on_horizontalSlider_3_valueChanged(int value)
{
    robot4::updateMotors(QString("%1").arg(value+3000));
}

void robot4::on_horizontalSlider_4_valueChanged(int value)
{
    robot4::updateMotors(QString("%1").arg(value+4000));
}

void robot4::on_horizontalSlider_5_valueChanged(int value)
{
    robot4::updateMotors(QString("%1").arg(value+5000));
}

void robot4::on_horizontalSlider_6_valueChanged(int value)
{
    robot4::updateMotors(QString("%1").arg(value+6000));
}

void robot4::updateMotors(QString command)
{
    if(arduino->isWritable()){
        arduino->putChar('A');
        arduino->write(command.toStdString().c_str());
   qDebug() << "OK: "<< command.toStdString().c_str();
        if (rec==1)
        {
            qDebug() << "OK: "<< command.toStdString().c_str();
            rec_tab[rec_i++]=command.toStdString().c_str();
        }
    }
    else{
        qDebug() << "Nie moglem wyslac sygnalu na port szeregowy";
    }
}


void robot4::on_recordButton_clicked()
{
    rec=1;
}

void robot4::on_playButton_clicked()
{
    rec=0;
    play=1;
   //while(play!=0)
    {
        for (play_i;play_i<=rec_i;play_i++)
        {
            qDebug()<<"now: "<<rec_tab[play_i];
            robot4::updateMotors(QString("%1").arg(rec_tab[play_i]));
        }

        play_i=0;
    }
}
void robot4::on_pauseButton_clicked()
{
    rec=0;
    play=0;
}

void robot4::on_stopButton_clicked()
{
    rec=0;
    play=0;
    play_i=0;
}

void robot4::on_resetButton_clicked()
{
    rec=0;
    play=0;
    for (int i=0;i<=rec_i;i++)
    {
        rec_tab[i]="";
    }
    play_i=0;
    rec_i=0;
}
