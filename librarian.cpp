#include "librarian.hpp"

Librarian::Librarian(QObject *parent) : QObject(parent)
{

}

Librarian::Librarian(const QDir &sourcePath, const QDir &outputPath, const QStringList fileNames, QObject *parent)
{
    _sourcePath = sourcePath;
    _outputPath = outputPath;
    _fileNames  = fileNames;
}

void Librarian::run(SortPrecision value)
{
    QStringListIterator iterator(_fileNames);

    while(iterator.hasNext())
    {
        QFileInfo fileInfo = QFileInfo(_sourcePath,iterator.next());
        _fileInfoList.append(fileInfo);
    }

    auto i = 0;
    for(i = 0 ;i < _fileInfoList.count(); ++i)
    {
        QString dirName;

        switch (value) {
        case day:
        {
            dirName = _fileInfoList[i].lastModified().date().toString("yyyy-MM-dd");
            break;
        }
        case month:
        {
            dirName = _fileInfoList[i].lastModified().date().toString("yyyy-MM");
            break;
        }
        case year:
        {
            dirName = _fileInfoList[i].lastModified().date().toString("yyyy");
            break;
        }
        }

        QString srcFile = _fileInfoList[i].filePath();
        QString outPath = _outputPath.path()+"/"+dirName;
        QString outFile = outPath+"/"+_fileInfoList[i].fileName();

        QDir outPathD(outPath);
        if(!outPathD.exists())
        {
            outPathD.mkpath(outPath);
        }

        QFile file(srcFile);
        file.open(QIODevice::ReadWrite);
        file.setPermissions(QFile::WriteOwner);
        emit beeingCopy(file.fileName(), i);

        if(!file.copy(outFile))
        {
            qDebug() << file.error() << file.errorString();
        }

    }

    ++i;
    emit beeingCopy("Gotowe", _fileInfoList.count());
}
