#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDir>

#include <QFileDialog>
#include "filecollerctor.hpp"
#include "librarian.hpp"

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

private:
    Ui::MainWindow *ui;

    QDir _sourceDirectory;
    QDir _outputDirectory;
};

#endif // MAINWINDOW_H
