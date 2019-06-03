#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDir>

#include <QFileDialog>
#include "filecollerctor.hpp"
#include "librarian.hpp"
#include <QTableWidgetItem>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_language_clicked();

    void on_pushButton_BrowseSource_clicked();

    void on_pushButton_BrowseOutput_clicked();

    void on_pushButton_start_clicked();

    void cellClicked(int row, int column);
    void cellChanged(QTableWidgetItem *item);

    void on_pushButton_back_clicked();

    void on_pushButton_exit_clicked();

private:
    Ui::MainWindow *ui;

    QDir _sourceDirectory;
    QDir _outputDirectory;

    void nextPage();

    QString _oldCatalogName;
};

#endif // MAINWINDOW_H
