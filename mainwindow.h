#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>
#include <QCheckBox>
#include <QPushButton>
#include <QLabel>
#include <QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void loadServiceState();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
