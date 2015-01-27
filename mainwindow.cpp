#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    creatorConnections();
    setWindowTitle(tr("Main application window"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::creatorConnections()
{
    QObject::connect(ui->pbShowDialog, SIGNAL(clicked()), &dlg, SLOT(show()));

}
