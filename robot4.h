#ifndef ROBOT4_H
#define ROBOT4_H

#include <QMainWindow>
#include <QSerialPort>



namespace Ui {
class robot4;
}

//int tab[1000];

class robot4 : public QMainWindow
{
    Q_OBJECT

public:

    explicit robot4(QWidget *parent = 0);
    ~robot4();

private slots:
    void on_horizontalSlider_1_valueChanged(int value);

    void on_horizontalSlider_2_valueChanged(int value);

    void on_horizontalSlider_3_valueChanged(int value);

    void on_horizontalSlider_4_valueChanged(int value);

    void on_horizontalSlider_5_valueChanged(int value);

    void on_horizontalSlider_6_valueChanged(int value);

    void updateMotors(QString);


    void on_recordButton_clicked();

    void on_playButton_clicked();

    void on_pauseButton_clicked();

    void on_stopButton_clicked();

    void on_resetButton_clicked();

    void on_horizontalSlider_7_valueChanged(int value);

private:
    Ui::robot4 *ui;
    QSerialPort *arduino;
    static const qint16 arduino_uno_vendor_id = 9025;
    static const qint16 arduino_uno_product_id = 67;
    QString arduino_port_name;
    bool arduino_is_available;
};

#endif // ROBOT4_H
