#include <QVector>
#include <QDir>
#include <QDirIterator>
#include <QFileInfo>

#include "file_utils.h"

qint64 FileUtils::calculateDirSize(const QString& path)
{
	qint64 totalSize = 0;
	QVector<QString> dirsToVisit{path};

	while (!dirsToVisit.isEmpty())
	{
		const QString currentDir = dirsToVisit.takeLast();

		QDirIterator it(currentDir,
			QDir::AllEntries | QDir::NoDotAndDotDot | QDir::Hidden,
			QDirIterator::NoIteratorFlags
		);

		while (it.hasNext())
		{
			it.next();
			const QFileInfo info = it.fileInfo();

			// ignore symlinks.
			if (info.isSymLink())
			{
				continue;
			}

			if (info.isDir())
			{
				dirsToVisit.push_back(info.filePath());
			}
			else
			{
				totalSize += info.size();
			}
		}
	}

	return totalSize;
}
