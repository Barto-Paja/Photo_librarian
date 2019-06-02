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

void Librarian::run()
{
    QStringListIterator iterator(_fileNames);

    while(iterator.hasNext())
    {
        QFileInfo fileInfo = QFileInfo(_sourcePath,iterator.next());
        _fileInfoList.append(fileInfo);
    }


}
