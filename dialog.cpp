#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog), sharedMemory("SharedMemory")
{
    ui->setupUi(this);
    setWindowTitle(tr("Additional application window"));
    creatorConnections();
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::creatorConnections()
{
    QObject::connect(ui->pbLoadInfo, SIGNAL(clicked()), this, SLOT(loadFromSharedMemory()));
}

void Dialog::loadFromSharedMemory()
{
    if (!sharedMemory.attach()){
        QMessageBox::warning(this, tr("Error"), tr("Unable to attach to shared memory segment!"));
        return;
    }

    QBuffer buffer;
    QDataStream in(&buffer);
    contact curContact;

    sharedMemory.lock();
    buffer.setData((char *)sharedMemory.constData(), sharedMemory.size());
    buffer.open( QBuffer::ReadOnly);
    in >> curContact.firstName;
    in >> curContact.lastName;
    in >> curContact.phone;
    sharedMemory.unlock();
    sharedMemory.detach();

    ui->lblFullName->setText( curContact.firstName + " " + curContact.lastName );
    ui->lblPhone->setText( curContact.phone );
}
