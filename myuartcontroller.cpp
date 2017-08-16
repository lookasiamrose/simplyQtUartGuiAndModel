#include "myuartcontroller.h"

MyUartController::MyUartController(QObject *parent) : QObject(parent)
{
    port = nullptr;
}
MyUartController::~MyUartController()
{
    if( (port != nullptr) && (port->isOpen()) )
        port->close();

    delete port;
}
void MyUartController::writeChar(char char_arg)
{
    if( (port != nullptr) && port->isOpen())
    {
        QByteArray toSend;
        toSend.append(char_arg); //just one byte appended to standard array of bytes

        port->write(toSend,1); //write up to this single byte

        port->waitForBytesWritten(-1); //save wait for each write
        toSend.clear(); //unneeded
    }
}
bool MyUartController::openPort(QString portName, int baudRate)
{
    bool isOpen = false;
    foreach (const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts())
    {
        //Weird, but we need to "find" the port to open, there is no "select by name" method built
        if(serialPortInfo.portName() == portName)
        {
            port = new QSerialPort(this);
            port->setPort(serialPortInfo);
            port->setBaudRate(baudRate);
            port->open(QIODevice::ReadWrite);

            isOpen = true;
            break;
        }
    }
    return isOpen;
}
QList<QString> MyUartController::checkAvailablePorts()
{
    QList<QString> allPortsInfoList;
    foreach (const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts())
    {
       QString singlePortInfo;
       singlePortInfo = "Port: " + serialPortInfo.portName();
       singlePortInfo += "\n Location: " + serialPortInfo.systemLocation();
       singlePortInfo += "\n Description: " + serialPortInfo.description();
       singlePortInfo += "\n Manufacturer: " + serialPortInfo.manufacturer();
       singlePortInfo += "\n Vendor Identifier: " + (serialPortInfo.hasVendorIdentifier() ? QByteArray::number(serialPortInfo.vendorIdentifier(), 16) : QByteArray());
       singlePortInfo += "\n Product Identifier:" + (serialPortInfo.hasProductIdentifier() ? QByteArray::number(serialPortInfo.productIdentifier(), 16) : QByteArray());
       singlePortInfo += "\n Busy:" + (serialPortInfo.isBusy() ? QObject::tr("Yes") : QObject::tr("No"));
       singlePortInfo += "\n";

       QSerialPort *tempOpenedPort = new QSerialPort(serialPortInfo);
       if (tempOpenedPort->open(QIODevice::ReadWrite))
       {
           singlePortInfo += "\n Baud rate: " + tempOpenedPort->baudRate();
           singlePortInfo += "\n Data bits: " + tempOpenedPort->dataBits();
           singlePortInfo += "\n Stop bits: " + tempOpenedPort->stopBits();
           singlePortInfo += "\n Parity: " + tempOpenedPort->parity();
           singlePortInfo += "\n Flow control: " + tempOpenedPort->flowControl();
           singlePortInfo += "\n Read buffer size: " + tempOpenedPort->readBufferSize();
           tempOpenedPort->close();
       } else
           {
               singlePortInfo += "\nUnable to open port, error code " + tempOpenedPort->error();
           }
       delete tempOpenedPort;

       allPortsInfoList.append(singlePortInfo);
    }
    return allPortsInfoList;
}
bool MyUartController::reopenPort()
{
    if( (port !=nullptr) && (port->isOpen()) )
        port->close();

    return openPort(portName, baudRate);
}
QList<QString> MyUartController::allAvailableCOMPorts()
{
    QList<QString> listOfCOMPorts;
    foreach (const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts())
    {
       listOfCOMPorts.append(serialPortInfo.portName());
    }
    return listOfCOMPorts;
}
QString MyUartController::getPortName()
{
    return portName;
}
void MyUartController::setPortName(QString portNameArg)
{
    portName = portNameArg;
}
qint32 MyUartController::getBaudRate()
{
    return baudRate;
}
void MyUartController::setBaudRate(qint32 baudRateArg)
{
    baudRate = baudRateArg;
}
QList<qint32> MyUartController::getStandardBaudRates()
{
    return QSerialPortInfo::standardBaudRates();
}


