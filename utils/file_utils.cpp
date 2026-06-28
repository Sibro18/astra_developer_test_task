#include <QVector>
#include <QDirIterator>
#include <QFileInfo>
#include <QSet>

#ifdef Q_OS_LINUX
#include <sys/stat.h>
#endif

#include "file_utils.h"

qint64 FileUtils::calculateDirSize(
	const QString& path,
	QDir::Filters filters,
	StopFlag* stopFlag
)
{
	qint64 totalSize = 0;
	QDirIterator it(
		path,
		filters,
		QDirIterator::Subdirectories
	);

	while (it.hasNext())
	{
		if (stopFlag && stopFlag->value())
		{
			break;
		}

		const QFileInfo info = it.next();

		if (!info.isFile())
		{
			continue;
		}

		#ifdef Q_OS_LINUX
			struct stat fileStat;

			if (
				stat(info.absoluteFilePath().toUtf8().constData(), &fileStat) == 0 &&
				(fileStat.st_blocks <= 0)
			)
			{
				continue;
			}

			totalSize += info.size();
		#else
			totalSize += info.size();
		#endif
	}

	return totalSize;
}
