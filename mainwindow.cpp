#include "mainwindow.h"
#include "ui_mainwindow.h"

// перегружаем операторы ввода/вывода QDataStream
QDataStream &operator << (QDataStream &out, const contact &cont)
{
    out << cont.firstName;
    out << cont.lastName;
    out << cont.phone;

    return out;
}

QDataStream &operator >> (QDataStream &in, contact &cont)
{
    in >> cont.firstName;
    in >> cont.lastName;
    in >> cont.phone;

    return in;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), sharedMemory("SharedMemory")
{
    ui->setupUi(this);

    creatorConnections();
    setWindowTitle(tr("Main application window"));
}

MainWindow::~MainWindow()
{
    sharedMemory.detach();
    delete ui;
}

void MainWindow::creatorConnections()
{
    QObject::connect(ui->pbShowDialog,  SIGNAL(clicked()), &dlg, SLOT(show()));
    QObject::connect(ui->pbSaveData,    SIGNAL(clicked()), this, SLOT(saveToSharedMemory()));
    QObject::connect(ui->pbLoadFromSharedMemory, SIGNAL(clicked()), this, SLOT(loadFromSharedMemory()));
    QObject::connect(ui->pbClear,       SIGNAL(clicked()), this, SLOT(clearFields()));

}

void MainWindow::saveToSharedMemory()
{
    if (sharedMemory.isAttached())
        if (!sharedMemory.detach())
            statusBar()->showMessage(tr("Unable to detach from shared memory."));

    if (ui->leFistName->text().isEmpty())
        return;

    contact newContact;
    newContact.firstName = ui->leFistName->text();
    newContact.lastName = ui->leSecondName->text();
    newContact.phone = ui->leNumberPhone->text();

    QBuffer buffer;
    buffer.open(QBuffer::ReadWrite);
    QDataStream out( &buffer );
    out << newContact;
    int size = buffer.size();

    if (!sharedMemory.create(size)){
        statusBar()->showMessage(tr("Unable to create shared memory segment."));
        return;
    }

    sharedMemory.lock();
    char *to = (char *) sharedMemory.data();
    const char *from = buffer.data().data();
    memcpy(to, from, qMin(sharedMemory.size(), size));
    sharedMemory.unlock();

    statusBar()->showMessage(tr("Info stored in the shared memory segment."));
}

void MainWindow::loadFromSharedMemory()
{
    QBuffer buffer;
    QDataStream in(&buffer);
    contact oldContact;

    sharedMemory.lock();
    buffer.setData((char *)sharedMemory.constData(), sharedMemory.size());
    buffer.open( QBuffer::ReadOnly);
    in >> oldContact;
    sharedMemory.unlock();

    ui->leFistName->setText( oldContact.firstName);
    ui->leSecondName->setText( oldContact.lastName);
    ui->leNumberPhone->setText( oldContact.phone);
}

void MainWindow::clearFields()
{
    ui->leFistName->clear();
    ui->leSecondName->clear();
    ui->leNumberPhone->clear();
}



