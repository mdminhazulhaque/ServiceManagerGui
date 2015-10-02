#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QStringList headerLabels;
    headerLabels << "Service Name" << "State";
    ui->serviceList->setHorizontalHeaderLabels(headerLabels);
    ui->serviceList->horizontalHeader()->setStretchLastSection(true);

    loadServiceState();

    setWindowTitle("ServiceManagerGui");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadServiceState()
{
    QProcess serviceListCmd;
    QStringList args;
    args << "--status-all";
    serviceListCmd.start("/usr/sbin/service", args);

    serviceListCmd.waitForFinished();
    QList<QByteArray>serviceNameList = serviceListCmd.readAll().split('\n');
    serviceListCmd.close();

    foreach(const QByteArray serviceName, serviceNameList)
    {
        if(serviceName.isEmpty())
            continue;

        QString serviceState = QString(serviceName).left(7);
        QString serviceNameStr = QString(serviceName).remove(0, 7);

        //qDebug() << serviceNameStr;

        QTableWidgetItem *serviceNameItem = new QTableWidgetItem(serviceNameStr);
        QLabel *button = new QLabel;

        switch(serviceState.toLocal8Bit().at(3))
        {
        case '+':
            button->setText(" Running");
            //button->setChecked(true);
            break;

        case '-':
            button->setText(" Stopped");
            //button->setChecked(false);
            break;

        case '?':
            button->setText("Undefined");
            break;
        }

        int rowIndex = ui->serviceList->rowCount();
        ui->serviceList->insertRow(rowIndex);

        ui->serviceList->setItem(rowIndex, 0, serviceNameItem);
        ui->serviceList->setCellWidget(rowIndex, 1, button);
    }

    //ui->serviceList->setVisible(false);
    ui->serviceList->resizeColumnsToContents();
    //ui->serviceList->setVisible(true);
}
