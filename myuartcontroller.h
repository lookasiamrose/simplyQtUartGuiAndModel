#ifndef MYUARTCONTROLLER_H
#define MYUARTCONTROLLER_H

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>

class MyUartController : public QObject
{
    Q_OBJECT
private:
    QSerialPort *port;

    QString portName;
    qint32 baudRate;
public:
    explicit MyUartController(QObject *parent = 0);
    ~MyUartController();

    //control
    void writeChar(char char_arg);
    bool openPort(QString port_name, int baud_rate);
    bool reopenPort();

    //information about
    QList<QString> checkAvailablePorts();
    QList<QString> allAvailableCOMPorts();
    bool isPortOpenned();

    //getters and setters
    QString getPortName();
    void setPortName(QString portNameArg);

    qint32 getBaudRate();
    void setBaudRate(qint32 baudRateArg);

    QList<qint32> getStandardBaudRates();

    //not yet SOLID design, but still too small for that
};

#endif // MYUARTCONTROLLER_H
