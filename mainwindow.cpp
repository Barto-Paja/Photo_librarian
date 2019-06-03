#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_language_clicked()
{

}

void MainWindow::on_pushButton_BrowseSource_clicked()
{
    _sourceDirectory = QFileDialog::getExistingDirectory(this, tr("Choose catalog"), QDir::homePath(), QFileDialog::ReadOnly);
    ui->lineEdit_SourcePath->setText(_sourceDirectory.path());
}

void MainWindow::on_pushButton_BrowseOutput_clicked()
{
    _outputDirectory = QFileDialog::getExistingDirectory(this, tr("Choose catalog"), QDir::homePath(), QFileDialog::ReadOnly);
    ui->lineEdit_output->setText(_outputDirectory.path());
}

void MainWindow::on_pushButton_start_clicked()
{
    FileCollerctor fc(_sourceDirectory);
    fc.run();

    Librarian lb(_sourceDirectory,_outputDirectory,fc.fileNames());
    lb.run();
}
