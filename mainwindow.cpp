#include "mainwindow.h"
#include "ui_mainwindow.h"

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

    QBuffer buffer;
    buffer.open(QBuffer::ReadWrite);
    QDataStream out( &buffer );
    out << ui->leFistName->text();
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
    QString strName;

    sharedMemory.lock();
    buffer.setData((char *)sharedMemory.constData(), sharedMemory.size());
    buffer.open( QBuffer::ReadOnly);
    in >> strName;

    qDebug() << strName;
    sharedMemory.unlock();

    ui->leFistName->setText( strName );
}

void MainWindow::clearFields()
{
    ui->leFistName->clear();
    ui->leSecondName->clear();
    ui->leNumberPhone->clear();
}
