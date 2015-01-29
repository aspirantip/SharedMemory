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
    qDebug() << "loadFromSharedMemory";

    if (!sharedMemory.attach()){
        QMessageBox::warning(this, tr("Error"), tr("Unable to attach to shared memory segment!"));
        return;
    }

    QBuffer buffer;
    QDataStream in(&buffer);
    QString strName;

    sharedMemory.lock();
    buffer.setData((char *)sharedMemory.constData(), sharedMemory.size());
    buffer.open( QBuffer::ReadOnly);
    in >> strName;

    qDebug() << strName;
    sharedMemory.unlock();
    sharedMemory.detach();

    ui->lblFullName->setText( strName );
}
