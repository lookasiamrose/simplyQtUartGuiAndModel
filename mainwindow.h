#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "myuartcontroller.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void createUpperMenu();

private slots:
    void baudSelection(QAction* baud);
    void menuSelection(QAction* item);
    void comPorts();
private:
    //gui
    Ui::MainWindow *ui;
    QAction* basicPortsInfoEntry;
    QList<QAction*> menuPortsAll;
    QMenu *upperMenu;
    QMenu *portsSubMenu;
    QMenu *baudsSubMenu;

    //model
    MyUartController* uartController;

    //window methods
    void addCOMPortsToMenu();
    void addBaudRatesToMenu();
    void connectMenuSignalsSlots();
};

#endif // MAINWINDOW_H
