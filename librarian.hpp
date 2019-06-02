#ifndef LIBRARIAN_HPP
#define LIBRARIAN_HPP

#include <QObject>
#include <QDir>

#include <QFile>
#include <QFileInfo>
#include <QByteArray>

class Librarian : public QObject
{
    Q_OBJECT
public:
    explicit Librarian(QObject *parent = nullptr);
    Librarian(const QDir &sourcePath,const QDir &outputPath, const QStringList fileNames, QObject *parent = nullptr);

    void run();

signals:

public slots:

private:

    QDir _sourcePath;
    QDir _outputPath;
    QStringList _fileNames;
    QList<QFileInfo> _fileInfoList;

};

#endif // LIBRARIAN_HPP
