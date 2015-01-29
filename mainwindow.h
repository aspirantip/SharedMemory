#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSharedMemory>
#include <QBuffer>
#include <QDebug>

#include <dialog.h>
#include <contact.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
public slots:
    void saveToSharedMemory();
    void loadFromSharedMemory();
    void clearFields();

private:
    Ui::MainWindow *ui;
    Dialog dlg;
    QSharedMemory sharedMemory;

    void creatorConnections();
};

#endif // MAINWINDOW_H
