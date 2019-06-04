#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTableWidgetItem>
#include <QHeaderView>
#include <QProcess>
#include <QThread>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->progressBar->setHidden(true);
    ui->label_3->setHidden(true);
}

MainWindow::~MainWindow()
{
    delete ui;
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

    ui->progressBar->setValue(0);
    ui->progressBar->setHidden(false);

    Librarian lb(_sourceDirectory,_outputDirectory,fc.fileNames());

    int count = fc.fileNames().count();
    ui->progressBar->setMaximum(count);
    connect(&lb, &Librarian::beeingCopy,[this](const QString &value, int index)
    {
        ui->label_3->setHidden(false);
        ui->label_3->setText(value);
        ui->progressBar->setValue(index);
        this->update();
    });

    if(ui->radioButton_day->isChecked())
    {
        lb.run(day);
    }
    else if (ui->radioButton_month->isChecked())
    {
        lb.run(month);
    }
    else if (ui->radioButton_year->isChecked())
    {
        lb.run(year);
    }
    else
    {
        lb.run();
    }

    QThread::sleep(1);
    nextPage();
}

void MainWindow::cellClicked(int row, int column)
{
    if(column == 1)
    {
        QString command = QString("explorer \"%1\\%2\"")
                .arg(QDir::toNativeSeparators(_outputDirectory.path()))
                .arg(ui->tableWidget->item(row,0)->text());
        QProcess::execute(command);
    }
    if(column == 0)
    {
       _oldCatalogName = ui->tableWidget->item(row,0)->text();
    }
}

void MainWindow::cellChanged(QTableWidgetItem *item)
{
    if(item->column() == 0)
    {
        if(ui->tableWidget->item(item->row(),0)->text().isEmpty())
        {
            ui->tableWidget->item(item->row(),0)->setText(_oldCatalogName);
        }
        else {
            QDir directory(_outputDirectory.path()+"/"+_oldCatalogName);
            directory.rename(directory.path(),QString("../%1").arg(ui->tableWidget->item(item->row(),0)->text()));
        }
    }
}

void MainWindow::nextPage()
{
    QStringList _catalogs = _outputDirectory.entryList();
    QStringList headers;
    headers << tr("Catalog Name") << tr("P");

    ui->tableWidget->setColumnCount(2);
    //ui->tableWidget->insertColumn(1);
    ui->tableWidget->setHorizontalHeaderLabels(headers);
    ui->tableWidget->horizontalHeader()->update();

    QIcon icon(QPixmap(":/folder.png").scaled(25,25));

    for(int i = 2; i < _catalogs.count(); ++i)
    {
        int row = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(row);
        ui->tableWidget->setItem(row,0,new QTableWidgetItem(_catalogs.value(i)));
        ui->tableWidget->setItem(row,1,new QTableWidgetItem(icon,""));
    }

    connect(ui->tableWidget,SIGNAL(cellClicked(int,int)),this,SLOT(cellClicked(int,int)));
    connect(ui->tableWidget,SIGNAL(itemChanged(QTableWidgetItem*)),this,SLOT(cellChanged(QTableWidgetItem*)));

    update();
    ui->stackedWidget->setCurrentIndex(1);

}

void MainWindow::on_pushButton_back_clicked()
{
    ui->tableWidget->clearContents();
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);
    ui->progressBar->setHidden(true);
    ui->label_3->setHidden(true);
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_pushButton_exit_clicked()
{  
    exit(0);
}

