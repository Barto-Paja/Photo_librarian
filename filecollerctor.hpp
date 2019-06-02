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

signals:

public slots:
};

#endif // FILECOLLERCTOR_HPP
