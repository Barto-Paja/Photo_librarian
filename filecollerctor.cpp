#include "filecollerctor.hpp"

FileCollerctor::FileCollerctor(QObject *parent) : QObject(parent)
{

}

FileCollerctor::FileCollerctor(const QString &catalogName, QObject *parent)
{

}

FileCollerctor::FileCollerctor(const QDir &path, QObject *parent)
{
    _path = path;
    if(!_path.exists())
    {
        // rzuć błędem
    }
}

void FileCollerctor::run()
{

}
