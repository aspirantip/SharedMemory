#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QSharedMemory>
#include <QBuffer>
#include <QMessageBox>
#include <QDebug>


namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    
public slots:
    void loadFromSharedMemory();

private:
    Ui::Dialog *ui;
    QSharedMemory sharedMemory;

    void creatorConnections();
};

#endif // DIALOG_H
