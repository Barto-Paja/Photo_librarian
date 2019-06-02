#ifndef FILECOLLERCTOR_HPP
#define FILECOLLERCTOR_HPP

#include <QObject>
#include <QDir>
#include <QDirIterator>

#include <QList>
#include <QStringList>

class FileCollerctor : public QObject
{
    Q_OBJECT
public:
    explicit FileCollerctor(QObject *parent = nullptr);

    FileCollerctor(const QString &catalogName, QObject *parent = nullptr);
    FileCollerctor(const QDir &path, QObject *parent = nullptr);

    void run();

    QStringList fileNames() const;

signals:

public slots:

private:

    QDir _path;
    QStringList _fileNames;

};

#endif // FILECOLLERCTOR_HPP
