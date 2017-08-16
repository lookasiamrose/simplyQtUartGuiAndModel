#include <QMessageBox>
#include <QActionGroup>
#include <QDebug>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    uartController = new MyUartController();

    createUpperMenu();
    connectMenuSignalsSlots();
}

void MainWindow::createUpperMenu()
{

    basicPortsInfoEntry = new QAction(tr("&Ports information"), this);
    basicPortsInfoEntry->setStatusTip(tr("Show connected COM ports"));
    upperMenu = menuBar()->addMenu(tr("&Menu"));
    upperMenu->addAction(basicPortsInfoEntry);

    portsSubMenu = new QMenu("Ports");
    baudsSubMenu = new QMenu("Baud rates");

    upperMenu->addMenu(portsSubMenu);
    upperMenu->addMenu(baudsSubMenu);

    addCOMPortsToMenu();
    addBaudRatesToMenu();
}

void MainWindow::addCOMPortsToMenu()
{
    QList<QString> allComPorts = uartController->allAvailableCOMPorts();
    foreach(QString port , allComPorts){
        menuPortsAll.append(new QAction(port));
    }

    QActionGroup* availablePortsSubMenu = new QActionGroup(this);
    foreach (QAction* menuEntryPort, menuPortsAll) {
        availablePortsSubMenu->addAction(menuEntryPort);
        menuEntryPort->setCheckable(true);
        portsSubMenu->addAction(menuEntryPort);
    }

    if(menuPortsAll.isEmpty()){
        QAction* emptyAction = new QAction("No ports available");
        portsSubMenu->addAction(emptyAction);
    }
}

void MainWindow::addBaudRatesToMenu()
{
    QList<qint32> availableBaudRates = uartController->getStandardBaudRates();
    if(!availableBaudRates.isEmpty())
        uartController->setBaudRate(availableBaudRates.at(0)); //just take the first one at beginning

    QActionGroup* baudGroup = new QActionGroup(this);
    foreach(qint32 numericBaud , availableBaudRates)
    {
        QString stringBaud = QString::number(numericBaud);
        QAction *baudMenuEntry = new QAction(stringBaud);

        baudGroup->addAction(baudMenuEntry);
        baudMenuEntry->setCheckable(true);
    }
    baudsSubMenu->addActions( baudGroup->actions() );
}

void MainWindow::connectMenuSignalsSlots()
{
    connect(portsSubMenu, SIGNAL(triggered(QAction*)), this, SLOT(menuSelection(QAction*)));
    connect(baudsSubMenu, SIGNAL(triggered(QAction*)), this, SLOT(baudSelection(QAction*)));
    connect(basicPortsInfoEntry, &QAction::triggered, this, &MainWindow::comPorts);
}

MainWindow::~MainWindow()
{
    delete portsSubMenu;
    delete baudsSubMenu;

    delete uartController;
    delete ui;
}
void MainWindow::baudSelection(QAction* baudEntry)
{
    uartController->setBaudRate(baudEntry->text().toInt());

    if(!uartController->getPortName().isEmpty())
        uartController->reopenPort();
}
void MainWindow::menuSelection(QAction* portEntry)
{
    uartController->setPortName(portEntry->text());
    uartController->reopenPort();
}
void MainWindow::comPorts()
{
    QList<QString> portsList = uartController->checkAvailablePorts();
    foreach(QString port , portsList){
        QMessageBox::information(this,"Ports",port,QMessageBox::Ok);
    }
    if(portsList.isEmpty()){
        QMessageBox::warning(this,"Ports","No COM ports detected");
    }
}
