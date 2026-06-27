#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <QString>
#include <QtGlobal>
#include <QDir>

#include "types.h"

class FileUtils
{
public:
	static qint64 calculateDirSize(
		const QString& path,
		QDir::Filters filters,
		StopFlag* stopFlag = nullptr
	);
};

#endif // FILE_UTILS_H
